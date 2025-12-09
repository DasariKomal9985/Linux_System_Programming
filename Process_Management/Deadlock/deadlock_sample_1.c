/************************************************************
 * DEADLOCK FREE PROGRAM USING CONSISTENT LOCK ORDER
 * ----------------------------------------------------------
 * Technique Used:
 *   1. Both threads lock mutexes in the SAME ORDER
 *   2. Mutexes are unlocked in REVERSE ORDER
 *
 * This prevents circular wait → NO DEADLOCK
 ************************************************************/

#include <stdio.h>      // printf()
#include <pthread.h>   // pthread_create, mutex functions
#include <unistd.h>    // sleep()

/***********************
 * FUNCTION PROTOTYPES
 ***********************/
void *fun1(void *arg);
void *fun2(void *arg);

/***********************
 * GLOBAL MUTEXES
 ***********************/
pthread_mutex_t first_mutex;
pthread_mutex_t second_mutex;

/***********************
 * MAIN FUNCTION
 ***********************/
int main()
{
    pthread_t T1, T2;

    /* Initialize mutexes */
    pthread_mutex_init(&first_mutex, NULL);
    pthread_mutex_init(&second_mutex, NULL);

    /* Create threads */
    pthread_create(&T1, NULL, fun1, NULL);
    pthread_create(&T2, NULL, fun2, NULL);

    /* Wait for both threads to finish */
    pthread_join(T1, NULL);
    pthread_join(T2, NULL);

    printf("Thread Joined. Program Finished Without Deadlock.\n");

    /* Destroy mutexes */
    pthread_mutex_destroy(&first_mutex);
    pthread_mutex_destroy(&second_mutex);

    return 0;
}

/***********************
 * THREAD 1 FUNCTION
 ***********************/
void *fun1(void *arg)
{
    printf("[T1] Trying to acquire FIRST mutex...\n");
    pthread_mutex_lock(&first_mutex);
    printf("[T1] FIRST mutex acquired.\n");

    sleep(1);   // Artificial delay

    printf("[T1] Trying to acquire SECOND mutex...\n");
    pthread_mutex_lock(&second_mutex);
    printf("[T1] SECOND mutex acquired.\n");

    /**************************************************
     * Unlock in REVERSE ORDER
     **************************************************/
    pthread_mutex_unlock(&second_mutex);
    pthread_mutex_unlock(&first_mutex);

    printf("[T1] Released both mutexes.\n");

    return NULL;
}

/***********************
 * THREAD 2 FUNCTION
 ***********************/
void *fun2(void *arg)
{
    printf("[T2] Trying to acquire FIRST mutex...\n");
    pthread_mutex_lock(&first_mutex);
    printf("[T2] FIRST mutex acquired.\n");

    sleep(1);   // Artificial delay

    printf("[T2] Trying to acquire SECOND mutex...\n");
    pthread_mutex_lock(&second_mutex);
    printf("[T2] SECOND mutex acquired.\n");

    /**************************************************
     * Unlock in REVERSE ORDER
     **************************************************/
    pthread_mutex_unlock(&second_mutex);
    pthread_mutex_unlock(&first_mutex);

    printf("[T2] Released both mutexes.\n");

    return NULL;
}





/*[T2] Trying to acquire FIRST mutex...
[T2] FIRST mutex acquired.
[T1] Trying to acquire FIRST mutex...
[T2] Trying to acquire SECOND mutex...
[T2] SECOND mutex acquired.
[T2] Released both mutexes.
[T1] FIRST mutex acquired.
[T1] Trying to acquire SECOND mutex...
[T1] SECOND mutex acquired.
[T1] Released both mutexes.
Thread Joined. Program Finished Without Deadlock.
*/
