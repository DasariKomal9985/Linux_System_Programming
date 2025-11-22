#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

int main() {
    int shmid;
    char *shm;

    shmid = shmget(1234, 1024, IPC_CREAT | 0666);

    if (fork() == 0) {
        // Child
        shm = shmat(shmid, NULL, 0);
        printf("Child: reading: %s\n", shm);
        shmdt(shm);
    }
    else {
        // Parent
        shm = shmat(shmid, NULL, 0);
        strcpy(shm, "Hello from Parent");
        shmdt(shm);
        wait(NULL);
    }

    shmctl(shmid, IPC_RMID, NULL); // delete shared memory
}

