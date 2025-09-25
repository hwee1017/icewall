#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
    char buf[200];
    while(1){
        printf(">>>> ");
        fflush(stdout);
        if(fgets(buf,sizeof(buf),stdin) == NULL){
            continue;
        }
        buf[strcspn(buf,"\n")] = 0;
        char* argv[20];
        int i = 0;
        char* token = strtok(buf," ");
        while(token != NULL){
            argv[i++] = token;
            token = strtok(NULL," ");
        }
        argv[i] = NULL;
        if(argv[0] == NULL){
            continue;
        }
        if(strcmp(argv[0],"exit") == 0){
            break;
        }
        if(strcmp(argv[0],"cd") == 0){
            if(argv[1] == NULL){
                fprintf(stderr,"cd : please enter directory name\n");
            }
            else if(chdir(argv[1]) != 0){
                perror("cd");
            }
            continue;
        }
        pid_t pid = fork();
        if(pid == 0){
            execvp(argv[0],argv);
            perror("execvp");
            exit(1);
        }
        else if(pid > 0){
            wait(0);
        }
        else{
            perror("fork");
        }
    }
    return 0;
}