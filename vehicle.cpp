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
#include "path.h"

Message message;
MessageMax messageReceived;
MessageSent messageVehicleState;
void handlerAlarm(int);
void handlerInterruption(int, siginfo_t *info, void *);
extern int idQ, idS, idM;
extern char *pShm;
extern Vehicle *w;
bool vehicleIsAtDepot = false;
bool returnToDepotRequested = false;
int secondsElapsed = 0;
VehicleState vehicleState = VEHICLE_NEXT_OPERATION;
VehicleState vehicleStateBeforeEvent = VEHICLE_NEXT_OPERATION;
bool vehiclePaused = false;
bool returnToDepotRequestedByUser = false;
int destination = DEPOT_LOCATION;
using namespace std;

Vehicle::Vehicle(QWidget * parent):QMainWindow(parent), ui(new Ui::Vehicle) {
    ui->setupUi(this);

    // Init all label instead of having the default "textlabel" label. 
    // Cannot even be used in this constructor without risking to have a core
    // dump.
    // w->printState("At the depot");

    // Since the purpose of this application is not to play with C++/Qt stuffs,
    // go directly to the alarm handler for the main logic. Going back and
    // forth the C++ code to C handler with sigsetjmp() and siglongjmp() has an
    // undefined behavior. Even gdb has issues trying to find which
    // instructions to read. The software crashes with SIGBUS and SIGSEGFAULT.
    // Also, the event handler function cannot manipulate unsafe functions i.e.
    // those not in this list:
    // http://man7.org/linux/man-pages/man7/signal.7.html otherwise the
    // behavior is undefined too.
    //
    struct sigaction actionInterruption;
    actionInterruption.sa_sigaction = handlerInterruption;
    sigemptyset(&actionInterruption.sa_mask);
    actionInterruption.sa_flags = SA_SIGINFO;
    if (sigaction(SIGINT, &actionInterruption, NULL) == -1) {
        Log::log(
            Log::Type::error,
            Log::Destination::stdout,
            std::string("Vehicle: Unable to arm the SIGINT signal: ") + strerror(errno));
        exit(1);
    }

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
    alarm(1);


    //force alarm
    // Alarm(1)
    //
    //
    // Meme si plus de destination, o
    //
    // alarm 1 piur découper segment en 5
    //
    //
    //
    // accumulation file de message
    // conbtrole est lancé, boucle, lire tous les messages
    //
    // 2L quand pas le pid de controle
    // IPC_NOWAIT
    // 
    // New intervention --> pas le numéro du tableau, mais la chaine
    //
    //
    //
    // Compter un véhicule simplement 3 variables de pid_t
}


    // ui->lineMessagePatron->setFocus();

Vehicle::~Vehicle(){
    delete ui;
}

void Vehicle::onSendButtonClicked() {
    Log::log(Log::Type::success, Log::Destination::stdout, "In vehicle onSendButtonClicked");
    ui->lineMessagePatron->clear();
    ui->lineMessagePatron->setFocus();
}

void Vehicle::onPauseButtonClicked() {
    Log::log(
        Log::Type::success,
        Log::Destination::stdout,
        "Vehicle: Pause button clicked");

    if (vehiclePaused) {
        vehicleState = vehicleStateBeforeEvent;
        vehiclePaused = false;
    } else {
        vehicleStateBeforeEvent = vehicleState;
        vehicleState = VEHICLE_PAUSING;
        vehiclePaused = true;
    }

    // Set focus to the text field used to send a message to the manager
    ui->lineMessagePatron->setFocus();
}

void Vehicle::onReturnButtonClicked() {
    Log::log(
        Log::Type::success,
        Log::Destination::stdout,
        "Vehicle: Return button clicked");

    if (returnToDepotRequestedByUser) {
        returnToDepotRequestedByUser = false;
    } else {
        returnToDepotRequestedByUser = true;
    }

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

void handlerAlarm(int) {

    Log::log(
        Log::Type::success,
        Log::Destination::stdout,
        "Vehicle: Received alarm");

    switch(vehicleState) {

        case VEHICLE_PAUSING:
            w->printState("Pausing");
            break;

        case VEHICLE_TRAVELLING:

            // If this is the first time, send the travelling state to the server.
            if (secondsElapsed == 0) {
                w->printState("Travelling");

                // Send state to server
                message.type = 1L;
                message.idProcess = getpid();
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
            }

            if (secondsElapsed < TIME_TO_TRAVEL) { 
                secondsElapsed++;
            } else {
                Log::log(
                    Log::Type::success,
                    Log::Destination::stdout,
                    "Vehicle: "
                    + to_string(TIME_TO_TRAVEL)
                    + " seconds elapsed, stopping to travel");
                if (returnToDepotRequested) {
                    vehicleState = VEHICLE_BACK_DEPOT;
                } else {
                    vehicleState = VEHICLE_OPERATING;
                }
                secondsElapsed = 0;
            }

            break;

        case VEHICLE_OPERATING:

            // If this is the first time, send the operating state to the server.
            if (secondsElapsed == 0) {

                w->printState("Operating");

                // Send state to server
                message.type = 1L;
                message.idProcess = getpid();
                message.request = REQUEST_VEHICLE_STATE_REPORT;
                message.start = VEHICLE_OPERATING;
                if (msgsnd(idQ, &message, sizeof(Message) - sizeof(long), 0) == -1) {
                    Log::log(
                        Log::Type::error,
                        Log::Destination::stdout,
                        std::string("Vehicle: Unable to send message (vehicle state operating) to message queue: ")
                        + strerror(errno));
                    exit(1);
                }
            }

            if (secondsElapsed < TIME_TO_OPERATE) { 
                secondsElapsed++;
            } else {
                Log::log(
                    Log::Type::success,
                    Log::Destination::stdout,
                    "Vehicle: "
                    + to_string(TIME_TO_OPERATE)
                    + " seconds elapsed, stopping to operate");
                vehicleState = VEHICLE_NEXT_OPERATION;
                secondsElapsed = 0;
            }

            break;
    
        // Vehicle back at depot
        case VEHICLE_BACK_DEPOT:
            // Outside to refresh UI
            w->printState("At the depot");

            // Send state to server
            message.type = 1L;
            message.idProcess = getpid();
            message.request = REQUEST_VEHICLE_STATE_REPORT;
            message.start = VEHICLE_BACK_DEPOT;
            if (msgsnd(idQ, &message, sizeof(Message) - sizeof(long), 0) == -1) {
                Log::log(
                    Log::Type::error,
                    Log::Destination::stdout,
                    std::string("Vehicle: Unable to send message (vehicle state back depot) to message queue: ")
                    + strerror(errno));
                exit(1);
            }

            vehicleState = VEHICLE_NEXT_OPERATION;
            vehicleIsAtDepot = true;

            break;

        // First time and ask for a new intervention to the server
        default:

            w->printState("Trying next operation");

            // The L suffix forces the literal value 1 to be cast to a long instead of an int.
            message.type = 1L;
            message.idProcess = getpid();
            message.request = REQUEST_SEARCH;
            message.start = destination;

            if (msgsnd(idQ, &message, sizeof(Message) - sizeof(long), 0) == -1) {
                Log::log(
                    Log::Type::error,
                    Log::Destination::stdout,
                    std::string("Vehicle: Unable to send message to message queue: ") + strerror(errno));
                exit(1);
            }

            // Receive location and reset the buffer first as msgrcv does not
            // do it for us.
            memset(messageReceived.message, 0, sizeof(messageReceived.message));
            if (msgrcv(idQ, &messageReceived, sizeof(MessageMax) - sizeof(long), getpid(), 0) == -1) {
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

            destination = messageReceived.message[i - 1];

            if (destination == DEPOT_LOCATION) {
                if (vehicleIsAtDepot) {
                    Log::log(
                        Log::Type::success,
                        Log::Destination::stdout,
                        "Vehicle: Request to get back to the depot received. But we are already at it. Not moving.");
                } else {
                    Log::log(
                        Log::Type::success,
                        Log::Destination::stdout,
                        "Vehicle: Request to get back to the depot received");
                }
                returnToDepotRequested = true;
            } else {
                returnToDepotRequested = false;
            }

            if (returnToDepotRequestedByUser) {
                returnToDepotRequested = true;
                returnToDepotRequestedByUser = false;
            }

            if (!(vehicleIsAtDepot && returnToDepotRequested)) {

                // Print the whole path to the destination in the vehicle Qt GUI.
                char bufferToDisplay[100] = "";
                char bufferForLoop[100] = "";
                for (i = 0; i < REQUEST_MESSAGE_MAX_PATH; i++) {
                    if (!messageReceived.message[i]) {
                        break;
                    }
                    sprintf(bufferForLoop, "%d(%s) ",
                        messageReceived.message[i],
                        stations[messageReceived.message[i]].stationName);
                    strcat(bufferToDisplay, bufferForLoop);
                }
                w->printMessageIntervention(bufferToDisplay);

                // Switch to the travelling branch of this condition after next alarm.
                vehicleState = VEHICLE_TRAVELLING;
                vehicleIsAtDepot = false;
            }
    }


    // Ask the OS to send a SIGALRM to the process after the number of
    // seconds has elapsed.
    alarm(1);
}

void handlerInterruption(int, siginfo_t *info, void *) {

    Log::log(
        Log::Type::success,
        Log::Destination::stdout,
        "Vehicle: Received SIGINT from "
        + to_string(info->si_pid)
        + ". Leaving.");

    // Send state to server
    message.type = 1L;
    message.idProcess = getpid();
    message.request = REQUEST_VEHICLE_QUIT;
    message.start = 0;
    if (msgsnd(idQ, &message, sizeof(Message) - sizeof(long), 0) == -1) {
        Log::log(
            Log::Type::error,
            Log::Destination::stdout,
            std::string("Vehicle: Unable to send message (vehicle request quit) to message queue: ")
            + strerror(errno));
        exit(1);
    }

    Log::log(
        Log::Type::success,
        Log::Destination::stdout,
        "Vehicle: Has quit.");

    exit(0);

}
