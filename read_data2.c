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
    int fd = open(argv[1], O_RDONLY, 0644);
    if (fd == -1) die("open");
    int i = 0;
    int16_t data[1];

    while (1) {
        int n = read(fd, data, sizeof(int16_t));
        if (n == -1) die("open");
        if (n == 0) break;
        printf("%d %d\n", i, (int16_t)data[0]);
        i++;
    }
    close(fd);
    return 0;
}

