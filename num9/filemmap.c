#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define STRLEN 10

int main() {
    int fd, pid;
    char *mem;
    char buf[] = "Hello";

    fd = open("testmmap", O_RDWR | O_CREAT, 0666);
    ftruncate(fd, STRLEN);
    printf("parent: file open successfully\n");

    pid = fork();
    if (pid == 0) { // 자식 프로세스
        mem = mmap(NULL, STRLEN, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
        memcpy(mem, buf, strlen(buf) + 1);  // null 종료 문자까지 복사
        printf("child: unmapping\n");
        munmap(mem, STRLEN);
    } else if (pid > 0) { // 부모 프로세스
        sleep(2);
        wait(NULL);
        mem = mmap(NULL, STRLEN, PROT_READ, MAP_SHARED, fd, 0);
        printf("parent: buf = %s\n", mem);
        munmap(mem, STRLEN);
    } else {
        perror("fork failed");
    }

    close(fd);
    return 0;
}

