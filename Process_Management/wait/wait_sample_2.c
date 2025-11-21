#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child: finished immediately\n");
        return 0;  // exits instantly
    }
    else {
        printf("Parent: sleeping, not waiting...\n");
        sleep(10);  // child becomes zombie here
    }
}






//ps aux | grep defunct
//komal       6013  0.0  0.0      0     0 pts/1    Z    20:51   0:00 [a.out] <defunct>
/*
 
/Linux_System_Programming/Process_Management/wait$ ./a.out &
[5] 6045
[4]   Done                    ./a.out
Linux_System_Programming/Process_Management/wait$ Parent: sleeping, not waiting...
Child: finished immediately
ps aux | grep defnuct
komal       6049  0.0  0.0   9144  2052 pts/1    S+   20:55   0:00 grep --color=auto defnuct
[5]-  Done                    ./a.out

 
 
 */
