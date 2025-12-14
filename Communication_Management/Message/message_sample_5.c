#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

/* Message structure */
struct msgbuf {
    long mtype;          // message type (must be > 0)
    char mtext[100];     // message data
};

int main() {
    key_t key;
    int msgid;
    struct msgbuf msg;

    /* 1️⃣ ftok() → generate unique key 🔑 */
    key = ftok("msgfile", 65);
    if (key == -1) {
        perror("ftok failed");
        return 1;
    }

    /* 2️⃣ msgget() → create/open message queue 📬 */
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    /* ================= PARENT PROCESS ================= */
    if (pid > 0) {
        sleep(1);  // ensure child is ready

        msg.mtype = 1;
        strcpy(msg.mtext, "Hello from Parent 🚀");

        /* 3️⃣ msgsnd() → user → kernel copy 📤 */
        msgsnd(msgid, &msg, sizeof(msg.mtext), 0);
        printf("📤 Parent: Message sent to kernel queue\n");

        sleep(1);

        /* 5️⃣ msgctl() → delete message queue ❌ */
        msgctl(msgid, IPC_RMID, NULL);
        printf("❌ Parent: Message queue deleted\n");
    }

    /* ================= CHILD PROCESS ================= */
    else {
        /* 4️⃣ msgrcv() → kernel → user copy 📥 */
        msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0);
        printf("📥 Child: Message received: %s\n", msg.mtext);
    }

    return 0;
}
