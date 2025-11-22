#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void *fun1();
void *fun2();
int shared = 1;
int main()
{
	pthread_t thread1,thread2;
	pthread_create(&thread1, NULL, fun1, NULL);
	pthread_create(&thread2, NULL, fun2, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("Final value of shared value is %d\n",shared);
}



void *fun1()
{
	int x;
	x = shared;
	printf("thread1 reads shared value : %d\n",x);
	x++;
	printf("Updated value of shared thread1 : %d\n",x);
	sleep(1);
	shared = x;
	printf("Shared value is updated :%d\n",shared);

}

void *fun2()
{
	int y;
	y = shared;
	printf("thread2 reads shared value : %d\n",y);
	y--;
	printf("Updated value of shared thread2: %d\n",y);
	sleep(1);
	shared = y;
	printf("shared value is updated :%d\n",shared);
}
