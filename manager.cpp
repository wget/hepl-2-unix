#include <signal.h>
#include <unistd.h>
#include "path.h"
#include "generic.h"
#include "manager.h"
#include "manager_ui.h"

extern int idQ, idS, idM;
char *pShm;
extern Manager *w;

Manager::Manager(QWidget * parent):QMainWindow(parent), ui(new Ui::Manager) {
    ui->setupUi(this);
    printMessageV1("To the depot");
    printMessageV2("To the depot");
    printMessageV3("To the depot");
}

Manager::~Manager() {
    delete ui;
}

void Manager::onSaveButtonClicked() {
    Log::log(Log::Type::success, Log::Destination::stdout, "In manager onSaveButtonClicked");
    ui->lineOperation->clear();
}

void Manager::onInvoiceButtonClicked() {
    Log::log(Log::Type::success, Log::Destination::stdout, "In manager onInvoiceButtonClicked");
}

void Manager::onSendButtonClicked() {
    Log::log(Log::Type::success, Log::Destination::stdout, "In manager onSendButtonClicked");
    ui->lineMessage->clear();
}

void Manager::onFinishButtonClicked() {
    Log::log(Log::Type::success, Log::Destination::stdout, "In manager onFinishButtonClicked");
}

void Manager::drawSection(QPainter * F, int D, int A) {
    F->setPen(Qt::black);
    F->drawLine(
        stations[D].dotLocation.x,
        stations[D].dotLocation.y,
        stations[A].dotLocation.x,
		stations[A].dotLocation.y);
    F->setPen(Qt::red);
    F->drawText(
        stations[D].textLocation.x,
        stations[D].textLocation.y,
		stations[D].stationName);
    F->drawText(
        stations[A].textLocation.x,
        stations[A].textLocation.y,
		stations[A].stationName);
}

void Manager::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setPen(Qt::red);
    painter.setBrush(Qt::red);
	// From V1 to A4
    painter.drawRect(237, 137, 7, 7);
    painter.setPen(Qt::blue);
    painter.setBrush(Qt::blue);
    // From V2 to A4
    painter.drawRect(237, 137, 7, 7);	
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    // From V3 to A4
    painter.drawRect(237, 137, 7, 7);	
    int i = 0;
    while (i < 47) {
        drawSection(&painter, sections[i].S1, sections[i].S2);
        i++;
    }
}

void Manager::printMessageV1(const char *M) {
    ui->lineV1->setText(M);
}

void Manager::printMessageV2(const char *M) {
    ui->lineV2->setText(M);
}

void Manager::printMessageV3(const char *M) {
    ui->lineV3->setText(M);
}

void Manager::AfficheIntervention(const char *M) {
    ui->lineOperation->setText(M);
}

void Manager::printMessage(const char *M) {
    ui->lineMessage->setText(M);
}

void Manager::refresh() {
    this->update();
}
