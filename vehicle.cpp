#include <signal.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

#include "vehicle.h"
#include "vehicle_ui.h"
#include "generic.h"
#include "common.h"

Message message;
MessageMax messageReceived;
MessageSent messageSent;
void handlerAlarm(int);
extern int idQ, idS, idM;
extern char *pShm;
extern Vehicle *w;
bool vehicleCurrentlyOperating, vehicleCurrentlyTravelling, vehicleCurrentlyPausing;

Vehicle::Vehicle(QWidget * parent):QMainWindow(parent), ui(new Ui::Vehicle) {
    ui->setupUi(this);
    vehicleCurrentlyTravelling = true;
    vehicleCurrentlyOperating = false;
    vehicleCurrentlyPausing = false;

    struct sigaction ActAlarm;
    ActAlarm.sa_handler = handlerAlarm;
    sigemptyset(&ActAlarm.sa_mask);
    ActAlarm.sa_flags = 0;
    if (sigaction(SIGALRM, &ActAlarm, NULL) == -1) {
        perror("Error in vehicle sigaction()");
        exit(1);
    }

    message.type = 1L;
    message.idProcess = getpid();
    message.request = REQUEST_SEARCH;
    message.start = 4;

    if (msgsnd(idQ, &message, sizeof(Message) - sizeof(long), 0) == -1) {
        perror("Error in vehicle msgsnd()");
        exit(1);
    }

    int rc;

    if ((rc = msgrcv(idQ, &messageReceived, sizeof(MessageMax) - sizeof(long), getpid(), 0)) == -1) {
        perror("Error in vehicle msgrcv()");
        exit(1);
    }
    Log::log(Log::Type::success, Log::Destination::stdout, "Message received (size : " + std::to_string(rc));

    char Buff[100];
    sprintf(Buff, "%d  %d  %d  %d  \n",
        messageReceived.message[0],
	    messageReceived.message[1],
        messageReceived.message[2],
	    messageReceived.message[3]);
    alarm(5);
    this->printMessageIntervention(Buff);
    printState("Vehicle currently travelling");
    ui->lineMessagePatron->setFocus();
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
        this->printState("Vehicle currently pausing");
        vehicleCurrentlyPausing = true;
        return;
    }

    if (vehicleCurrentlyOperating) {
        this->printState("Vehicle currently operating");

        //vehicleCurrentlyOperating = false;
        vehicleCurrentlyPausing = false;
        return;
    }

    //if (vehicleCurrentlyTravelling) {
	this->printState("Vehicle currently travelling");

	//vehicleCurrentlyTravelling = false;
	vehicleCurrentlyPausing = false;
    // }
    ui->lineMessagePatron->setFocus();
}

void Vehicle::onReturnButtonClicked() {
    Log::log(Log::Type::success, Log::Destination::stdout, "In vehicle onReturnButtonClicked");
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

void handlerAlarm(int) {
    // For the demo
    Log::log(Log::Type::success, Log::Destination::stdout, "Vehicle received alarm");
    vehicleCurrentlyTravelling = false;
    vehicleCurrentlyOperating = true;
    vehicleCurrentlyPausing = false;
    w->printState("Vehicle currently operating");
}
