#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>

struct msgbuf {
    long mtype;
    char mtext[100];
};

int main() {
    key_t key = ftok("file", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    if (fork() == 0) {
        // Child receives type 1
        struct msgbuf msg;
        msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0);
        printf("Child got: %s\n", msg.mtext);

        // Send reply type 2
        msg.mtype = 2;
        strcpy(msg.mtext, "Hello Parent!");
        msgsnd(msgid, &msg, strlen(msg.mtext) + 1, 0);
    }
    else {
        struct msgbuf msg;

        // Parent sends type 1
        msg.mtype = 1;
        strcpy(msg.mtext, "Hello Child!");
        msgsnd(msgid, &msg, strlen(msg.mtext) + 1, 0);

        // Wait for reply type 2
        msgrcv(msgid, &msg, sizeof(msg.mtext), 2, 0);
        printf("Parent got: %s\n", msg.mtext);

        wait(NULL);
        msgctl(msgid, IPC_RMID, NULL);
    }
}

