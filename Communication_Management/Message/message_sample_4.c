#include <stdio.h>
#include <mqueue.h>

int main() {
    char buffer[100];
    mqd_t mq = mq_open("/komal_mq", O_RDONLY);

    mq_receive(mq, buffer, 100, NULL);
    printf("Received: %s\n", buffer);

    mq_close(mq);
    mq_unlink("/komal_mq");
}

