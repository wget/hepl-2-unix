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

    sprintf(szBuffer, "(size: %d)   ", sizePath);
    for (i = 0; i < sizePath; i++) {
        sprintf(szBuffer1, "%d(%s) ", path[i], stations[path[i]].stationName);
        strcat(szBuffer, szBuffer1);
    }
    Log::log(
        Log::Type::success,
        Log::Destination::stdout,
        "Path finder (" + std::to_string(messageToVehicle.type)
        + "): "
        + szBuffer);
    return;
}

int main(int, char *argv[]) {
    Log::log(
        Log::Type::success,
        Log::Destination::stdout,
        // Escape ? char to avoid trigraphs to be triggered
        // http://stackoverflow.com/a/1234618/3514658
        "Path finder (?\?\?\?): Main");

    int rc;
    int followedPath[55];
    int optimalPath[55];
    int sizePath = 0;
    string destinationName;
    string destinationDescription;
    int destination = 0;
    bool destinationExecuted = false;
    unsigned int numberOfStations = sizeof(stations) / sizeof(Station);

    // Receive the message queue id by argument to the process
    idQ = atoi(argv[1]);

    // Take only the concerned message from the queue (determined by PID)
    if ((rc = msgrcv(idQ, &message, sizeof(Message) - sizeof(long), getpid(), 0)) == -1) {
        Log::log(
            Log::Type::error,
            Log::Destination::stdout,
            // Escape ? char to avoid trigraphs to be triggered
            // http://stackoverflow.com/a/1234618/3514658
            std::string("Path finder (?\?\?\?): Unable to receive message from message queue: ")
            + strerror(errno));
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
            "Path finder (" + std::to_string(messageToVehicle.type)
            + "): Unable to open INTERVENTIONS_FILE in read mode.");
        exit(1);
    }

    string line = "";
    char *stringToParse = NULL;
    char *tokenizedString = NULL;
    while(getline(interventionFile, line)) {
        Log::log(
            Log::Type::success,
            Log::Destination::stdout,
            "Path finder (" + std::to_string(messageToVehicle.type)
            + "): Reading from file: " + line);

        // strtok wants a char* while string.c_str() returns a const char*.
        // Let's duplicate our string content to a plain old char array à la C.
        free(stringToParse);
        stringToParse = strdup(line.c_str());

        // Parse the destination number
        tokenizedString = strtok(stringToParse, INTERVENTIONS_FILE_SEPARATOR);
        if (tokenizedString == NULL) {
            Log::log(
                Log::Type::warning,
                Log::Destination::stdout,
                "Path finder (" + std::to_string(messageToVehicle.type)
                + "): Error while parsing: \"" + line + "\". Skipping line.");
            continue;
        }

        // Research if destination valid. We need to find the index in the stations[] table
        unsigned int stationNumber = 0;
        for (stationNumber = 0; stationNumber < numberOfStations; stationNumber++) {
            if (!strcmp(tokenizedString, stations[stationNumber].stationName)) {
                destinationName = stations[stationNumber].stationName;
                break;
            }
        }

        if (stationNumber == numberOfStations) {
            Log::log(
                Log::Type::warning,
                Log::Destination::stdout,
                "Path finder (" + std::to_string(messageToVehicle.type)
                + "): Station not found. Skipping line.");
            continue;
        } else {

            Log::log(
                Log::Type::warning,
                Log::Destination::stdout,
                "Path finder (" + std::to_string(messageToVehicle.type)
                + "): Station number = "
                + to_string(stationNumber));
        }

        destination = stationNumber;

        // Parse the destination name
        tokenizedString = strtok(NULL, INTERVENTIONS_FILE_SEPARATOR);
        if (tokenizedString == NULL) {
            Log::log(
                Log::Type::warning,
                Log::Destination::stdout,
                "Path finder (" + std::to_string(messageToVehicle.type)
                + "): Error while parsing: \"" + line + "\". Skipping line.");
            continue;
        }
        destinationDescription = tokenizedString;

        Log::log(
            Log::Type::warning,
            Log::Destination::stdout,
            "Path finder (" + std::to_string(messageToVehicle.type)
            + "): Destination name \"" + string(tokenizedString) + "\"");

        // Parse the execution
        tokenizedString = strtok(NULL, INTERVENTIONS_FILE_SEPARATOR);
        if (tokenizedString == NULL) {
            Log::log(
                Log::Type::warning,
                Log::Destination::stdout,
                "Path finder (" + std::to_string(messageToVehicle.type)
                + "): Error while parsing: \"" + line + "\". Skipping line.");
            continue;
        }
        destinationExecuted = (atoi(tokenizedString) != 0);

        if (destinationExecuted) {
            Log::log(
                Log::Type::success,
                Log::Destination::stdout,
                "Path finder (" + std::to_string(messageToVehicle.type)
                + "): The destination \""
                + destinationName
                + "\" has been executed. Skipping line.");
            destination = -1;
            destinationName.clear();
            destinationExecuted = false;
            continue;
        }

        // Here we are sure the parsed variables have been initialized. 

        int filePosition = interventionFile.tellg();

        // Write in the file the task has been executed
        interventionFile.seekp(filePosition - 1 - line.length(), ios::beg);
        interventionFile
            << destinationName
            << INTERVENTIONS_FILE_SEPARATOR
            << destinationDescription
            << INTERVENTIONS_FILE_SEPARATOR
            << "1"
            << endl;

        Log::log(
            Log::Type::success,
            Log::Destination::stdout,
            "Path finder (" + std::to_string(messageToVehicle.type)
            + "): Task "
            + std::to_string(destination)
            + "; " + destinationName
            + " now set as executed.");
        break;
    }

    // The temporary char array might not get freed if we have reached the end
    // of the file. Must make sure manually as we are freeing at the next loop
    // iteration.
    if (stringToParse != NULL) {
        free(stringToParse);
    }

    // If not destination enough, send the vehicle back to the depot.
    // As interventionFile is a stream, detect if we reached end of file.
    if (!interventionFile) {
        Log::log(
            Log::Type::success,
            Log::Destination::stdout,
            "Path finder (" + std::to_string(messageToVehicle.type)
            + "): No destination available. Sending vehicle back to depot.");
        // According to instructions, the depot is reported to be at A4, which
        // is the 3rd y in the global stations[] variable table.
        destination = DEPOT_LOCATION;
    }

    Log::log(
        Log::Type::success,
        Log::Destination::stdout,
        "Path finder (" + std::to_string(messageToVehicle.type)
        + "): Searching from "
        + stations[message.start].stationName
        + " to "
        + stations[destination].stationName);

    // Find the shortest path
    search(message.start, destination, 0, followedPath, &(optimalPath[1]), &sizePath);

    Log::log(
        Log::Type::success,
        Log::Destination::stdout,
        "Path finder (" + std::to_string(messageToVehicle.type)
        + "): Search results (size " + std::to_string(sizePath) + ")");

    optimalPath[0] = message.start;
    // Display the path as debug info
    displayPath(optimalPath, sizePath + 1);

    messageToVehicle.message[0] = message.start;
    memcpy(messageToVehicle.message, optimalPath, (sizePath + 1) * sizeof(int));

    if (msgsnd(idQ, &messageToVehicle, sizeof(int) * (sizePath + 1) + sizeof(pid_t) + sizeof(int), 0) == -1) {
        Log::log(
            Log::Type::error,
            Log::Destination::stdout,
            "Path finder (" + std::to_string(messageToVehicle.type)
            + "): Unable to send message to vehicle ("
            + std::to_string(messageToVehicle.idProcess)
            + ")");
        exit(1);
    }

    Log::log(
        Log::Type::success,
        Log::Destination::stdout,
        "Path finder (" + std::to_string(messageToVehicle.type)
        + "): Exited with successful.");
    exit(0);
}

