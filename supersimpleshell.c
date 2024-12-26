#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LENGTH 1024

int main() {
    char command[MAX_CMD_LENGTH];

    while (1) {
        printf("#cisfun$ ");
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;  
        }

        
        command[strcspn(command, "\n")] = 0;

        
        if (strcmp(command, "exit") == 0) {
            break;

        } else if (strcmp(command, "ppid") == 0) {
            printf("%d\n", getppid());

        } else if (strcmp(command, "pid") == 0) {
            printf("%d\n", getpid());

        } else {
            
            pid_t pid = fork();
            if (pid == 0) {
                
                char *args[] = {command, NULL};
                execvp(command, args);
                
                perror("Error executing command");
                exit(1);
            } else if (pid > 0) {
                
                wait(NULL);
            } else {
                
                perror("Fork failed");
                exit(1);
            }
        }
    }

    return 0;
}

