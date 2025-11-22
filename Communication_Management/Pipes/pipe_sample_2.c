#include <stdio.h>
#include <unistd.h>

int main() {
    int fd[2];
    char buffer[50];

    pipe(fd);
    pid_t pid = fork();

    if (pid == 0) {
        close(fd[0]);  // close read end
        write(fd[1], "Hello from Child", 17);
        close(fd[1]);
    }
    else {
        close(fd[1]);  // close write end
        read(fd[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);
        close(fd[0]);
    }
}

