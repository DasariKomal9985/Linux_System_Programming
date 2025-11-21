#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

if (pid == 0)
    printf("Child Process\n");
else if (pid > 0)
    printf("Parent Process, child pid = %d\n", pid);
else
    printf("fork failed\n");
	
}

