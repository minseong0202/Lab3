#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "chat.h"

int main() {
    key_t key_send = ftok("sendfile", 65);
    key_t key_receive = ftok("receivefile", 66);

    int msgid_send = msgget(key_send, 0666 | IPC_CREAT);
    int msgid_receive = msgget(key_receive, 0666 | IPC_CREAT);

    printf("1: 홍길동 , 2: 김민성 : ");
    int choice;
    scanf("%d", &choice);
    getchar(); // 개행 문자 제거

    if (choice == 1) {
        start_chat("홍길동", msgid_send, msgid_receive);
    } else if (choice == 2) {
        start_chat("김민성", msgid_receive, msgid_send);
    } else {
        printf("잘못된 선택\n");
    }

    msgctl(msgid_send, IPC_RMID, NULL);
    msgctl(msgid_receive, IPC_RMID, NULL);

    return 0;
}

