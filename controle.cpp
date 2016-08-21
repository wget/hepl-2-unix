#include "controle.h"
#include "ui_controle.h"
#include <signal.h>
#include <unistd.h>
#include "Donnee.dat"
#include "Ecran.h"

extern int	idQ,idS,idM;
char	*pShm;
extern Controle*	w;

Controle::Controle(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Controle)
{
    ui->setupUi(this);
    AfficheMessageV1("Au depot");
    AfficheMessageV2("Au depot");
    AfficheMessageV3("Au depot");

}

Controle::~Controle()
{
    delete ui;
}

void Controle::on_BouttonEnregistrer_clicked()
{
    Trace("dans on_BouttonEnregistrer_clicked");
    ui->lineIntervention->clear();
}

void Controle::on_BouttonFacture_clicked()
{
 Trace("dans on_BouttonFacture_clicked");
 
}

void Controle::on_BouttonTransmettre_clicked()
{
 Trace("dans on_BouttonTransmettre_clicked");
 ui->lineMessage->clear();
}

void Controle::on_BouttonTerminer_clicked()
{
 Trace("dans on_BouttonTerminer_clicked");
}


void Controle::TraceTroncon(QPainter* F,int D,int A)
{
        F->setPen(Qt::black);
        F->drawLine(Donnee[D].PosReel.L, Donnee[D].PosReel.C, Donnee[A].PosReel.L, Donnee[A].PosReel.C);
        F->setPen(Qt::red);
        F->drawText(Donnee[D].PosStation.L,Donnee[D].PosStation.C,Donnee[D].Station);
        F->drawText(Donnee[A].PosStation.L,Donnee[A].PosStation.C,Donnee[A].Station);
}

void Controle::paintEvent(QPaintEvent *event)
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

void Controle::AfficheMessageV1(const char* M)
{
    ui->lineV1->setText(M);
}

void Controle::AfficheMessageV2(const char* M)
{
    ui->lineV2->setText(M);
}

void Controle::AfficheMessageV3(const char* M)
{
    ui->lineV3->setText(M);
}

void Controle::AfficheIntervention(const char* M)
{
    ui->lineIntervention->setText(M);
}

void Controle::AfficheMessage(const char* M)
{
    ui->lineMessage->setText(M);
}

void Controle::Rafraichir()
{
    this->update();
}

