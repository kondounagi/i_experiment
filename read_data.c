#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void die(char * s) {
    perror(s);
    exit(1);
}

int main(int argc, char ** argv) {
    int fd = open(argv[1], O_RDONLY, 0644);
    if (fd == -1) die("open");
    int i = 0;
    while (1) {
        char data[1];
        int n = read(fd, data, 1);
        if (n == -1) die("open");
        if (n == 0) break;
        printf("%d %d\n", i, (unsigned char)data[0]);
        i++;
    }
    close(fd);
}

