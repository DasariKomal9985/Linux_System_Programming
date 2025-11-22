#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main() {
    int fd = open("data.txt", O_RDWR);
    struct stat st;
    fstat(fd, &st);

    char *map = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    printf("File content: %s\n", map);

    // Modify file through memory
    strcpy(map, "Hello mmap!");

    munmap(map, st.st_size);
    close(fd);
}

