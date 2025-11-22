#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
void *thread_function(void *arg);
int num[2]={3,7};
int main()
{
	pthread_t k_thread;
	void *result;
	pthread_create(&k_thread, NULL, thread_function, (void *)num);
	pthread_join(k_thread, &result);
	printf("Inside main process\n");
	printf("thread returned: %s\n",(char *)result);

}


void *thread_function(void *arg)
{
	printf("Inside Thread\n");
	int *x = arg;
	int sum = x [0]+x[1];
	printf("Sum is %d\n",sum);
	pthread_exit("Sum Calaulated");
}
