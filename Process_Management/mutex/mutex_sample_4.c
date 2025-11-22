#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int balance = 1000;
pthread_mutex_t lock;

void* withdraw(void* arg) {
    int amount = *(int*)arg;

    pthread_mutex_lock(&lock);
    if (balance >= amount) {
        printf("Withdrawing %d...\n", amount);
        balance -= amount;
        printf("New balance: %d\n", balance);
    } else {
        printf("Not enough balance\n");
    }
    pthread_mutex_unlock(&lock);

    return NULL;
}

void* deposit(void* arg) {
    int amount = *(int*)arg;

    pthread_mutex_lock(&lock);
    printf("Depositing %d...\n", amount);
    balance += amount;
    printf("New balance: %d\n", balance);
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    pthread_t t1, t2, t3;

    int w1 = 500;
    int w2 = 700;
    int d1 = 300;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, withdraw, &w1);
    pthread_create(&t2, NULL, withdraw, &w2);
    pthread_create(&t3, NULL, deposit, &d1);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    pthread_mutex_destroy(&lock);

    printf("Final balance = %d\n", balance);
    return 0;
}

