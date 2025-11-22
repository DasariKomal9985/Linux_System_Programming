#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int buf_index = 0;   // fixed

sem_t empty, full;
pthread_mutex_t lock;

void* producer(void* arg) {
    for(int i = 1; i <= 10; i++) {
        sem_wait(&empty);        // Wait for empty slot
        pthread_mutex_lock(&lock);

        buffer[buf_index++] = i;     // FIXED
        printf("Produced: %d\n", i);

        pthread_mutex_unlock(&lock);
        sem_post(&full);         // Signal data available
    }
    return NULL;
}

void* consumer(void* arg) {
    for(int i = 1; i <= 10; i++) {
        sem_wait(&full);         // Wait for data
        pthread_mutex_lock(&lock);

        int item = buffer[--buf_index];  // FIXED
        printf("Consumed: %d\n", item);

        pthread_mutex_unlock(&lock);
        sem_post(&empty);        // Signal empty slot
    }
    return NULL;
}

int main() {
    pthread_t p, c;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&lock, NULL);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&lock);

    return 0;
}

