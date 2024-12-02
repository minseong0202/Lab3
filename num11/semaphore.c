#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/sem.h>
#include "semaphore.h"

#define SHM_SIZE 1024

struct sembuf sb;

void copy_file_to_shared_memory(const char *source_filename, void *shared_memory, int semid) {
    int source_file = open(source_filename, O_RDONLY);
    if (source_file == -1) {
        perror("source file open error");
        exit(1);
    }

    sb.sem_num = 0;
    sb.sem_op = -1;
    sb.sem_flg = 0;
    if (semop(semid, &sb, 1) == -1) {
        perror("semop error (lock)");
        exit(1);
    }

    ssize_t bytes_read = read(source_file, shared_memory, SHM_SIZE);
    if (bytes_read == -1) {
        perror("file read error");
        close(source_file);
        exit(1);
    }

    printf("읽은 바이트 수: %ld\n", bytes_read);

    close(source_file);

    sb.sem_op = 1;
    if (semop(semid, &sb, 1) == -1) {
        perror("semop error (unlock)");
        exit(1);
    }
}

void copy_from_shared_memory_to_file(const char *destination_filename, void *shared_memory, int semid) {
    sb.sem_num = 0;
    sb.sem_op = -1;
    sb.sem_flg = 0;
    if (semop(semid, &sb, 1) == -1) {
        perror("semop error (lock)");
        exit(1);
    }

    int dest_file = open(destination_filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (dest_file == -1) {
        perror("destination file open error");
        exit(1);
    }

    ssize_t bytes_written = write(dest_file, shared_memory, SHM_SIZE);
    if (bytes_written == -1) {
        perror("file write error");
        close(dest_file);
        exit(1);
    }

    close(dest_file);

    sb.sem_op = 1;
    if (semop(semid, &sb, 1) == -1) {
        perror("semop error (unlock)");
        exit(1);
    }
}

