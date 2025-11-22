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
        // CHILD: receive message
        struct msgbuf message;
        msgrcv(msgid, &message, sizeof(message.mtext), 1, 0);
        printf("Child received: %s\n", message.mtext);
    }
    else {
        // PARENT: send message
        struct msgbuf message;
        message.mtype = 1;
        strcpy(message.mtext, "Hello from Parent!");

        msgsnd(msgid, &message, strlen(message.mtext) + 1, 0);

        wait(NULL);
        msgctl(msgid, IPC_RMID, NULL);
    }
}

