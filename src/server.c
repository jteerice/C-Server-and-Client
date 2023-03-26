#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(char* error_mesg);

int main(int argc, char** argv) {

    // Ensure correct syntax
    if (argc != 3) error("Syntax: <exec> <ip> <port>\n");

    int s;
    struct sockaddr_in server_addr;

    // Create socket
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) error("Error creating socket.\n");

    server_addr.sin_family      = AF_INET;
    printf("%s\n", argv[2]);
    server_addr.sin_port        = htons(atoi(argv[2]));  // Conert port number to network byte order
    printf("here2\n");
    server_addr.sin_addr.s_addr = inet_aton(argv[1]);    // Convert IP address to network byte order
    //printf("here3\n");

    // Bind socket to port
    if (bind(s, (struct sockaddr*)&server_addr, (socklen_t)sizeof(server_addr)) < 0) error("Error binding port.\n");

    return 0;
}

void error(char* error_mesg) {
    printf("%s", error_mesg);
    exit(1);
}

