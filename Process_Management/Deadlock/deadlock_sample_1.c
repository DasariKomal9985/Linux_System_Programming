/************************************************************
 * DEADLOCK-FREE MULTI-THREADING PROGRAM USING MUTEX ORDERING
 * ----------------------------------------------------------
 * This program creates two threads (T1 and T2). Both threads
 * need to lock TWO mutexes. If they lock them in different
 * orders, a deadlock occurs. However, here both threads lock
 * the mutexes in the SAME order:
 *
 *          first_mutex → second_mutex
 *
 * Because both threads follow the same locking order, there
 * is no circular wait condition → NO DEADLOCK.
 ************************************************************/

#include <unistd.h>      // For sleep()
#include <pthread.h>     // For pthreads and mutex functions
#include <stdio.h>       // For printf()

/***********************
 * FUNCTION DECLARATIONS
 ***********************/
void *fun1();   // Thread 1 function
void *fun2();   // Thread 2 function

/*******************************
 * GLOBAL MUTEX DECLARATIONS
 * --------------------------
 * These mutexes protect shared resources.
 *******************************/
pthread_mutex_t first_mutex;   // First lock
pthread_mutex_t second_mutex;  // Second lock


/***********************
 * MAIN FUNCTION STARTS
 ***********************/
int main()
{
    /**************************************************
     * INITIALIZE BOTH MUTEXES
     **************************************************/
    pthread_mutex_init(&first_mutex, NULL);   // Initialize first mutex
    pthread_mutex_init(&second_mutex, NULL);  // Initialize second mutex

    pthread_t T1, T2;   // Thread identifiers

    /**************************************************
     * CREATE THREAD 1 → runs fun1()
     **************************************************/
    pthread_create(&T1, NULL, fun1, NULL);

    /**************************************************
     * CREATE THREAD 2 → runs fun2()
     **************************************************/
    pthread_create(&T2, NULL, fun2, NULL);

    /**************************************************
     * WAIT FOR BOTH THREADS TO FINISH
     **************************************************/
    pthread_join(T1, NULL);
    pthread_join(T2, NULL);

    printf("Thread Joined. Program Finished Without Deadlock.\n");

    return 0; // End of main
}



/*******************************************
 * THREAD FUNCTION 1  → fun1()
 * -----------------------------------------
 * Locks mutexes in order:
 *      1. first_mutex
 *      2. second_mutex
 *******************************************/
void *fun1()
{
    printf("\n[T1] Trying to acquire FIRST mutex...\n");

    /**************************************************
     * THREAD 1 LOCKS first_mutex
     **************************************************/
    pthread_mutex_lock(&first_mutex);
    printf("[T1] FIRST mutex acquired.\n");

    /**************************************************
     * SLEEP to let other thread attempt locks
     **************************************************/
    sleep(1);

    printf("[T1] Trying to acquire SECOND mutex...\n");

    /**************************************************
     * THREAD 1 LOCKS second_mutex
     **************************************************/
    pthread_mutex_lock(&second_mutex);
    printf("[T1] SECOND mutex acquired.\n");

    /**************************************************
     * Unlock in REVERSE ORDER (good practice)
     **************************************************/
    pthread_mutex_unlock(&second_mutex);
    pthread_mutex_unlock(&first_mutex);

    printf("[T1] Released both mutexes.\n");

    return NULL;
}



/*******************************************
 * THREAD FUNCTION 2  → fun2()
 * -----------------------------------------
 * Also locks mutexes in SAME ORDER:
 *      1. first_mutex
 *      2. second_mutex
 *
 * Because both threads follow SAME LOCK ORDERING,
 * circular wait is impossible → NO DEADLOCK.
 *******************************************/
void *fun2()
{
    printf("\n[T2] Trying to acquire FIRST mutex...\n");

    /**************************************************
     * THREAD 2 LOCKS first_mutex
     **************************************************/
    pthread_mutex_lock(&first_mutex);
    printf("[T2] FIRST mutex acquired.\n");

    /**************************************************
     * SLEEP to increase chance of interleaving
     **************************************************/
    sleep(1);

    printf("[T2] Trying to acquire SECOND mutex...\n");

    /**************************************************
     * THREAD 2 LOCKS second_mutex
     **************************************************/
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










//output
//
//
//



/*
[T2] Trying to acquire FIRST mutex...
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
