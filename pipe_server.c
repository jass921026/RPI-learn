#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<netinet/in.h>

// 遇到的問題
// socket連續兩次send或receive好像會出事
// 在client那裡按下Ctrl+C會把server也終止，這樣感覺不太好?
// 如果是向上周那樣在fork的child process用exec的話，要怎麼把輸出接到pipe?

int main(int argc, char* argv[]){
    char InputBuffer[256] = {};
    char message[] = "Hi I am server <3\n";
    int socket_fd = 0, for_client_socket_fd = 0;
    int pipe_fd[2];
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1){
        printf("Failed to create a socket.");
    }
    struct sockaddr_in serverInfo, clientInfo;
    bzero(&serverInfo, sizeof(serverInfo));
    unsigned int addrlen = sizeof(clientInfo);

    serverInfo.sin_family = AF_INET;
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(7122);
    bind(socket_fd, (struct sockaddr*)&serverInfo, sizeof(serverInfo));
    listen(socket_fd, 5);

    while(1){
        printf("My ip:%d\n", serverInfo.sin_addr.s_addr);
        for_client_socket_fd = accept(socket_fd, (struct sockaddr*)&clientInfo, &addrlen);
        // send(for_client_socket_fd, message, sizeof(message), 0);
        // 感覺連續兩次send會出事??
        char message[] = "Please enter command: ", command[256] = {};
        send(for_client_socket_fd, message, sizeof(message), 0);
        printf("message sent!\n");

        while(1){
            recv(for_client_socket_fd, command, sizeof(command), 0);
            if (strcmp(command, "q") == 0){
                send(for_client_socket_fd, "bye\n", 256, 0);
                break;
            // } else if (strcmp(command, "ls") == 0){ // how to use pipe in exec???
            //     pipe(pipe_fd);
            //     pid_t pid = fork();
            //     if (pid == 0){
            //         int ret = execlp("/bin/ls", "ls", NULL);
            //         if (ret == -1) {
            //             perror("execlp error");
            //             exit(0);
            //         }
            //     } else{
            //         wait(NULL);
            //     }
            } else if (strcmp(command, "a") == 0){
                pipe(pipe_fd);
                pid_t pid = fork();
                if (pid == 0) { // child process
                    close(pipe_fd[0]); // why 0 is read and 1 is write...
                    char message[] = "AAAAAAAAAAAAA\nPlease enter command: ";
                    write(pipe_fd[1], message, sizeof(message));
                    printf("child process write: ");
                    printf("%s\n", message);
                    close(pipe_fd[1]);
                    exit(0);
                } else{ // parent process
                    close(pipe_fd[1]);
                    char buffer[256] = {};
                    wait(NULL);
                    read(pipe_fd[0], buffer, sizeof(buffer));
                    printf("Get: %s", buffer);
                    send(for_client_socket_fd, buffer, sizeof(buffer), 0);
                    close(pipe_fd[0]);
                }
            } else {
                send(for_client_socket_fd, "IDK what to do...\nPlease enter command: ", 256, 0);
            }
        }

    }
    return 0;

}