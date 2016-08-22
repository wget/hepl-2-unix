#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include "screen.h"
#include "common.h"
#include "path.h"

Message message;
MessageMax ride;
int idQ;

int search(int currentNode, int destinationNode, int currentSize,
	       int followedPath[], int optimalPath[], int *sizePath) {
    int rc, Mrc, i;

    if (nodes[currentNode].visit)
        return 0;

    if (currentNode == destinationNode) {
        if (currentSize < *sizePath || *sizePath == 0) {
            memcpy(optimalPath, followedPath, currentSize * sizeof(int));
            *sizePath = currentSize;
            return 1;
        }
        return 0;
    }
    nodes[currentNode].visit = 1;

    i = 0;
    while (i < 6 && nodes[currentNode].nextnodes[i] != 0) {
        followedPath[currentSize] = nodes[currentNode].nextnodes[i];
        rc = search(nodes[currentNode].nextnodes[i], destinationNode, currentSize + 1, followedPath, optimalPath, sizePath);
        if (rc != 0)
            Mrc = rc;
        i++;
    }
    nodes[currentNode].visit = 0;
    return Mrc;
}

void displayPath(int path[], int sizePath) {
    int i = 0;
    char szBuffer[80];
    char szBuffer1[80];

    sprintf(szBuffer, "(%d)   ", sizePath);
    while (i < sizePath) {
        sprintf(szBuffer1, "%d ", path[i++]);
        strcat(szBuffer, szBuffer1);
    }
    Trace("\t(%d) %s", getpid(), szBuffer);
    return;
}

int main(int argc, char *argv[]) {
    Trace("In path finder main search");
    int rc;
    int followedPath[55];
    int optimalPath[55];
    int sizePath = 0;
    int destination;
    idQ = atoi(argv[1]);
    if ((rc = msgrcv(idQ, &message, sizeof(Message) - sizeof(long), getpid(), 0)) == -1) {
        perror("Error in path finder sgrcv()");
        exit(1);
    }

    ride.type = message.idProcess;
    // Must be modified according the destination
    destination = 29;

    // For tests
    Trace("Starting path finder search: %d to %d", message.start, destination);
    search(message.start, destination, 0, followedPath, &(optimalPath[1]), &sizePath);

    Trace("path finder results (size %d)", sizePath);
    optimalPath[0] = message.start;
    displayPath(optimalPath, sizePath + 1);

    Trace("path finder displayed results");
    ride.message[0] = message.start;
    memcpy(ride.message, optimalPath, (sizePath + 1) * sizeof(int));

    if (msgsnd(idQ, &ride, sizeof(int) * (sizePath + 1) + sizeof(pid_t) + sizeof(int), 0) == -1) {
        perror("Error in path finder msgsnd()");
        exit(1);
    }
    exit(0);
}

