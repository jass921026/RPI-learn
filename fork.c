#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
    printf("Hello\n");
    char command[100];
    while(1){
        printf("Please enter command: ");
        scanf("%s", command);
        if (strcmp(command, "q") == 0){
            printf("bye\n");
            break;
        } else if (strcmp(command, "ls") == 0){
            pid_t pid = fork();
            if (pid == 0){
                int ret = execlp("/bin/ls", "ls", NULL);
                if (ret == -1) {
                    perror("execlp error");
                    exit(0);
                }
            } else{
                wait(NULL);
            }
        } else if (strcmp(command, "a") == 0){
            pid_t pid = fork();
            if (pid == 0) { // child process
                int ret = execlp("./a.out", "a.out", NULL);
                if (ret == -1){ // something's wrong...
                    perror("execlp error");
                }
                exit(0);
            } else{
                wait(NULL);
            }
        } else {
            printf("Your command is: %s\n", command);
            printf("IDK what to do...\n");
        }
        
    }
    // pid = fork();
    // if (pid == 0){

    // }
    return 0;
}