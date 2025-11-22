#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    int shmid = shmget(5555, 1024, IPC_CREAT | 0666);
    char *shm = shmat(shmid, NULL, 0);

    strcpy(shm, "Hello from writer!");
    printf("Writer wrote message.\n");

    shmdt(shm);
}

