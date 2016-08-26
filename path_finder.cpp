#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include "generic.h"
#include "common.h"
#include "path.h"
#include <fstream>

Message message;
MessageMax messageToVehicle;
int idQ;
using namespace std;

int search(int currentNode, int destinationNode, int currentSize,
	       int followedPath[], int optimalPath[], int *sizePath) {
    int rc = 0;
    int mrc = 0;
    int i = 0;

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
            mrc = rc;
        i++;
    }
    nodes[currentNode].visit = 0;
    return mrc;
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
    Log::log(
        Log::Type::success,
        Log::Destination::stdout,
        std::to_string(getpid()) + " " + szBuffer);
    return;
}

int main(int, char *argv[]) {
    Log::log(
        Log::Type::success,
        Log::Destination::stdout,
        "Path finder: Main");

    int rc;
    int followedPath[55];
    int optimalPath[55];
    int sizePath = 0;
    string destinationName;
    int destination = 0;
    bool destinationExecuted = false;

    // Receive the message queue id by argument to the process
    idQ = atoi(argv[1]);

    // Take only the concerned message from the queue (determined by PID)
    if ((rc = msgrcv(idQ, &message, sizeof(Message) - sizeof(long), getpid(), 0)) == -1) {
        Log::log(
            Log::Type::error,
            Log::Destination::stdout,
            std::string("Path finder: Unable to receive message from message queue: ") + strerror(errno));
        exit(1);
    }

    // Message.idProcess has actually the pid of the vehicle process that sent
    // a message to the server which redirected that message to this process.
    messageToVehicle.type = message.idProcess;

    // Read destination id and name from the file
    fstream interventionFile(INTERVENTIONS_FILE,  ios::out | ios::in);
    if (!interventionFile) {
        Log::log(
            Log::Type::error,
            Log::Destination::stdout,
            "Server: Unable to open INTERVENTIONS_FILE in read mode.");
        exit(1);
    }

    string line = "";
    char *stringToParse = NULL;
    char *tokenizedString = NULL;
    while(getline(interventionFile, line)) {
        Log::log(
            Log::Type::success,
            Log::Destination::stdout,
            "Server: Reading from file: " + line);

        // strtok wants a char* while string.c_str() returns a const char*.
        // Let's duplicate our string content to a plain old char array à la C.
        free(stringToParse);
        stringToParse = strdup(line.c_str());

        cout << "DEBUG: \"" + string(stringToParse) << "\"" << endl;

        // Parse the destination number
        tokenizedString = strtok(stringToParse, INTERVENTIONS_FILE_SEPARATOR);
        if (tokenizedString == NULL) {
            Log::log(
                Log::Type::warning,
                Log::Destination::stdout,
                "Path finder: Error while parsing: \"" + line + "\". Skipping line.");
            continue;
        }
        destination = atoi(tokenizedString);

        // Parse the destination name
        tokenizedString = strtok(NULL, INTERVENTIONS_FILE_SEPARATOR);
        if (tokenizedString == NULL) {
            Log::log(
                Log::Type::warning,
                Log::Destination::stdout,
                "Path finder: Error while parsing: \"" + line + "\". Skipping line.");
            continue;
        }
        destinationName = tokenizedString;
            Log::log(
                Log::Type::warning,
                Log::Destination::stdout,
                "Path finder: destination name \"" + string(tokenizedString) + "\"");

        // Parse the execution
        tokenizedString = strtok(NULL, INTERVENTIONS_FILE_SEPARATOR);
        if (tokenizedString == NULL) {
            Log::log(
                Log::Type::warning,
                Log::Destination::stdout,
                "Path finder: Error while parsing: \"" + line + "\". Skipping line.");
            continue;
        }
        destinationExecuted = (atoi(tokenizedString) != 0);

        if (destinationExecuted) {
            Log::log(
                Log::Type::success,
                Log::Destination::stdout,
                "Path finder: The destination \"" + destinationName + "\" has been executed. Skipping line.");
            destination = -1;
            destinationName.clear();
            destinationExecuted = false;
            continue;
        }

        // Here we are sure the variable have been initialized. 

        int filePosition = interventionFile.tellg();
        cout << "File filePosition = " << filePosition << endl;

        // Write in the file the task has been executed
        interventionFile.seekp(filePosition - 1 - line.length(), ios::beg);
        interventionFile
            << destination
            << INTERVENTIONS_FILE_SEPARATOR
            << destinationName
            << INTERVENTIONS_FILE_SEPARATOR
            << "1"
            << endl;

        Log::log(
            Log::Type::success,
            Log::Destination::stdout,
            "Path finder: Task " + std::to_string(destination) + "; " + destinationName + " now set as executed.");
        break;
    }

    // The temporary char array might not be freed if we have reached the end
    // of the file. Must make sure manually as we are freeing at the next loop
    // iteration.
    if (stringToParse != NULL) {
        free(stringToParse);
    }

    // If not enough destination, go back to the depot.
    if (destination == 0) {
        Log::log(
            Log::Type::success,
            Log::Destination::stdout,
            "Path finder: No destination available. Sending vehicle to the depot.");
        // According to instructions, the depot is reported to be at A4, which
        // is the 3rd column in the global stations[] variable table.
        destination = DEPOT_LOCATION;
    }

    Log::log(
        Log::Type::success,
        Log::Destination::stdout,
        "Path finder: Searching from " + std::to_string(message.start) + " to " + std::to_string(destination));

    // Make sure the message body is empty in order to determine the size of
    // the message and find the last element of the message to detect the
    // depot.
    // memset(messageToVehicle.message, 0, sizeof(messageToVehicle.message));
    // for (unsigned int i=0; i< sizeof(messageToVehicle.message); i++) {
    //     cout << "Debug: " << i << ": \"" + messageToVehicle.message[i] << "\"" << endl;
    // }

    // Find the shortest path
    search(message.start, destination, 0, followedPath, &(optimalPath[1]), &sizePath);

    Log::log(
        Log::Type::success,
        Log::Destination::stdout,
        "Path finder: Search results (size " + std::to_string(sizePath) + ")");

    optimalPath[0] = message.start;
    // Display the path as debug info
    displayPath(optimalPath, sizePath + 1);

    messageToVehicle.message[0] = message.start;
    memcpy(messageToVehicle.message, optimalPath, (sizePath + 1) * sizeof(int));
    cout << "debug ------> here" << endl;

    if (msgsnd(idQ, &messageToVehicle, sizeof(int) * (sizePath + 1) + sizeof(pid_t) + sizeof(int), 0) == -1) {
        Log::log(
            Log::Type::error,
            Log::Destination::stdout,
            std::string("Path finder: Unable to send message to vehicle (" + std::to_string(messageToVehicle.idProcess) + ")"));
        exit(1);
    }

    Log::log(
        Log::Type::success,
        Log::Destination::stdout,
        "Path finder: " + std::to_string(getpid()) + " exited with successful.");
    exit(0);
}

