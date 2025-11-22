#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

void* run(void* arg) {
    sem_wait(&sem);
    printf("Thread %ld running\n", pthread_self());
    sleep(1);
    sem_post(&sem);
    return NULL;
}

int main() {
    pthread_t t[10];

    sem_init(&sem, 0, 3);  // Allow 3 threads at a time

    for(int i=0; i<10; i++)
        pthread_create(&t[i], NULL, run, NULL);

    for(int i=0; i<10; i++)
        pthread_join(t[i], NULL);

    sem_destroy(&sem);
}

