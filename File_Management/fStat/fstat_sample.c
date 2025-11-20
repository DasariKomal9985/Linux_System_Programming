/*  

fstat() gets file information using an already opened file descriptor (fd).

❓ Why to use fstat()?

Because sometimes you don’t have the filename, only file descriptor.

Examples:

stdin (fd = 0)
pipe
socket
file after open()

int fd = open(...);
fstat(fd, &info);



📌 Where fstat() is used?

Checking if fd is file, pipe, socket
Getting file size after open()
Debugging file descriptors
Networking programs
Shells and system tools

*/




#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    struct stat st;
    int fd = open("random.txt", O_RDONLY);
    int fd1 = open("random2.txt",O_RDONLY);

    if (fd < 0) {
        perror("open failed");
        return 1;
    }

    fstat(fd, &st);

    printf("fstat(): File size = %ld\n", st.st_size);
    printf("fstat(): Number of links = %ld\n", st.st_nlink);

    close(fd);
    close(fd);
}

