#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 16
#define QKEY (key_t)0111

struct msgq_data {
    long type;
    char text[BUFSIZE];
};

int main() {
    int qid;
    struct msgq_data send_data = {1, "Hello, world"};

    qid = msgget(QKEY, IPC_CREAT | 0666);
    if (qid == -1) {
        perror("msgget failed");
        exit(1);
    }

    if (msgsnd(qid, &send_data, strlen(send_data.text), 0) == -1) {
        perror("msgsnd failed");
        exit(1);
    }

    printf("Message sent: %s\n", send_data.text);
    return 0;
}

