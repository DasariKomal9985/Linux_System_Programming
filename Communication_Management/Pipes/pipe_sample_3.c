#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int p2c[2];  // parent to child
    int c2p[2];  // child to parent

    pipe(p2c);
    pipe(c2p);

    pid_t pid = fork();

    if (pid == 0) {
        // CHILD
        char msg[50];

        close(p2c[1]);  // close write end of p2c
        read(p2c[0], msg, 50);
        printf("Child got: %s\n", msg);

        close(c2p[0]);  // close read end of c2p
        write(c2p[1], "Hello Parent!", 14);
    }
    else {
        // PARENT
        char msg[50];

        close(p2c[0]); 
        write(p2c[1], "Hello Child!", 13);

        close(c2p[1]);
        read(c2p[0], msg, 50);
        printf("Parent got: %s\n", msg);
    }
}

