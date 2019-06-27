//本課題6.1 のclient_recv.cを改良した
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
    int s = socket(PF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));
    //int ret = connect(s, (struct sockaddr *)&addr, sizeof(addr));
    //if(ret != 0){
    //    fprintf(stderr, "connection failed!!\n");
    //    exit(0);
    //}
    
    char send_data[1];
    int n;
    send_data[0] = 'a';
    //while ((n = read(0, send_data, sizeof(send_data))) != 0) {
    int snd = sendto(s, send_data, sizeof(send_data), 0, (struct sockaddr * )&addr, sizeof(addr));
    if(snd == -1) {
        fprintf(stderr, "send error\n");
        exit(0);
    }
    //}
    fprintf(stderr, "datasend finished.\n");
    shutdown(s, SHUT_WR);
    char received_data[1];
    int r;
    fprintf(stderr, "start receiving\n");
    while( r = recvfrom(s, received_data, sizeof(received_data), 0, (struct sockaddr * )&addr, sizeof(addr)) >0 ){
        int wrt = write(1, received_data, sizeof(received_data));
        if(wrt == -1){
            fprintf(stderr, "write error!\n");
            exit(0);
        }
    }
    fprintf(stderr, "receiving finished.\n");
    return 0;
}