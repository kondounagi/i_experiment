#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
    int s = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));
    int ret = connect(s, (struct sockaddr *)&addr, sizeof(addr));
    if(ret != 0){
        printf("connection failed!!\n");
        exit(0);
    }
    //char data[] = "abc";
    //int n = send(s, data, sizeof(data) , 0);
    // if(n < 0){
    //    printf("send failed!!\n");
    //    exit(0);
    //}
    char received_data[1];
    int r;
    while( r = recv(s, received_data, sizeof(received_data), 0) >0 ){
        //printf("receive!\n");
        //printf("r = %d\n", r);
        write(1, received_data, sizeof(received_data));
    
    }
    //int r = recv(s, received_data, sizeof())  
    return 0;
}