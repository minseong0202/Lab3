#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include "semaphore.h"

#define SHM_SIZE 1024

int main() {
    const char *source_filename = "hello.txt";
    const char *destination_filename = "semaphore.txt";

    key_t key = ftok(".", 'R');
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget error");
        exit(1);
    }

    void *shared_memory = shmat(shmid, NULL, 0);
    if (shared_memory == (void *)-1) {
        perror("shmat error");
        exit(1);
    }

    key_t sem_key = ftok(".", 'S');
    int semid = semget(sem_key, 1, 0666 | IPC_CREAT);
    if (semid == -1) {
        perror("semget error");
        exit(1);
    }

    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror("semctl error (init)");
        exit(1);
    }

    if (fork() == 0) {
        copy_file_to_shared_memory(source_filename, shared_memory, semid);
        exit(0);
    }

    if (fork() == 0) {
        copy_from_shared_memory_to_file(destination_filename, shared_memory, semid);
        exit(0);
    }

    wait(NULL);
    wait(NULL);

    if (shmdt(shared_memory) == -1) {
        perror("shmdt error");
        exit(1);
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl error");
        exit(1);
    }

    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl error (delete)");
        exit(1);
    }

    printf("파일 복사 완료!\n");

    return 0;
}

