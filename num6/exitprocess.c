#include <stdio.h>
#include <stdlib.h>

int main() {
    int exit_status;
    printf("Enter exit status: ");
    scanf("%d", &exit_status);
    exit(exit_status);
}

