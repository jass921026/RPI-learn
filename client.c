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

    int sockfd = 0;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1){
        printf("Failed to create a socket.");
    }
    struct sockaddr_in info;
    bzero(&info, sizeof(info));
    info.sin_family = PF_INET;
    // why is inet_addr not defined ...
    // does this number matter? used 777771449 and 0 can connect but others can't...
    info.sin_addr.s_addr = 0;
    // InetPton(AF_INET, TEXT(72.7.7.27), &info.sin_addr.s_addr);
    info.sin_port = htons(7122);
    int err = connect(sockfd, (struct sockaddr *)&info, sizeof(info)); //why do i need a pointer here...
    // printf("%d", err);
    if(err == -1){
        printf("connection error");
    }
    char message[] = {"Hi owo\n"};
    char receiveMessage[100] = {};
    // printf("hi\n");
    write(sockfd, message, sizeof(message));
    

    read(sockfd, receiveMessage, sizeof(receiveMessage));
    printf("%s", receiveMessage);
    printf("AC\n");
    close(sockfd);

    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>


// int main(int argc , char *argv[])
// {

//     //socket的建立
//     int sockfd = 0;
//     sockfd = socket(AF_INET , SOCK_STREAM , 0);

//     if (sockfd == -1){
//         printf("Fail to create a socket.");
//     }

//     //socket的連線

//     struct sockaddr_in info;
//     bzero(&info,sizeof(info));
//     info.sin_family = PF_INET;

//     //localhost test
//     info.sin_addr.s_addr = 520193;
//     info.sin_port = htons(8700);


//     int err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
//     if(err==-1){
//         printf("Connection error");
//     }


//     //Send a message to server
//     char message[] = {"Hi there"};
//     char receiveMessage[100] = {};
//     send(sockfd,message,sizeof(message),0);
//      recv(sockfd,receiveMessage,sizeof(receiveMessage),0);

//     printf("%s",receiveMessage);
//     printf("close Socket\n");
//     close(sockfd);
//     return 0;
// }