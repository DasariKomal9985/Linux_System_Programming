#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    printf("Running execvp...\n");

    // Pass the program's argv directly to ls
    // Example: ./a.out -l   => runs ls -l
    execvp("ls", argv);

    perror("execvp failed");
    return 0;
}

