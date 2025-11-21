#include <unistd.h>
#include <stdio.h>

int main() {
    execl("/bin/ls", "ls", "-l", NULL);

    // If this executes, exec failed
    perror("execl failed");
}

