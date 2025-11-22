#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

void* worker(void* arg) {
    sem_wait(&sem);           // Lock
    printf("Thread %ld entered critical section\n", pthread_self());
    sleep(1);
    printf("Thread %ld leaving\n", pthread_self());
    sem_post(&sem);           // Unlock
    return NULL;
}

int main() {
    pthread_t t1, t2;

    sem_init(&sem, 0, 1);     // Binary semaphore (1)

    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sem);
}

