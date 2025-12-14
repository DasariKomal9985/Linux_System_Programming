#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Before fork\n");

    fork();

    printf("After fork\n");
    return 0;
}


/*
Before fork
After fork
After fork
*/