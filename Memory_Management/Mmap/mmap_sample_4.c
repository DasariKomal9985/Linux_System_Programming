#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    int fd = shm_open("/komal_shm", O_RDONLY, 0666);
    char *ptr = mmap(NULL, 100, PROT_READ, MAP_SHARED, fd, 0);

    printf("Reader: %s\n", ptr);

    munmap(ptr, 100);
    close(fd);
    shm_unlink("/komal_shm");
}

