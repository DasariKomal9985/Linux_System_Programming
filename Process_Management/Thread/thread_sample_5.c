#include <stdio.h>
#include <pthread.h>

void* worker(void* arg) {
    printf("Thread started. My pthread ID = %lu\n", pthread_self());
    return NULL;
}

int main() {
    pthread_t tid;

    pthread_create(&tid, NULL, worker, NULL);

    printf("Main created thread with ID = %lu\n", tid);

    pthread_join(tid, NULL);
    return 0;
}

