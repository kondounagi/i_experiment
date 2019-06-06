#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void die(char * s) {
    perror(s);
    exit(1);
}

int main(int argc, char ** argv) {
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) die("open");
    int n = 256;
    int a[n];
    for (int i = 0; i < 256; i++) {
        a[i] = i;
    }
    if (write(fd, a, n) == -1) die("open");
    close(fd);
}

