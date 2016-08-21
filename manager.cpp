#include "manager.h"
#include "ui_manager.h"
#include <signal.h>
#include <unistd.h>
#include "Data.dat"
#include "Screen.h"

extern int	idQ,idS,idM;
char	*pShm;
extern Manager*	w;

Manager::Manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Manager)
{
    ui->setupUi(this);
    AfficheMessageV1("Au depot");
    AfficheMessageV2("Au depot");
    AfficheMessageV3("Au depot");

}

Manager::~Manager()
{
    delete ui;
}

void Manager::on_BouttonEnregistrer_clicked()
{
    Trace("dans on_BouttonEnregistrer_clicked");
    ui->lineIntervention->clear();
}

void Manager::on_BouttonFacture_clicked()
{
 Trace("dans on_BouttonFacture_clicked");
 
}

void Manager::on_BouttonTransmettre_clicked()
{
 Trace("dans on_BouttonTransmettre_clicked");
 ui->lineMessage->clear();
}

void Manager::on_BouttonTerminer_clicked()
{
 Trace("dans on_BouttonTerminer_clicked");
}


void Manager::TraceTroncon(QPainter* F,int D,int A)
{
        F->setPen(Qt::black);
        F->drawLine(Data[D].PosReel.L, Data[D].PosReel.C, Data[A].PosReel.L, Data[A].PosReel.C);
        F->setPen(Qt::red);
        F->drawText(Data[D].PosStation.L,Data[D].PosStation.C,Data[D].Station);
        F->drawText(Data[A].PosStation.L,Data[A].PosStation.C,Data[A].Station);
}

void Manager::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::red);
    painter.setBrush(Qt::red);
    painter.drawRect(237,137,7,7);          // positionnement de V1 en A4
    painter.setPen(Qt::blue);
    painter.setBrush(Qt::blue);
    painter.drawRect(237,137,7,7);          // positionnement de V2 en A4
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.drawRect(237,137,7,7);          // positionnement de V3 en A4
 int i = 0;
 while (i<47)
 {TraceTroncon(&painter,Troncon[i].S1,Troncon[i].S2);
     i++;
 }

}

void Manager::AfficheMessageV1(const char* M)
{
    ui->lineV1->setText(M);
}

void Manager::AfficheMessageV2(const char* M)
{
    ui->lineV2->setText(M);
}

void Manager::AfficheMessageV3(const char* M)
{
    ui->lineV3->setText(M);
}

void Manager::AfficheIntervention(const char* M)
{
    ui->lineIntervention->setText(M);
}

void Manager::AfficheMessage(const char* M)
{
    ui->lineMessage->setText(M);
}

void Manager::Rafraichir()
{
    this->update();
}

