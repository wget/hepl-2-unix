#include "vehicle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

#include "generic.h"
#include "common.h"

int idQ, idS, idM;
char *pShm;
Vehicle *w;
int main(int argc, char *argv[])
{
    if ((idQ = msgget(MSG_QUEUE_KEY, 0)) == -1) {
        Log::log(
            Log::Type::error,
            Log::Destination::stdout,
            std::string("Vehicle main: Unable to recover the message queue: ") + strerror(errno));
        exit(1);
    }

    QApplication a(argc, argv);
    w = new Vehicle();
    w->show();

    Log::log(
        Log::Type::success,
        Log::Destination::stdout,
        "Vehicle main: idQ = " + std::to_string(idQ) + " idM = " + std::to_string(idM));

    return a.exec();
}
