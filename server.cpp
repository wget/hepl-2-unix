#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <vector>
#include <fstream>

#include "generic.h"
#include "common.h"

using namespace std;

int idQ, idS, idM;
char *pShm;

Message message;

void cleanup(int);

int main(int argc, char *argv[])
{

    struct sigaction sigAction;
    sigAction.sa_handler = cleanup;
    sigemptyset(&sigAction.sa_mask);
    sigAction.sa_flags = 0;

    if (sigaction(SIGINT, &sigAction, NULL) == -1) {
        Log::log(
            Log::Type::error,
            Log::Destination::stdout,
            std::string("Server: Unable to arm the SIGINT signal: ") + strerror(errno));
        exit(1);
    }

    if ((idQ = msgget(MSG_QUEUE_KEY, IPC_CREAT | IPC_EXCL | 0666)) == -1) {
        Log::log(
            Log::Type::error,
            Log::Destination::stdout,
            std::string("Server: Unable to create the message queue: ") + strerror(errno));
        exit(1);
    }

    if (argc > 1 && std::string(argv[1]) == "--init") {

        // Creation of a list of fictive interventions if specified by the user
        Log::log(
            Log::Type::success,
            Log::Destination::stdout,
            "Server: Creating fictive list of interventions");

        std::vector<std::string> records = {
            "4;Batibouw;0",
            "7;Arch Linux;0",
            "12;Some values;0",
            "6;Love mum;0",
            "8;Seraing;0",
            "9;Evil;0"};

        {
            ofstream interventionFile(INTERVENTIONS_FILE);
            if (!interventionFile) {
                Log::log(
                    Log::Type::error,
                    Log::Destination::stdout,
                    "Server: Unable to open INTERVENTIONS_FILE for writing");
                cleanup(0);
                exit(1);
            }
            for (unsigned int i = 0; i < records.size(); i++) {
                Log::log(
                    Log::Type::success,
                    Log::Destination::stdout,
                    "Server: Writing " + records[i]);
                interventionFile << records[i] << endl;
            }
            interventionFile.close();
        }

        ifstream interventionFile(INTERVENTIONS_FILE);
        if (!interventionFile) {
            Log::log(
                Log::Type::error,
                Log::Destination::stdout,
                "Server: Unable to open INTERVENTIONS_FILE for opening");
            cleanup(0);
            exit(1);
        }

        string line = "";

        while(getline(interventionFile, line)) {
            Log::log(
                Log::Type::success,
                Log::Destination::stdout,
                "Server: Reading from file: " + line);
        }
    }

    Log::log(
        Log::Type::success,
        Log::Destination::stdout,
        "idQ = " + std::to_string(idQ) + " : idM = " + std::to_string(idM));

    int idpath_finder;

    // Used to send the queue ID to the path_finder process as an argument to execl
    char BuffQ[20];
    sprintf(BuffQ, "%d", idQ);

    while (1) {
        // Get all requests identified by the type 1L sent by vehicles.
        if (msgrcv(idQ, &message, sizeof(Message) - sizeof(long), 1L, 0) == -1) {
            Log::log(
                Log::Type::error,
                Log::Destination::stdout,
                std::string("Server: Unable to receive message from message queue: ") + strerror(errno));
            exit(1);
        }

        Log::log(
            Log::Type::success,
            Log::Destination::stdout,
            "Server: Message received from " + std::to_string(message.idProcess));

        switch (message.request) {
            case REQUEST_SEARCH:
                Log::log(
                    Log::Type::success,
                    Log::Destination::stdout,
                    "Server: Message received is a REQUEST_SEARCH");

                if ((idpath_finder = fork()) == -1) {
                    Log::log(
                        Log::Type::error,
                        Log::Destination::stdout,
                        std::string("Server: Unable to fork to path_finder: ") + strerror(errno));
                    exit(1);
                }

                // The new fork will enter the branch and change the execution by path_finder
                if (!idpath_finder) {
                    execl("./path_finder", "path_finder", BuffQ, NULL);
                    Log::log(
                        Log::Type::error,
                        Log::Destination::stdout,
                        std::string("Server: Unable to replace process image by path_finder: ") + strerror(errno));
                    exit(1);
                }

                // Send a message via the message queue to the path finder
                // process. The latter will check if a message corresponding to
                // its pid is on the queue, remove it from the queue and put it
                // in a buffer.
                message.type = idpath_finder;

                if (msgsnd(idQ, &message, sizeof(Message) - sizeof(long), 0) == -1) {
                    Log::log(
                        Log::Type::error,
                        Log::Destination::stdout,
                        std::string("Server: Unable to send a message to message queue: ") + strerror(errno));
                    exit(1);
                }

                break;

            case REQUEST_VEHICLE_STATE_REPORT:
                Log::log(
                    Log::Type::success,
                    Log::Destination::stdout,
                    "Server: Message received is a REQUEST_VEHICLE_STATE_REPORT");

                switch (message.start) {


                    case VEHICLE_PAUSING:
                        Log::log(
                            Log::Type::success,
                            Log::Destination::stdout,
                            "Server: Vehicle ("
                            + std::to_string(message.idProcess)
                            + ") is currently pausing.");
                        break;

                    case VEHICLE_TRAVELLING:
                        Log::log(
                            Log::Type::success,
                            Log::Destination::stdout,
                            "Server: Vehicle ("
                            + std::to_string(message.idProcess)
                            + ") is currently travelling.");
                        break;

                    case VEHICLE_OPERATING:
                        Log::log(
                            Log::Type::success,
                            Log::Destination::stdout,
                            "Server: Vehicle ("
                            + std::to_string(message.idProcess)
                            + ") is currently operating.");
                        break;

                    case VEHICLE_BACK_DEPOT:
                        Log::log(
                            Log::Type::success,
                            Log::Destination::stdout,
                            "Server: Vehicle ("
                            + std::to_string(message.idProcess)
                            + ") is currently back at the depot.");
                        break;

                    default:
                        Log::log(
                            Log::Type::warning,
                            Log::Destination::stdout,
                            "Server: Vehicle ("
                            + std::to_string(message.idProcess)
                            + ") reported an unrecognized state.");
                }

                break;
                
        }

    }
}

void cleanup(int) {

    if (idQ == -1){
        Log::log(
            Log::Type::success,
            Log::Destination::stdout,
            "Message queue does not exist. Unneeded to clean.");
        return;
    }

    if (msgctl(idQ, IPC_RMID, NULL)) {
        Log::log(
            Log::Type::error,
            Log::Destination::stdout,
            "Message queue failed to be removed.");
        return;
    }

    Log::log(
        Log::Type::success,
        Log::Destination::stdout,
        "Message queue removed with successful.");
}
