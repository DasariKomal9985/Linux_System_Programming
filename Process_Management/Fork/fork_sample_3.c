#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("I am Child My ID is %d\n",getpid());
	printf("My Parent ID is %d\n",getppid());
    } else if (pid > 0) {
        printf("I am Parent My ID is %d\n",getpid());
	printf("My Child Process ID is %d\n",pid);
    } else {
        perror("fork failed");
    }
}




/*

I am Parent My ID is 8932
My Child Process ID is 8933
I am Child My ID is 8933
My Parent ID is 8932


*/
