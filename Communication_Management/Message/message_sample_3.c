#include <stdio.h>
#include <mqueue.h>
#include <string.h>

int main() {
    mqd_t mq = mq_open("/komal_mq", O_CREAT | O_WRONLY, 0666, NULL);

    char msg[] = "Hello from POSIX MQ!";
    mq_send(mq, msg, strlen(msg) + 1, 0);

    mq_close(mq);
}

