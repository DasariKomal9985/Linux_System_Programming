#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    char input[100];
    char *args[10];

    while (1) {
        printf("KomalShell> ");
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = 0; // remove newline

        // split input into tokens
        int i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL) {
            args[++i] = strtok(NULL, " ");
        }

        // exit shell
        if (strcmp(args[0], "exit") == 0)
            break;

        pid_t pid = fork();

        if (pid == 0) {
            execvp(args[0], args);
            perror("Command failed");
        }
        else {
            wait(NULL);
        }
    }

    return 0;
}

