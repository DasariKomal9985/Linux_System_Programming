#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        execl("/bin/ls", "ls", NULL);
        perror("execl failed");
    }
    else if (pid > 0) {
        // Parent process
        wait(NULL);  // wait for child
        printf("Parent: child completed.\n");
    }
    else {
        perror("fork failed");
    }
}

