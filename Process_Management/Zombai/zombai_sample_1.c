#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child: I am dead\n");
        return 0;
    }
    else {
        int status;
        wait(&status);
        printf("Parent: cleaned child\n");
        sleep(5);
    }
}

