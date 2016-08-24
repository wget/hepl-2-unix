#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "generic.h"
#include "common.h"

int idQ, idS, idM;
char *pShm;

Message message;

int main()
{
    if ((idQ = msgget(MSG_QUEUE_KEY, IPC_CREAT | IPC_EXCL | 0666)) == -1) {
        perror("Err de msgget()");
        exit(1);
    }

    Log::log(Log::Type::success, Log::Destination::stdout, "idQ = " + std::to_string(idQ) + " : idM = " + std::to_string(idM));
    int idpath_finder;
    char BuffQ[20];
    sprintf(BuffQ, "%d", idQ);

    while (1) {
        if (msgrcv(idQ, &message, sizeof(Message) - sizeof(long), 1L, 0) ==
            -1) {
            perror("Error in server msgrcv()");
            exit(1);
        }

        Log::log(Log::Type::success, Log::Destination::stdout, "Message received");

        switch (message.request) {
            case REQUEST_SEARCH:
                printf("message REQUEST_SEARCH");

                if ((idpath_finder = fork()) == -1) {
                    perror("Error in server fork");
                    exit(1);
                }

                if (!idpath_finder) {
                    execl("./path_finder", "path_finder", BuffQ, NULL);
                    perror("Error in server execlp");
                    exit(1);
                }

                message.type = idpath_finder;
                Log::log(Log::Type::success, Log::Destination::stdout, "----" + std::to_string(idpath_finder));

                if (msgsnd(idQ, &message, sizeof(Message) - sizeof(long), 0) ==  -1) {
                    perror("Error in server msgsnd");
                    exit(1);
                }

                break;
        }

    }
}
