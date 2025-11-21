#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child
        printf("Child: initial parent = %d\n", getppid());
        sleep(3);   // parent will exit before this
        printf("Child: new parent after orphan = %d\n", getppid());
    }
    else {
        // Parent
        printf("Parent: my PID = %d, exiting now...\n", getpid());
        sleep(1);
    }
    return 0;
}

