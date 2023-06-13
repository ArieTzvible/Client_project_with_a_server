#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void send_and_recv(int sock, char* buffer, int size_buffer);


int main()
{
    char *ip = "127.0.0.1";
    int port = 5566;

    int sock;
    struct sockaddr_in addr;
    socklen_t addr_size;
    char buffer[1024];
    int n;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("[-]Socket error\n");
        exit(1);
    }

    printf("[+]TCP server socket created.\n");

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = inet_addr(ip);

    connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    printf("Connected to the server.\n");

    bzero(buffer, 1024);
    strcpy(buffer, "HELLO, THIS IS CLIENT.");
    send_and_recv(sock, buffer, strlen(buffer));
    
    while(strcmp(buffer, "quit"))
    {
        bzero(buffer, 1024);
        scanf("%s", buffer);
        printf("%s", buffer);
        send_and_recv(sock, buffer, strlen(buffer));
    }


    bzero(buffer, 1024);
    strcpy(buffer, "BYE BYE.");
    send(sock, buffer, strlen(buffer), 0);

    close(sock);
    printf("Disconnected from the server.\n\n");

    return 0;
}

void send_and_recv(int sock, char* buffer, int size_buffer)
{
    send(sock, buffer, size_buffer, 0);
    printf("Client: %s\n", buffer);
    bzero(buffer, size_buffer);
    char this_buffer[1024] = {0};
    recv(sock, this_buffer, sizeof(this_buffer), 0);
    strcpy(buffer, this_buffer);
    printf("Server: %s\n", buffer); 
}