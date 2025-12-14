#include <stdio.h>
#include <unistd.h>

int main() {
    fork();
    printf("Hello from process\n");
    return 0;
}
