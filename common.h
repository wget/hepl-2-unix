#define MAX 20
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
    int message[MAX];
} MessageMax;

typedef struct {
    long type;
    pid_t idProcess;
    int request;
    char Texte[80];
} MessageSent;

#define REQUEST_SEARCH                 1
#define REQUEST_IDENTIFICATION_MANAGER 2
#define REQUEST_IDENTIFICATION_VEHICLE 3
#define REQUEST_NUM_VEHICLE            4
#define REQUEST_STOP                   5

