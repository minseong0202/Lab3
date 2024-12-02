#ifndef SEMAPHORE_H
#define SEMAPHORE_H

void copy_file_to_shared_memory(const char *source_filename, void *shared_memory, int semid);
void copy_from_shared_memory_to_file(const char *destination_filename, void *shared_memory, int semid);

#endif

