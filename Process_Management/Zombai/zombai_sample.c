#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child: I am dying now...\n");
        return 0;
    }
    else {
        printf("Parent: I will not wait. Child becomes zombie.\n");
        sleep(10); // During this, check 'ps'
    }
}

