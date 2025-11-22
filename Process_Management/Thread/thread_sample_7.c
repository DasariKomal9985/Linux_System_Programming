#include <stdio.h>
#include <pthread.h>

void* myThread(void* arg) {
    printf("Inside thread function\n");
    pthread_exit("Thread finished work");
}

int main() {
    pthread_t tid;
    void* result;

    pthread_create(&tid, NULL, myThread, NULL);
    pthread_join(tid, &result);

    printf("Main received: %s\n", (char*)result);
    return 0;
}

