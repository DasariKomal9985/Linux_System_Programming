#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>

int main() {

    printf("Running execvpe...\n");

    char *args[] = {"env", NULL};
    char *env[]  = {"USER=KOMAL", "MESSAGE=HELLO", NULL};

    execvpe("env", args, env);

    perror("execvpe failed");
    return 0;
}

