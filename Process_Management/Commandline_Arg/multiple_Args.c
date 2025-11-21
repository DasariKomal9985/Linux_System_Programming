#include <stdio.h>

int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("Usage: %s <first> <second>\n", argv[0]);
        return 1;
    }

    printf("First argument  = %s\n", argv[1]);
    printf("Second argument = %s\n", argv[2]);

    return 0;
}



/*

/a.out  hello komal


First argument  = hello
Second argument = komal




*/
