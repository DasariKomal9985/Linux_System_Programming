#include <stdio.h>
#include <unistd.h>

int main() {
    fork();
    fork();
    printf("Process running\n");
    return 0;
}
/*
2² = 4
*/