#ifndef COMMON_H
#define COMMON_H
#include <unistd.h>

// According to instructions, the depot is reported to be at A4, which
// is the 3rd column in the global stations[] variable table.
#define DEPOT_LOCATION 3

#define REQUEST_MESSAGE_MAX_PATH 20
#define REQUEST_MESSAGE_MAX 80
#define MSG_QUEUE_KEY (key_t)1234

typedef struct {
    long type;
    pid_t idProcess;
    int request;
    int start;
} Message;

typedef struct {
    long type;
    pid_t idProcess;
    int request;
    int message[REQUEST_MESSAGE_MAX_PATH];
} MessageMax;

typedef struct {
    long type;
    pid_t idProcess;
    int request;
    char text[REQUEST_MESSAGE_MAX];
} MessageSent;

typedef struct {
    int location;
    char locationName[20];
    int executed;
} InterventionRecord;

typedef enum {
    VEHICLE_TRAVELLING,
    VEHICLE_OPERATING,
    VEHICLE_PAUSING,
    VEHICLE_BACK_DEPOT
} VehicleState;

#define INTERVENTIONS_FILE "interventions.txt"
// The code does not support separator with multi characters
#define INTERVENTIONS_FILE_SEPARATOR ";"

#define REQUEST_SEARCH                 1
#define REQUEST_VEHICLE_STATE_REPORT   2
#define REQUEST_IDENTIFICATION_MANAGER 3
#define REQUEST_NUM_VEHICLE            4
#define REQUEST_STOP                   5

#endif // COMMON_H
