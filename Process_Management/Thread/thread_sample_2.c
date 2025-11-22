#include <stdio.h>
#include <pthread.h>

void* printNumber(void* arg) {
    int num = *(int*)arg;
    printf("Thread got: %d\n", num);
    return NULL;
}

int main() {
    pthread_t t;
    int x = 99;

    pthread_create(&t, NULL, printNumber, &x);
    pthread_join(t, NULL);

    return 0;
}

