#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    pid_t pid;
    int status, exit_status;

    if ((pid = fork()) < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) { 
        sleep(4);
        exit(5);
    }

    while (waitpid(pid, &status, WNOHANG) == 0) {
        printf("still waiting...\n");
        sleep(1);
    }

    if (WIFEXITED(status)) {
        exit_status = WEXITSTATUS(status);
        printf("Exit status from %d was %d\n", pid, exit_status);
    }

    exit(0);
}

