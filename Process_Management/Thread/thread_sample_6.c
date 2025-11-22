#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* task(void* arg) {
    printf("Detached thread running...\n");
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    // Make the thread DETACHED
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // Set custom stack size
    pthread_attr_setstacksize(&attr, 1024 * 1024); // 1 MB

    pthread_create(&tid, &attr, task, NULL);

    pthread_attr_destroy(&attr);

    printf("Main will not join thread because it's detached.\n");

    sleep(1);
    return 0;
}

