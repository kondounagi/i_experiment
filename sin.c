#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _USE_MATH_DEFINES

void die(char * s) {
    perror(s);
    exit(1);
}

int main(int argc, char ** argv) {
    if (argc != 4) die("please input 4 args\n");
    double a = atof(argv[1]);
    double f = atof(argv[2]);
    int n = atoi(argv[3]);

    __int16_t sin_array[n];
    for (int t = 0; t < n; t++) {
        sin_array[t] = (__int16_t)(a * sin(2 * M_PI * f * (double)t / (double)44100));
    }
        write(1, sin_array, n*sizeof(__int16_t));
}
