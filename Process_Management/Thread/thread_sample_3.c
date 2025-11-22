#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
void *komalthread_function(void *arg);
int i, j;
int main()
{
	pthread_t komal_thread;
	pthread_create(&komal_thread, NULL, komalthread_function, NULL);
	pthread_join(komal_thread, NULL);
	printf("Inside the main function");
	for(i=0;i<=5;i++)
	{
		printf("%d\n",i);
		sleep(1);
	}
}

void *komalthread_function(void *arg)
{
	printf("Inside Thread");
	for(j=6;j<=10;j++)
	{
		printf("%d\n",j);
		sleep(1);
	}
}
