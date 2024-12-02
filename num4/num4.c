#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

void list_directory_recursive(const char *path) {
    DIR *dir = opendir(path);
    struct dirent *entry;
    struct stat statbuf;
    
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    
    printf("현재 디렉토리: %s\n", path);

    
    while ((entry = readdir(dir)) != NULL) {
       
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

       
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        
       
        if (stat(full_path, &statbuf) == 0) {
            
            if (S_ISDIR(statbuf.st_mode)) {
                printf("%s/\n", entry->d_name);  
                list_directory_recursive(full_path); 
            } else {
                printf("%s\n", entry->d_name); 
            }
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "에러\n");
        return 1;
    }

    list_directory_recursive(argv[1]); 
    return 0;
}

