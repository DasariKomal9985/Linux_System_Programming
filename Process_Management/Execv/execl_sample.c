#include <unistd.h>
#include <stdio.h>

int main() {

    printf("Running execl...\n");

    // execl(path, arg0, arg1, ..., NULL)
    execl("/bin/ls", "ls", "-l", NULL);

    // Only runs if exec fails
    perror("execl failed");
    return 0;
}

