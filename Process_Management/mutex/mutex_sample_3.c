#include <pthread.h>
#include <stdio.h>

pthread_mutex_t lock;

void fun(int x) {
    if (x == 0) return;
    pthread_mutex_lock(&lock);
    printf("fun(%d)\n", x);
    fun(x - 1);   // recursion
    pthread_mutex_unlock(&lock);
}

int main() {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);

    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

    pthread_mutex_init(&lock, &attr);

    fun(5);

    pthread_mutex_destroy(&lock);
}

