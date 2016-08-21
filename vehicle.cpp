#include "vehicle.h"
#include "ui_vehicle.h"
#include "Screen.h"
#include "Common.dat"

#include <signal.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

MESSAGE	Message;
MESSAGEMAX	MessageRecu;
MESSAGEEMIS	MessageEmis;

void HandlerAlarm(int);

extern int	idQ,idS,idM;
extern char	*pShm;
extern Vehicle*	w;
bool    enIntervention,enDeplacement,enPause;

Vehicle::Vehicle(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Vehicle)
{
    ui->setupUi(this);
    enDeplacement = true;
    enIntervention = false;
    enPause = false;

struct sigaction ActAlarm;
ActAlarm.sa_handler = HandlerAlarm;
sigemptyset(&ActAlarm.sa_mask);
ActAlarm.sa_flags = 0;
if (sigaction(SIGALRM,&ActAlarm,NULL) == -1)
   { perror("Err de sigaction()");
     exit(1);
   }


Message.lType = 1L;
Message.idProcess = getpid();
Message.Requete = RECHERCHE;
Message.Depart = 4;
if (msgsnd(idQ,&Message,sizeof(MESSAGE) - sizeof(long),0) == -1)
   { perror("Err de msgsnd()");
     exit(1);
   }
int rc;
if ((rc = msgrcv(idQ,&MessageRecu,sizeof(MESSAGEMAX) - sizeof(long),getpid(),0)) == -1)
        { perror("Err. de msgrcv()");
          exit(1);
        }
Trace(" message recu (size : %d)",rc);
char Buff[100];
sprintf(Buff,"%d  %d  %d  %d  \n",MessageRecu.Message[0],MessageRecu.Message[1],MessageRecu.Message[2],MessageRecu.Message[3]);

alarm(5);
    this->AfficheMessageIntervention(Buff);

    AfficheEtat("En deplacement");
    ui->lineMessagePatron->setFocus();

}

Vehicle::~Vehicle()
{
    delete ui;
}

void Vehicle::on_BouttonEnvoyer_clicked()
{
    Trace("dans on_BouttonEnvoyer_clicked");
    ui->lineMessagePatron->clear();
    ui->lineMessagePatron->setFocus();
}

void Vehicle::on_BouttonPause_clicked()
{
    Trace("dans on_BouttonPause_clicked");
    if (!enPause)
       { this->AfficheEtat("En Pause");
         enPause = true;
         return;
       }
    if (enIntervention)
    { this->AfficheEtat("En intervention");
      //enIntervention = false;
      enPause = false;
      return;
    }
    
    //if (enDeplacement)
       { this->AfficheEtat("En deplacement");
         //enDeplacement = false;
         enPause = false;
       }
    
    ui->lineMessagePatron->setFocus();
}

void Vehicle::on_BouttonRetour_clicked()
{   Trace("dans on_BouttonRetour_clicked");
    AfficheEtat("Retour au depot");
    ui->lineMessagePatron->setFocus();
}

void Vehicle::AfficheMessageIntervention(const char* M)
{
    ui->lineMessageIntervention->setText(M);
}

void Vehicle::AfficheMessageRecu(const char* M)
{
    ui->lineMessageRecu->setText(M);
}

void Vehicle::AfficheEtat(const char* M)
{
    ui->labelEtat->setText(M);
}

void HandlerAlarm(int)
{
Trace("Reception d'un alarm");    // juste pour la demo
enDeplacement = false;
enIntervention = true;
enPause = false;
w->AfficheEtat("En intervention" );

}
