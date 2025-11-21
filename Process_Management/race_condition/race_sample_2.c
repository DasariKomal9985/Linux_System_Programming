#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("race.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fork() == 0) {
        write(fd, "AAAAA\n", 6);
    } else {
        write(fd, "BBBBB\n", 6);
    }

    close(fd);
}

