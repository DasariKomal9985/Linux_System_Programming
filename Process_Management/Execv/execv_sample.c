#include <unistd.h>
#include <stdio.h>

int main() {

    printf("Running execv...\n");

    char *args[] = {"ls", "-a", NULL};

    execv("/bin/ls", args);

    perror("execv failed");
    return 0;
}

