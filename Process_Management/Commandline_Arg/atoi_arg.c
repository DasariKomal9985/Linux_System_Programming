#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    printf("You entered number: %d\n", n);

    return 0;
}

/*

/a.out 543

You entered number: 543





*/