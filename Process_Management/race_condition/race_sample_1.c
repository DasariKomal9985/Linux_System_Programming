#include <stdio.h>
#include <pthread.h>

int counter = 0;

void* routine(void* arg) {
    for (int i = 0; i < 100000; i++) {
        counter++;  // NOT ATOMIC → race condition
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, routine, NULL);
    pthread_create(&t2, NULL, routine, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final counter: %d\n", counter);
}

