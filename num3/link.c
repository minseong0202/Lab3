#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char cmd;
    char *src;
    char *target;

    
    if (argc < 3) {
        fprintf(stderr, "Usage: file_link [l,u,s] ...\n");
        fprintf(stderr, " file_link l[ink] src target\n");
        fprintf(stderr, " file_link u[nlink] filename\n");
        fprintf(stderr, " file_link s[ymlink] src target\n");
        exit(1);
    }

    
    cmd = argv[1][0];

    if (cmd == 'l') { 
        if (argc < 4) {
            fprintf(stderr, "Usage: file_link l src target\n");
            exit(1);
        }
        src = argv[2];
        target = argv[3];
        if (link(src, target) < 0) {
            perror("link");
            exit(1);
        }
    } else if (cmd == 's') { 
        if (argc < 4) {
            fprintf(stderr, "Usage: file_link s src target\n");
            exit(1);
        }
        src = argv[2];
        target = argv[3];
        if (symlink(src, target) < 0) {
            perror("symlink");
            exit(1);
        }
    } else if (cmd == 'u') { 
        src = argv[2];
        if (unlink(src) < 0) {
            perror("unlink");
            exit(1);
        }
    } else {
        fprintf(stderr, "에러 발생.\n");
        exit(1);
    }

    return 0;
}

