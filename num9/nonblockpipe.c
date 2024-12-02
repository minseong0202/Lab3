#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSGSIZE 16

char *parent_name = "parent";
char *child_name = "child";
char *parent_msg = "Hello, child!";
char *child_msg = "Hello, parent!";

void nonblock_rw(char *name, int read_fd, int write_fd, char *msg);

int main() {
    int pp[2][2], i;
    int pid;

    for (i = 0; i < 2; i++) {
        if (pipe(pp[i]) == -1) {
            perror("pipe call failed");
            exit(1);
        }
    }

    pid = fork();
    if (pid == 0) {  
        close(pp[0][1]);
        close(pp[1][0]);
        nonblock_rw(child_name, pp[0][0], pp[1][1], child_msg);
    } else if (pid > 0) {
        close(pp[0][0]);
        close(pp[1][1]);
        nonblock_rw(parent_name, pp[1][0], pp[0][1], parent_msg);
    } else {
        perror("fork failed");
    }

    return 0;
}

void nonblock_rw(char *name, int read_fd, int write_fd, char *msg) {
    char buf[MSGSIZE];
    int flags;

    flags = fcntl(read_fd, F_GETFL, 0);
    fcntl(read_fd, F_SETFL, flags | O_NONBLOCK);

    flags = fcntl(write_fd, F_GETFL, 0);
    fcntl(write_fd, F_SETFL, flags | O_NONBLOCK);

    while (1) {
        if (read(read_fd, buf, MSGSIZE) > 0) {
            printf("%s received: %s\n", name, buf);
        }

        if (write(write_fd, msg, strlen(msg) + 1) < 0 && errno != EAGAIN) {
            perror("write failed");
            break;
        }

        sleep(1);
    }
}

