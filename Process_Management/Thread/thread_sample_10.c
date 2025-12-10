/***************************************************************
 *                 MULTI-THREAD RACE CONDITION DEMO
 *        ADDITION & SUBTRACTION USING PTHREADS + MUTEX
 *
 *  ✅ Two threads operate on the SAME shared variable
 *  ✅ One thread performs ADDITION
 *  ✅ Another thread performs SUBTRACTION
 *  ✅ A mutex is used to prevent race condition
 *  ✅ Demonstrates real multi-thread behavior
 ***************************************************************/

#include <stdio.h>      // printf()
#include <pthread.h>    // pthread_create, mutex APIs
#include <unistd.h>     // sleep()

/***************************************************************
 *                  SHARED GLOBAL VARIABLES
 *
 * These variables are accessible by ALL threads.
 * This sharing is the reason mutex protection is required.
 ***************************************************************/
int a = 100;            // First operand (shared)
int b = 40;             // Second operand (shared)
int result = 0;         // Shared result modified by both threads

/***************************************************************
 *                         MUTEX
 *
 * Mutex ensures that only ONE thread can modify
 * the shared variable 'result' at a time.
 ***************************************************************/
pthread_mutex_t lock;

/***************************************************************
 *                 THREAD 1 FUNCTION – ADDITION
 *
 * This function is executed by the first thread.
 * It locks the mutex, performs addition,
 * updates the shared result, and unlocks the mutex.
 ***************************************************************/
void *add_thread(void *arg)
{
    // Indicate that the addition thread has started
    printf("[Add Thread] Started 🧵\n");

    // Lock the mutex to enter critical section
    pthread_mutex_lock(&lock);

    // Confirm mutex acquisition
    printf("[Add Thread] Mutex locked 🔐\n");

    // Sleep to simulate context switching and concurrency
    sleep(1);

    // Critical section: modify shared variable
    result = a + b;

    // Display addition result
    printf("[Add Thread] %d + %d = %d ✅\n", a, b, result);

    // Unlock the mutex after finishing critical section
    pthread_mutex_unlock(&lock);

    // Confirm mutex release
    printf("[Add Thread] Mutex unlocked 🔓\n");

    // Terminate the thread cleanly
    pthread_exit(NULL);
}

/***************************************************************
 *               THREAD 2 FUNCTION – SUBTRACTION
 *
 * This function is executed by the second thread.
 * It locks the SAME mutex, performs subtraction,
 * updates the SAME shared result, and unlocks the mutex.
 ***************************************************************/
void *sub_thread(void *arg)
{
    // Indicate that the subtraction thread has started
    printf("[Sub Thread] Started 🧵\n");

    // Lock the mutex to prevent race condition
    pthread_mutex_lock(&lock);

    // Confirm mutex acquisition
    printf("[Sub Thread] Mutex locked 🔐\n");

    // Sleep to force thread scheduling overlap
    sleep(1);

    // Critical section: update shared variable
    result = a - b;

    // Display subtraction result
    printf("[Sub Thread] %d - %d = %d ✅\n", a, b, result);

    // Unlock mutex to allow other threads
    pthread_mutex_unlock(&lock);

    // Confirm mutex release
    printf("[Sub Thread] Mutex unlocked 🔓\n");

    // Exit the thread properly
    pthread_exit(NULL);
}

/***************************************************************
 *                     MAIN FUNCTION
 *
 * - Initializes mutex
 * - Creates both threads
 * - Waits for both threads to complete
 * - Displays final shared result
 ***************************************************************/
int main()
{
    // Thread identifiers for addition and subtraction threads
    pthread_t t1, t2;

    // Initialize mutex with default attributes
    pthread_mutex_init(&lock, NULL);
    printf("[Main] Mutex initialized ⚙️\n");

    // Create addition thread
    pthread_create(&t1, NULL, add_thread, NULL);

    // Create subtraction thread
    pthread_create(&t2, NULL, sub_thread, NULL);

    // Indicate both threads have been created
    printf("[Main] Threads created 🧵🧵\n");

    // Wait for addition thread to complete
    pthread_join(t1, NULL);

    // Wait for subtraction thread to complete
    pthread_join(t2, NULL);

    // Confirm both threads have finished execution
    printf("[Main] Both threads joined ⏳\n");

    // Print final value of shared result
    // Final value depends on which thread executed last
    printf("[Main] Final value in result = %d 🎯\n", result);

    // End program execution
    return 0;
}



/*

Output

[Main] Mutex initialized ⚙️
[Main] Threads created 🧵🧵
[Add Thread] Started 🧵
[Add Thread] Mutex locked 🔐
[Sub Thread] Started 🧵
[Add Thread] 100 + 40 = 140 ✅
[Add Thread] Mutex unlocked 🔓
[Sub Thread] Mutex locked 🔐
[Sub Thread] 100 - 40 = 60 ✅
[Sub Thread] Mutex unlocked 🔓
[Main] Both threads joined ⏳
[Main] Final value in result = 60 🎯


*/