#include <stdio.h>
#include <pthread.h>

void* calculate(void* arg) {
    int* nums = (int*)arg;
    int sum = nums[0] + nums[1];
    printf("Sum = %d\n", sum);
    return NULL;
}

int main() {
    pthread_t tid;
    int arr[2] = {10, 20};

    pthread_create(&tid, NULL, calculate, (void*)arr);
    pthread_join(tid, NULL);

    return 0;
}

