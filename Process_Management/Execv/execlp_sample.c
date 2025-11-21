#include <unistd.h>
#include <stdio.h>

int main() {

    printf("Running execlp...\n");

    // Finds 'ls' in PATH
    execlp("ls", "ls", "-lh", NULL);

    perror("execlp failed");
    return 0;
}

