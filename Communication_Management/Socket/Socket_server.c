#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_un addr;

    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "komal_socket");

    unlink("komal_socket"); // remove if exists
    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 5);

    printf("Server waiting...\n");

    client_fd = accept(server_fd, NULL, NULL);
    
    char buf[100];
    read(client_fd, buf, sizeof(buf));
    printf("Message from client: %s\n", buf);

    write(client_fd, "Hello from Server!", 19);

    close(client_fd);
    close(server_fd);
}

