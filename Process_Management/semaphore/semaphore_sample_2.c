#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

void* thread1(void* arg) {
    printf("Thread1 waiting...\n");
    sem_wait(&sem); // wait for signal
    printf("Thread1 got signal!\n");
    return NULL;
}

void* thread2(void* arg) {
    sleep(2);
    printf("Thread2 sending signal\n");
    sem_post(&sem); // signal thread1
    return NULL;
}

int main() {
    pthread_t t1, t2;

    sem_init(&sem, 0, 0);

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sem);
}

