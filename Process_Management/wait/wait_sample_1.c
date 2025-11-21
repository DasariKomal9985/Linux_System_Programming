#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child: I am child process\n");
        sleep(2);
        printf("Child: I am done\n");
    }
    else {
        printf("Parent: Waiting for child...\n");
        wait(NULL);
        printf("Parent: Child completed.\n");
    }
}

