#include <unistd.h>
#include <stdio.h>

int main() {

    printf("Running execve...\n");

    char *args[] = {"echo", "Hello from execve", NULL};
    char *env[]  = {NULL};

    execve("/bin/echo", args, env);

    perror("execve failed");
    return 0;
}

