/************************************************************
 * DEMONSTRATION OF DEADLOCK USING TWO MUTEXES AND TWO THREADS
 * -----------------------------------------------------------
 * This program intentionally creates a DEADLOCK.
 * 
 * Thread 1 locks mutexes in this order:
 *      first_mutex  →  second_mutex
 *
 * Thread 2 locks mutexes in this order:
 *      second_mutex →  first_mutex
 *
 * Because both threads acquire locks in OPPOSITE ORDER,
 * they will wait forever for each other → DEADLOCK OCCURS.
 ************************************************************/

#include <unistd.h>      // For sleep()
#include <pthread.h>     // For threads and mutexes
#include <stdio.h>       // For printf()

/***********************
 * FUNCTION DECLARATIONS
 ***********************/
void *fun1();   // Thread 1 entry function
void *fun2();   // Thread 2 entry function

/*******************************
 * GLOBAL MUTEX DECLARATIONS
 *******************************/
pthread_mutex_t first_mutex;    // First shared lock
pthread_mutex_t second_mutex;   // Second shared lock


/***********************
 *        MAIN
 ***********************/
int main()
{
    /**************************************************
     * INITIALIZE BOTH MUTEXES
     **************************************************/
    pthread_mutex_init(&first_mutex, NULL);
    pthread_mutex_init(&second_mutex, NULL);

    pthread_t T1, T2;  // Thread identifiers

    /**************************************************
     * CREATE THREAD 1 → runs fun1()
     **************************************************/
    pthread_create(&T1, NULL, fun1, NULL);

    /**************************************************
     * CREATE THREAD 2 → runs fun2()
     **************************************************/
    pthread_create(&T2, NULL, fun2, NULL);

    /**************************************************
     * WAIT FOR BOTH THREADS (but they will deadlock)
     **************************************************/
    pthread_join(T1, NULL);
    pthread_join(T2, NULL);

    /**************************************************
     * THIS LINE WILL NEVER EXECUTE (due to deadlock)
     **************************************************/
    printf("Thread Joined\n");
}



/**************************************************************
 * THREAD FUNCTION 1  (fun1)
 * ------------------------------------------------------------
 * LOCK ORDER (Thread 1):
 *      1. first_mutex
 *      2. second_mutex
 *
 * This is HALF of the deadlock.
 **************************************************************/
void *fun1()
{
    /**************************************************
     * TRY TO LOCK FIRST MUTEX
     **************************************************/
    printf("T1 trying to acquire first mutex\n");
    pthread_mutex_lock(&first_mutex);
    printf("T1 acquired first mutex\n");

    /**************************************************
     * SLEEP so that T2 gets a chance to lock second_mutex
     **************************************************/
    sleep(1);

    /**************************************************
     * TRY TO LOCK SECOND MUTEX
     * BUT T2 ALREADY LOCKED THIS → T1 WILL BLOCK FOREVER
     **************************************************/
    printf("T1 trying to acquire second mutex\n");
    pthread_mutex_lock(&second_mutex);
    printf("T1 acquired second mutex\n");

    /**************************************************
     * THIS LINE WILL NEVER EXECUTE
     **************************************************/
    pthread_mutex_unlock(&first_mutex);

    return NULL;
}



/**************************************************************
 * THREAD FUNCTION 2  (fun2)
 * ------------------------------------------------------------
 * LOCK ORDER (Thread 2):
 *      1. second_mutex
 *      2. first_mutex
 *
 * This order is the OPPOSITE of fun1, completing the deadlock.
 **************************************************************/
void *fun2()
{
    /**************************************************
     * TRY TO LOCK SECOND MUTEX
     **************************************************/
    printf("T2 trying to acquire second mutex\n");
    pthread_mutex_lock(&second_mutex);
    printf("T2 acquired second mutex\n");

    /**************************************************
     * SLEEP so that T1 gets a chance to lock first_mutex
     **************************************************/
    sleep(1);

    /**************************************************
     * TRY TO LOCK FIRST MUTEX
     * BUT T1 ALREADY LOCKED THIS → T2 WILL BLOCK FOREVER
     **************************************************/
    printf("T2 trying to acquire first mutex\n");
    pthread_mutex_lock(&first_mutex);
    printf("T2 acquired first mutex\n");

    /**************************************************
     * THIS LINE WILL NEVER EXECUTE
     **************************************************/
    pthread_mutex_unlock(&second_mutex);

    return NULL;
}














//output




/*T2 trying to acquire second mutex
T2 acquired second mutex
T1 trying to acquire first mutex
T1 acquired first mutex
T2 trying to acquire first mutex
T1 trying to acquire second mutex

*/
