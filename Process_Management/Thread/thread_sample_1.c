#include <stdio.h>
#include <pthread.h>

void* myThread(void* arg) {
    printf("Hello from thread!\n");
    return NULL;
}

int main() {
    pthread_t tid;

    pthread_create(&tid, NULL, myThread, NULL);
    pthread_join(tid, NULL);

    printf("Main finished\n");
    return 0;
}

