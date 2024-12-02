#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

void rmdir_test(int arg_num, char **arg_list) {
    if (arg_num < 2) {
        printf("디렉토리 명을 작성하세요\n");
    } else {
        if (rmdir(arg_list[1]) == -1) {
            printf("디렉토리 삭제 실패\n");
        } else {
            printf("디렉토리 삭제 완료\n");
        }
    }
}

int main(int argc, char *argv[]) {
    rmdir_test(argc, argv);
    return 0;
}

