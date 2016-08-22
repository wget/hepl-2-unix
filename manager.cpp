#include <signal.h>
#include <unistd.h>
#include "path.h"
#include "screen.h"
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
    Trace("In manager onSaveButtonClicked");
    ui->lineOperation->clear();
}

void Manager::onInvoiceButtonClicked() {
    Trace("In manager onInvoiceButtonClicked");
}

void Manager::onSendButtonClicked() {
    Trace("In manager onSendButtonClicked");
    ui->lineMessage->clear();
}

void Manager::onFinishButtonClicked() {
    Trace("In manager onFinishButtonClicked");
}

void Manager::drawSection(QPainter * F, int D, int A) {
    F->setPen(Qt::black);
    F->drawLine(
        stations[D].realLocation.row,
        stations[D].realLocation.column,
        stations[A].realLocation.row,
		stations[A].realLocation.column);
    F->setPen(Qt::red);
    F->drawText(
        stations[D].stationLocation.row,
        stations[D].stationLocation.column,
		stations[D].Station);
    F->drawText(
        stations[A].stationLocation.row,
        stations[A].stationLocation.column,
		stations[A].Station);
}

void Manager::paintEvent(QPaintEvent * event) {
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
