#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include "chat.h"

void start_chat(const char *username, int send_id, int receive_id) {
    struct message msg;

    while (1) {
       
        if (msgrcv(receive_id, &msg, sizeof(msg) - sizeof(long), 1, 0) != -1) {
            printf("\n%s: %s\n", msg.sender, msg.text);
            if (strcmp(msg.text, "exit") == 0) {
                printf("채팅 종료\n");
                break;
            }
        }

        
        printf("%s: ", username);
        fgets(msg.text, MAX_TEXT, stdin);
        msg.text[strcspn(msg.text, "\n")] = '\0';
        strncpy(msg.sender, username, MAX_TEXT);
        msg.message_type = 1;

        msgsnd(send_id, &msg, sizeof(msg) - sizeof(long), 0);

        if (strcmp(msg.text, "exit") == 0) {
            printf("채팅 종료\n");
            break;
        }
    }
}

