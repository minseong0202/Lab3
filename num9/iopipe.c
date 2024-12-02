#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 256

int main() {
    FILE *pin, *pout;
    char buf[BUFSIZE];

    pin = popen("who", "r");
    if (pin == NULL) {
        perror("popen for 'who' failed");
        exit(1);
    }

    pout = popen("wc -l", "w");
    if (pout == NULL) {
        perror("popen for 'wc -l' failed");
        pclose(pin);
        exit(1);
    }

    while (fgets(buf, BUFSIZE, pin) != NULL) {
        fputs(buf, pout);
    }

    pclose(pin);
    pclose(pout);

    return 0;
}

