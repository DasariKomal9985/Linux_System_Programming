#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

    if (argc > 1 && strcmp(argv[1], "--help") == 0) {
        printf("Usage: %s <arguments>\n", argv[0]);
        printf("This is a help message.\n");
        return 0;
    }

    printf("Program running normally...\n");

    return 0;
}



/*


 ./a.out --help


Usage: ./a.out <arguments>
This is a help message.






*/