#include <stdio.h>
#include <unistd.h>

int main() {
    int x = 10;

    if (fork() == 0) {
        x = 50;
        printf("Child: x = %d\n", x);
    } else {
        sleep(1);
        printf("Parent: x = %d\n", x);
    }
    return 0;
}


/*
Child: x = 50
Parent: x = 10

Confirms separate memory*/