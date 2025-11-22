#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<sys/wait.h>
int main()
{
	pid_t q;
	q = fork();
	if(q == 0)
	{
		printf("I am child having ID %d\n",getpid());
		execl("/bin/ps", "ps",NULL);
	//	printf("I am child having ID %d\n",getpid());
		sleep(10);
	}
	else
	{
		wait(NULL);
		printf("I am Parent Having ID %d\n",getpid());
	}
}
