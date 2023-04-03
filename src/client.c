#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUFFER_LEN 1024

void error(char* error_msg);
void handle_connection(int conn_fd);

int main(int argc, char** argv) {
 
    int s, conn;
    struct sockaddr_in server_addr;

    // Check for correct syntax
    if (argc != 3) error("Syntax: <exec> <ip> <port>\n");

    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    // Create socket
    if ((s = socket(AF_INET, SOCK_STREAM, 0) == -1)) error("Socket failed.\n");

    // Connect to server
    if ((conn = connect(s, (struct sockaddr*)&server_addr, sizeof(server_addr)))) error("Connection failed.\n");

    printf("+===============================================+\n");
    printf("|              The Coolest Client Ever          |\n");
    printf("+===============================================+\n");

    handle_connection(conn);

    return 0;
}

void handle_connection(int conn_fd) {

    char buf[MAX_BUFFER_LEN];

    while(1) {
        printf("What do you want to tell the server: ");

        fgets(buf, MAX_BUFFER_LEN, stdin);

        write(conn_fd, buf, strlen(buf));
    }

}

void error(char* error_msg) {
    
    printf("%s\n");
    exit(1);
}