#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main() {
    int fd;
    struct sockaddr_un addr;

    fd = socket(AF_UNIX, SOCK_STREAM, 0);

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "komal_socket");

    connect(fd, (struct sockaddr*)&addr, sizeof(addr));

    write(fd, "Hello Server", 13);

    char buf[100];
    read(fd, buf, sizeof(buf));
    printf("Server replied: %s\n", buf);

    close(fd);
}

