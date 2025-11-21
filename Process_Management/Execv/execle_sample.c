#include <unistd.h>
#include <stdio.h>

int main() {

    printf("Running execle...\n");

    char *env[] = {"MYVAR=KOMAL", "CITY=HYDERABAD", NULL};

    // execl(path, arg0, ..., NULL, env);
    execle("/usr/bin/env", "env", NULL, env);

    perror("execle failed");
    return 0;
}

