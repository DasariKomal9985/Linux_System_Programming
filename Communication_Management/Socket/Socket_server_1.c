#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server, client;
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr*)&server, sizeof(server));
    listen(server_fd, 3);

    printf("TCP Server waiting...\n");

    socklen_t c = sizeof(client);
    client_fd = accept(server_fd, (struct sockaddr*)&client, &c);

    read(client_fd, buffer, sizeof(buffer));
    printf("Client says: %s\n", buffer);

    write(client_fd, "Hello Client", 13);

    close(client_fd);
    close(server_fd);
}

