#include "vehicule.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

#include "Ecran.h"

#include "Commun.dat"

int	idQ,idS,idM;
char	*pShm;

Vehicule*	w;

int main(int argc, char *argv[])
{
    if ((idQ = msgget(CLE,0)) == -1)
       { perror("Err de msgget()");
         exit(1);
       }

    Trace("idQ = %d  idM = %d\n",idQ,idM);
    QApplication a(argc, argv);
    w = new Vehicule();
    w->show();

    return a.exec();
}
