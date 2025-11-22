#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

int main() {
    char *shm = mmap(NULL, 100, PROT_READ | PROT_WRITE,
                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (fork() == 0) {
        // Child reads
        sleep(1);
        printf("Child got: %s\n", shm);
    }
    else {
        // Parent writes
        strcpy(shm, "Hello from Parent via mmap!");
        wait(NULL);
    }

    munmap(shm, 100);
}

