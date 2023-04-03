#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define CONN_BUFFER_LEN 1
#define MAX_BUFFER_LEN 1024

void error(char* error_mesg);
void handle_connection(int conn_fd);

int main(int argc, char** argv) {

    // Ensure correct syntax
    if (argc != 3) error("Syntax: <exec> <ip> <port>\n");

    int s, conn;
    struct sockaddr_in server_addr, conn_addr;
    socklen_t conn_len = sizeof(conn_addr);

    // Create socket
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) error("Error creating socket.\n");
    // Zero out address space of server_addr
    bzero(&server_addr, sizeof(server_addr)); 

    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(atoi(argv[2]));  // Conert port number to network byte order
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);    // Convert IP address to network byte order

    // Bind socket to port
    if (bind(s, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) error("Error binding port.\n");
    // Set socket to passive 
    if (listen(s, CONN_BUFFER_LEN) < 0) error("Error setting socket to listen.\n");

    printf("+===============================================+\n");
    printf("|              The Coolest Server Ever          |\n");
    printf("+===============================================+\n");

    // Wait for connection
    if ((conn = accept(s, (struct sockaddr *)&conn_addr, &conn_len)) < 0) error("Failed to accept connection.\n");
    printf("Connection found!\n");
    handle_connection(conn);

    return 0;
}

void handle_connection(int conn_fd) {

    char buf[MAX_BUFFER_LEN];

    while(1) {
        read(conn_fd, buf, (MAX_BUFFER_LEN - 1));

        // Null terminate the buffer
        buf[MAX_BUFFER_LEN - 1] = '\0';

        printf("The client says: %s\n", buf);
    }
}

void error(char* error_mesg) {
    printf("%s", error_mesg);
    exit(1);
}

