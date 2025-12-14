#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    char buffer[100];

    pipe(fd);  // create pipe

    if (fork() == 0) {
        // CHILD PROCESS 👶
        close(fd[1]);  // close write end
        read(fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(fd[0]);
    } else {
        // PARENT PROCESS 👨
        close(fd[0]);  // close read end
        char msg[] = "Hello from Parent";
        write(fd[1], msg, strlen(msg) + 1);
        close(fd[1]);
    }
    return 0;
}
