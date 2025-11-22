#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = shm_open("/komal_shm", O_CREAT | O_RDWR, 0666);
    ftruncate(fd, 100);

    char *ptr = mmap(NULL, 100, PROT_WRITE, MAP_SHARED, fd, 0);
    strcpy(ptr, "Hello from writer!");

    munmap(ptr, 100);
    close(fd);
}

