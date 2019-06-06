#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void die(char * s) {
    perror(s);
    exit(1);
}

int main(int argc, char ** argv) {
    if (argc != 2) die("give me 1 arg");
    int thin_rate = atoi(argv[1]);

    int count = 0;

    while (1) {
        int16_t data[1];
        int n = read(0, data, sizeof(int16_t));

        if (n == -1) die("read");
        if (n == 0) break;

        if (count % thin_rate == 0) {
            write(1, data, sizeof(int16_t));
        }

        count++;
    }
}

