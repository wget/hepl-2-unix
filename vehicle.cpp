#include <signal.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <setjmp.h>

#include "vehicle.h"
#include "vehicle_ui.h"
#include "generic.h"
#include "common.h"

Message message;
MessageMax messageReceived;
MessageSent messageVehicleState;
void handlerAlarm(int);
extern int idQ, idS, idM;
extern char *pShm;
extern Vehicle *w;
bool vehicleCurrentlyOperating = false;
bool vehicleCurrentlyTravelling = false;
bool vehicleCurrentlyPausing = false;
bool returnToDepotRequested = false;
jmp_buf nextOperationEnv;
jmp_buf backFromAlarmEnv;
int backFromAlarm = 0;
using namespace std;

Vehicle::Vehicle(QWidget * parent):QMainWindow(parent), ui(new Ui::Vehicle) {
    ui->setupUi(this);

    struct sigaction actionAlarm;
    actionAlarm.sa_handler = handlerAlarm;
    sigemptyset(&actionAlarm.sa_mask);
    actionAlarm.sa_flags = 0;
    if (sigaction(SIGALRM, &actionAlarm, NULL) == -1) {
        Log::log(
            Log::Type::error,
            Log::Destination::stdout,
            std::string("Vehicle: Unable to arm the SIGALRM signal: ") + strerror(errno));
        exit(1);
    }

    // Location where we are sent back when an operation has been finished and
    // we want to get the next one.
    backFromAlarm = sigsetjmp(backFromAlarmEnv, 1);
    returnToDepotRequested = false;

    // Ask new intervention to the server
    // The L suffix forces the literal value 1 to be cast to a long instead of an int.
    message.type = 1L;
    message.idProcess = getpid();
    message.request = REQUEST_SEARCH;
    message.start = 4;

    if (msgsnd(idQ, &message, sizeof(Message) - sizeof(long), 0) == -1) {
        Log::log(
            Log::Type::error,
            Log::Destination::stdout,
            std::string("Vehicle: Unable to send message to message queue: ") + strerror(errno));
        exit(1);
    }

    int rc;

    // Receive location
    if ((rc = msgrcv(idQ, &messageReceived, sizeof(MessageMax) - sizeof(long), getpid(), 0)) == -1) {
        Log::log(
            Log::Type::error,
            Log::Destination::stdout,
            std::string("Vehicle: Unable to receive message from message queue: ") + strerror(errno));
        exit(1);
    }

    // Detect if the vehicle needs to get back to the depot.
    unsigned int i = 0;
    for (i = 0; i < REQUEST_MESSAGE_MAX_PATH; i++) {
        if (!messageReceived.message[i]) {
            break;
        }
    }
    if (messageReceived.message[i - 1] == DEPOT_LOCATION) {
        returnToDepotRequested = true;
    }

    Log::log(
        Log::Type::success,
        Log::Destination::stdout,
        "Vehicle: Message received (size : " + std::to_string(rc) + ")");

    // Put vehicle state on GUI.
    printState("Travelling");
    vehicleCurrentlyTravelling = true;

    // Send state to server
    message.request = REQUEST_VEHICLE_STATE_REPORT;
    message.start = VEHICLE_TRAVELLING;
    if (msgsnd(idQ, &message, sizeof(Message) - sizeof(long), 0) == -1) {
        Log::log(
            Log::Type::error,
            Log::Destination::stdout,
            std::string("Vehicle: Unable to send message (vehicle state travelling) to message queue: ")
            + strerror(errno));
        exit(1);
    }

    // Print the whole path to the destination in the vehicle Qt GUI.
    char buffer[100];
    sprintf(buffer, "%d  %d  %d  %d  \n",
        messageReceived.message[0],
        messageReceived.message[1],
        messageReceived.message[2],
        messageReceived.message[3]);
    this->printMessageIntervention(buffer);

    // Save the environment in order to get back after the alarm handler.
    backFromAlarm = sigsetjmp(backFromAlarmEnv, 1);

    // Back from travelling
    if (backFromAlarm == 1) {
        vehicleCurrentlyTravelling = false;
        vehicleCurrentlyOperating = true;
        vehicleCurrentlyPausing = false;

        if (returnToDepotRequested) {
            message.start = VEHICLE_BACK_DEPOT;
            printState("At the depot");
        } else {
            message.start = VEHICLE_OPERATING;
            printState("Operating");
        }

        // Send state to server
        message.request = REQUEST_VEHICLE_STATE_REPORT;
        if (msgsnd(idQ, &message, sizeof(Message) - sizeof(long), 0) == -1) {
            Log::log(
                Log::Type::error,
                Log::Destination::stdout,
                std::string("Vehicle: Unable to send message (vehicle state operating) to message queue: ")
                + strerror(errno));
            exit(1);
        }

        // Do not ask another operation as there isn't any one more.
        if (returnToDepotRequested) {
            return;
        }

        // Time for the execution of the operation
        alarm(5);

    // Back from operating
    } else if (backFromAlarm == 2) {
        vehicleCurrentlyTravelling = false;
        vehicleCurrentlyOperating = false;
        vehicleCurrentlyPausing = false;
        printState("Next operation");
        siglongjmp(nextOperationEnv, 1);

    // First time
    } else {
        // Ask the OS to send a SIGALRM to the process after the number of
        // seconds has elapsed.
        alarm(5);
    }


    ui->lineMessagePatron->setFocus();

    Log::log(
        Log::Type::success,
        Log::Destination::stdout,
        "Vehicle: No more operation. Do not ask another one.");
}

Vehicle::~Vehicle(){
    delete ui;
}

void Vehicle::onSendButtonClicked() {
    Log::log(Log::Type::success, Log::Destination::stdout, "In vehicle onSendButtonClicked");
    ui->lineMessagePatron->clear();
    ui->lineMessagePatron->setFocus();
}

void Vehicle::onPauseButtonClicked() {
    Log::log(Log::Type::success, Log::Destination::stdout, "In vehicle onPauseButtonClicked");
    if (!vehicleCurrentlyPausing) {
        printState("Pausing");
        vehicleCurrentlyPausing = true;
        return;
    }

    if (vehicleCurrentlyOperating) {
        printState("Operating");

        //vehicleCurrentlyOperating = false;
        vehicleCurrentlyPausing = false;
        return;
    }

    //if (vehicleCurrentlyTravelling) {
	this->printState("Travelling");

	//vehicleCurrentlyTravelling = false;
	vehicleCurrentlyPausing = false;
    // }
    ui->lineMessagePatron->setFocus();
}

void Vehicle::onReturnButtonClicked() {
    Log::log(
        Log::Type::success,
        Log::Destination::stdout,
        "In vehicle onReturnButtonClicked");

    printState("Vehicle back to the depot");
    ui->lineMessagePatron->setFocus();
}

void Vehicle::printMessageIntervention(const char *M) {
    ui->lineMessageIntervention->setText(M);
}

void Vehicle::printMessageRecu(const char *M) {
    ui->lineMessageReceived->setText(M);
}

void Vehicle::printState(const char *M) {
    ui->labelState->setText(M);
}

// Do bot manipulate the GUI thread from that function. The behavior is
// undefined. And prevents the handler to manipulate unsafe functions i.e.
// those not in this list: http://man7.org/linux/man-pages/man7/signal.7.html
// otherwise the behavior is undefined too.
void handlerAlarm(int) {

    Log::log(
        Log::Type::success,
        Log::Destination::stdout,
        "Vehicle received alarm");

    if (vehicleCurrentlyTravelling) {
        siglongjmp(backFromAlarmEnv, 1);
    } else if (vehicleCurrentlyOperating) {
        siglongjmp(backFromAlarmEnv, 2);
    }
}
