#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
// #include<WS2tcpip.h>
//no headfile???

int main(int argc, char *argv[]){

    int sockfd = 0, ip = 0;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1){
        printf("Failed to create a socket.");
    }
    struct sockaddr_in info;
    bzero(&info, sizeof(info));
    info.sin_family = PF_INET;
    printf("Please input ip: ");
    scanf("%d", &ip);
    info.sin_addr.s_addr = ip;
    info.sin_port = htons(7122);
    int err = connect(sockfd, (struct sockaddr *)&info, sizeof(info)); //why do i need a pointer here...
    // printf("%d", err);
    if(err == -1){
        printf("connection error");
    }
    char message[256] = {};
    char receiveMessage[256] = {};

    // recv(sockfd, receiveMessage, sizeof(receiveMessage), 0);
    // printf("%s", receiveMessage);
    while (1){
        recv(sockfd, receiveMessage, sizeof(receiveMessage), 0);
        printf("%s", receiveMessage);
        if (strcmp(receiveMessage, "bye\n") == 0){
            break;
        }
        scanf("%s", message);
        send(sockfd, message, sizeof(message), 0);
    }
    close(sockfd);

    return 0;
}
