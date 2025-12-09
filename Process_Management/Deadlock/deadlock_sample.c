
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
"sample_1.c" 106L, 2694B                                                                                                                                              106,43-40     Bot
