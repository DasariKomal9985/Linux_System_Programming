#include <stdio.h>

int main(int argc, char *argv[]) {    //How many arguments are passed from command line and array of strings (char *) 

    printf("Total arguments (argc) = %d\n", argc);

    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    return 0;
}

/*

./a.out dasari komal 123

Total arguments (argc) = 4
argv[0] = ./a.out
argv[1] = dasari
argv[2] = komal
argv[3] = 123



*/