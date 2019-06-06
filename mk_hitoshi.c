#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd = open("hitoshi", O_WRONLY | O_CREAT, 0644);
    printf("%d", fd);
    int n = 6;
    char a[6];
    a[0] = 228;
    a[1] = 186;
    a[2] = 186;
    a[3] = 229;
    a[4] = 191;
    a[5] = 151;
    write(fd, a, n);
    close(fd);
}