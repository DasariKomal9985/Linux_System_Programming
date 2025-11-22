#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    int shmid = shmget(5555, 1024, 0666);
    char *shm = shmat(shmid, NULL, 0);

    printf("Reader got: %s\n", shm);

    shmdt(shm);
}

