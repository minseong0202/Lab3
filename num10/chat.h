#ifndef CHAT_H
#define CHAT_H

#define MAX_TEXT 512

struct message {
    long message_type;
    char sender[MAX_TEXT];
    char text[MAX_TEXT];
};

void start_chat(const char *username, int send_id, int receive_id);

#endif

