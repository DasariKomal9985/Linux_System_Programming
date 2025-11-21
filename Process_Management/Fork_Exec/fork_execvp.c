#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {

    pid_t pid = fork();

    if (pid == 0) {
        char *args[] = {"ls", "-l", NULL};
        execvp("ls", args);
        perror("execvp failed");
    }
    else {
        wait(NULL);
        printf("Parent waiting complete.\n");
    }
}

