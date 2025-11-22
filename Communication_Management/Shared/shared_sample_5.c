#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    int fd = shm_open("/myshm", O_RDONLY, 0666);

    char *ptr = mmap(0, 1024, PROT_READ, MAP_SHARED, fd, 0);

    printf("Read: %s\n", ptr);

    munmap(ptr, 1024);
    close(fd);

    shm_unlink("/myshm");
}

