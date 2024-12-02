#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int execute_command(const char *cmd) {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("자식 프로세스 생성 실패");
        exit(1);
    }

    if (child_pid == 0) {
        char *command_args[] = {"/bin/sh", "-c", (char *)cmd, NULL};
        execvp(command_args[0], command_args);

        perror("명령어 실행 실패");
        exit(1);
    } else {
        int status_code;
        pid_t completed_pid = waitpid(child_pid, &status_code, 0);

        if (completed_pid == -1) {
            perror("자식 프로세스 종료 대기 실패");
            exit(1);
        }

        if (WIFEXITED(status_code)) {
            return WEXITSTATUS(status_code);
        } else {
            exit(1);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("인자가 부족하다.\n");
        return 1;
    }

    char cmd_buffer[1024] = "";
    for (int i = 1; i < argc; i++) {
        strcat(cmd_buffer, argv[i]);
        if (i < argc - 1) {
            strcat(cmd_buffer, " ");
        }
    }

    int status_code = execute_command(cmd_buffer);

    if (status_code == 0) {
        printf("명령어가 성공적으로 실행\n");
    } else {
        printf("명령어 실행 실패\n");
    }

    return 0;
}

