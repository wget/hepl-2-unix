#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "screen.h"
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

    Trace("idQ = %d : idM = %d", idQ, idM);
    int idpath_finder;
    char BuffQ[20];
    sprintf(BuffQ, "%d", idQ);

    while (1) {
        if (msgrcv(idQ, &message, sizeof(Message) - sizeof(long), 1L, 0) ==
            -1) {
            perror("Err. de msgrcv()");
            exit(1);
        }

        Trace("message recu\n");

        switch (message.request) {
            case REQUEST_SEARCH:
                printf("message REQUEST_SEARCH\n");

                if ((idpath_finder = fork()) == -1) {
                    perror("Err de fork()");
                    exit(1);
                }

                if (!idpath_finder) {
                    execl("./path_finder", "path_finder", BuffQ, NULL);
                    perror("Err de execlp()");
                    exit(1);
                }

                message.type = idpath_finder;
                Trace("----%d", idpath_finder);

                if (msgsnd(idQ, &message, sizeof(Message) - sizeof(long), 0) ==  -1) {
                    perror("(serveur)Err de msgsnd()");
                    exit(1);
                }

                break;
        }

    }
}
