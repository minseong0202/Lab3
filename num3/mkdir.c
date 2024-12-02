#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h> 

void mkdir_test(int arg_num, char **arg_list) {
    if (arg_num < 2) {
        printf("디렉토리명을 작성하세요\n");
    } else {
        if (mkdir(arg_list[1], 0755) == -1) {
            if (errno == EEXIST) {
                printf("디렉토리가 이미 존재\n");
            } else {
                printf("오류 발생\n");
            }
        } else {
            printf("디렉토리 생성\n");
        }
    }
}

int main(int argc, char *argv[]) {
    mkdir_test(argc, argv);
    return 0;
}

