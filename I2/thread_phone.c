#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#define BUF 4096

void* send_from_stdin(int* s) {
    int n;
    char send_data[BUF];
    while (true) {
        n = read(0, send_data, sizeof(send_data));
        if (n > 0) {
            int snd = send(*s, send_data, sizeof(send_data), 0);
            if (snd == -1) {
                fprintf(stderr, "send error\n");
                exit(0);
            }
        }
    }
}


void* recieve_to_stdout(int* s) {
    int r;
    char recieved_data[BUF];
    while (true) {
        r = recv(*s, recieved_data, sizeof(recieved_data), 0);
        if (r > 0) {
            int wrt = write(1, recieved_data, sizeof(recieved_data));
            if (wrt == -1) {
                fprintf(stderr, "write error!\n");
                exit(0);
            }
        }
    }
}


int main(int argc, char* argv[]){

    // build socket
    int s;
    int* s_pointer = &s;
    if (argc == 2) {
        int ss = socket(PF_INET, SOCK_STREAM, 0);
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(atoi(argv[1]));
        addr.sin_addr.s_addr = INADDR_ANY;
        bind(ss, (struct sockaddr *)&addr, sizeof(addr));
        listen(ss, 10);
        struct sockaddr_in client_addr;
        socklen_t len = sizeof(struct sockaddr_in);
        s = accept(ss, (struct sockaddr *)&client_addr, &len);
        if (s < 0) {
            fprintf(stderr, "connection failed!!\n");
            exit(0);
        }
        close(ss);
    } else if (argc == 3) {
        s = socket(PF_INET, SOCK_STREAM, 0);
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(argv[1]);
        addr.sin_port = htons(atoi(argv[2]));
        int ret = connect(s, (struct sockaddr *)&addr, sizeof(addr));
        if (ret != 0) {
            fprintf(stderr, "connection failed !!!\n");
        }
    } else {
        fprintf(stderr, "please check args\n");
    }

    // build threads
    pthread_t send_thread, recieve_thread;
    int send_thread_id, recieve_thread_id;

    int ret1 = send_thread_id = pthread_create(
            &send_thread,
            NULL,
            (void *)send_from_stdin,
            s_pointer
    );

    int ret2 = recieve_thread_id = pthread_create(
            &recieve_thread,
            NULL,
            (void *)recieve_to_stdout,
            s_pointer
    );

    if (ret1 != 0) {
        err(EXIT_FAILURE, "can not create thread 1: %s", strerror(ret1));
    }
    if (ret2 != 0) {
        err(EXIT_FAILURE, "can not create thread 2: %s", strerror(ret2) );
    }

    fprintf(stderr, "datasend finished.\n");
    close(s);
    return 0;
}
