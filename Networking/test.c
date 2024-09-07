#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "Server.h"

void launch(struct Server *server) {
    char buffer[30000];
    while (1) {
        printf("====== WAITING FOR CONNECTION ======\n");
        int address_length = sizeof(server->address);
        int new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length);
        read(new_socket, buffer, 30000);
        printf("%s\n", buffer);
        char *hello = "HTTP/1.1 200 ok\nDate: Sat, 7th Sep 2024 20:00:00 GMT\nServer: Apache\nLast-Modified: Sat, 7th Sep 2024 20:00:00 GMT\nContent-Length: 88\nContent-Type: text/html\r\nConnection: Closed\r\n\r\n<html><body><h1>Hello World!</h1></body></html>\r\n";
        write(new_socket, hello, strlen(hello));
        close(new_socket);
    }
}

int main() {
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 10, launch);
    server.launch(&server);
}