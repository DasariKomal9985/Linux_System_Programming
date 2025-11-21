#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        sleep(5);   // Parent will exit before this
        printf("Child: My parent now is %d\n", getppid());
    }
    else {
        // Parent process
        printf("Parent: exiting now\n");
    }

    return 0;
}

