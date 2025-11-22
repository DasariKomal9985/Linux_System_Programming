#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// THREAD FUNCTION
void* compute(void* arg) {
    int* nums = (int*)arg;

    printf("[Thread] My pthread ID = %lu\n", pthread_self());
    printf("[Thread] Received numbers: %d and %d\n", nums[0], nums[1]);

    int* result = malloc(sizeof(int));
    *result = nums[0] + nums[1];

    pthread_exit((void*)result);
}

int main() {
    pthread_t tid;
    pthread_attr_t attr;
    void* thread_result;

    int numbers[2] = {5, 15};

    // Initialize thread attributes
    pthread_attr_init(&attr);

    // Set custom stack size
    pthread_attr_setstacksize(&attr, 1024 * 1024);

    // Ensure thread is JOINABLE (default)
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // Create thread using attributes and pass argument
    pthread_create(&tid, &attr, compute, (void*)numbers);

    printf("[Main] Created thread with ID = %lu\n", tid);

    // Clean up attributes
    pthread_attr_destroy(&attr);

    // Wait for thread and get return value
    pthread_join(tid, &thread_result);

    int final_sum = *(int*)thread_result;
    printf("[Main] Thread returned sum = %d\n", final_sum);

    free(thread_result);

    return 0;
}

