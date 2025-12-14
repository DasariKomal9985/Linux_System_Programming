#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    key_t key;
    int shmid;
    int *shared_data;

    /* 1️⃣ Generate key */
    key = ftok("shmfile", 65);

    /* 2️⃣ Create shared memory (4 bytes for int) */
    shmid = shmget(key, sizeof(int), 0666 | IPC_CREAT);

    pid_t pid = fork();

    /* ================= PARENT PROCESS ================= */
    if (pid > 0) {
        /* 3️⃣ Attach shared memory */
        shared_data = (int *)shmat(shmid, NULL, 0);

        *shared_data = 123;   // write directly
        printf("🧠 Parent wrote: %d\n", *shared_data);

        sleep(2);

        /* 4️⃣ Detach */
        shmdt(shared_data);

        /* 5️⃣ Delete shared memory */
        shmctl(shmid, IPC_RMID, NULL);
        printf("❌ Shared memory deleted\n");
    }

    /* ================= CHILD PROCESS ================= */
    else {
        sleep(1);

        shared_data = (int *)shmat(shmid, NULL, 0);
        printf("👶 Child read: %d\n", *shared_data);

        shmdt(shared_data);
    }

    return 0;
}
