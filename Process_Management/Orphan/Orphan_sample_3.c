#include <stdio.h>
#include <unistd.h>

int main() {
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            printf("Child %d: initial parent = %d\n", i, getppid());
            sleep(5);
            printf("Child %d: new parent = %d\n", i, getppid());
            return 0;
        }
    }

    printf("Parent exiting immediately...\n");
    return 0;
}

