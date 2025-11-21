#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int main() {
    struct termios t;

    // get current terminal settings
    ioctl(0, TCGETS, &t);

    t.c_lflag &= ~ECHO;    // disable echo

    // apply settings
    ioctl(0, TCSETS, &t);

    printf("Echo disabled. Type something: ");
    char buf[100];
    read(0, buf, sizeof(buf));
    printf("\nYou typed: %s\n", buf);

    return 0;
}
