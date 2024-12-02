#include <stdio.h>
#include <string.h>
#include <time.h>

int main() {
    char correct_input[100];
    char real_input[100];
    int wrong = 0;
    int total = 0;
    time_t start_time, end_time;

    printf("타자 연습 프로그램 시작(exit 치면 종료)\n");

    while (1) {
        printf("입력할 문장: \n");
        fgets(real_input, sizeof(real_input), stdin);

        if (strncmp(real_input, "exit", 4) == 0) {
            break;
        }

        printf("올바른 문장 입력: \n");
        fgets(correct_input, sizeof(correct_input), stdin);

        correct_input[strcspn(correct_input, "\n")] = '\0';
        real_input[strcspn(real_input, "\n")] = '\0';

        time(&start_time);

        wrong = 0;
        for (int i = 0; i < strlen(correct_input); i++) {
            if (real_input[i] != correct_input[i]) {
                wrong++;
            }
        }

        total += strlen(real_input);

        time(&end_time);

        double time_taken = difftime(end_time, start_time);

        double minute = 0;
        if (time_taken > 0) {
            minute = (total / 5.0) / (time_taken / 60.0);
        }

        printf("잘못 타이핑한 횟수: %d\n", wrong);
        printf("현재 분당 타자수: %.1f 분\n", minute);
    }

    printf("타자 연습 종료\n");

    return 0;
}

