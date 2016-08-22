#include "vehicle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

#include "screen.h"

#include "common.h"
int idQ, idS, idM;
char *pShm;
Vehicle *w;
int main(int argc, char *argv[])
{
    if ((idQ = msgget(MSG_QUEUE_KEY, 0)) == -1) {
        perror("Error in vehicle main msgget()");
        exit(1);
    }
    Trace("idQ = %d  idM = %d\n", idQ, idM);
    QApplication a(argc, argv);
    w = new Vehicle();
    w->show();
    return a.exec();
}
