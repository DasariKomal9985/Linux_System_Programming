#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = shm_open("/myshm", O_CREAT | O_RDWR, 0666);
    ftruncate(fd, 1024);

    char *ptr = mmap(0, 1024, PROT_WRITE, MAP_SHARED, fd, 0);
    strcpy(ptr, "Hello from POSIX!");

    munmap(ptr, 1024);
    close(fd);
    return 0;
}

