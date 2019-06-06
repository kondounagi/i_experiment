#include <unistd.h>
#include <fcntl.h>

int main(int argc, char ** argv) {
    int fd = open(argv[1], O_WRONLY | O_CREAT |O_TRUNC, 0644);
    int n = 256;
    int a[n];
    for (int i = 0; i < 256; i++) {
        a[i] = i;
    }
    write(fd, a, n);
    close(fd);
}

