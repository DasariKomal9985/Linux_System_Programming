#include <stdio.h>
#include <unistd.h>

int main() {
    int fd[2];
    char buffer[50];

    pipe(fd);    // create pipe

    pid_t pid = fork();

    if (pid == 0) {
        // Child
        close(fd[1]); // close write end
        read(fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(fd[0]);
    }
    else {
        // Parent
        close(fd[0]); // close read end
        write(fd[1], "Hello from Parent", 18);
        close(fd[1]);
    }
}

