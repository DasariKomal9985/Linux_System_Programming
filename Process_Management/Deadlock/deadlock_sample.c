ubuntu@ubuntu:~/Documents/LSP/Deadlock$ cat sample_1.c
/************************************************************
 * DEADLOCK DEMONSTRATION USING TWO MUTEXES AND TWO THREADS
 * --------------------------------------------------------
 * Thread 1 lock order: first_mutex  -> second_mutex
 * Thread 2 lock order: second_mutex -> first_mutex
 *
 * This opposite locking order causes DEADLOCK.
 ************************************************************/

#include <stdio.h>      // printf()
#include <pthread.h>   // pthread_create, pthread_mutex
#include <unistd.h>    // sleep()

/***********************
 * FUNCTION PROTOTYPES
 ***********************/
void *fun1(void *arg);   // Thread 1 function
void *fun2(void *arg);   // Thread 2 function

/************************
 * GLOBAL MUTEXES
 ************************/
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

    /* Wait for threads (this will never return due to deadlock) */
    pthread_join(T1, NULL);
    pthread_join(T2, NULL);

    /* Cleanup (never reached) */
    pthread_mutex_destroy(&first_mutex);
    pthread_mutex_destroy(&second_mutex);

    return 0;
}

/***********************
 * THREAD 1 FUNCTION
 ***********************/
void *fun1(void *arg)
{
    printf("T1 trying to acquire FIRST mutex\n");
    pthread_mutex_lock(&first_mutex);
    printf("T1 acquired FIRST mutex\n");

    sleep(1);  // Force context switch

    printf("T1 trying to acquire SECOND mutex\n");
    pthread_mutex_lock(&second_mutex);   // Stuck here
    printf("T1 acquired SECOND mutex\n");

    pthread_mutex_unlock(&second_mutex);
    pthread_mutex_unlock(&first_mutex);

    return NULL;
}

/***********************
 * THREAD 2 FUNCTION
 ***********************/
void *fun2(void *arg)
{
    printf("T2 trying to acquire SECOND mutex\n");
    pthread_mutex_lock(&second_mutex);
    printf("T2 acquired SECOND mutex\n");

    sleep(1);  // Force context switch

    printf("T2 trying to acquire FIRST mutex\n");
    pthread_mutex_lock(&first_mutex);    // Stuck here
    printf("T2 acquired FIRST mutex\n");

    pthread_mutex_unlock(&first_mutex);
    pthread_mutex_unlock(&second_mutex);

    return NULL;
}







/*T1 trying to acquire FIRST mutex
T1 acquired FIRST mutex
T2 trying to acquire SECOND mutex
T2 acquired SECOND mutex
T1 trying to acquire SECOND mutex
T2 trying to acquire FIRST mutex
⛔ Program hangs here forever → DEADLOCK*/
