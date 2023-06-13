#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void send_and_recv(int client_sock, char* buffer, int size_buffer);

int main()
{
    char *ip = "127.0.0.1";
    int port = 5566;

    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];
    int n;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        perror("[-]Socket error\n");
        exit(1);
    }

    printf("[+]TCP server socket created.\n");

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    n = bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (n < 0)
    {
        perror("[-]Bind error");
        exit(1);
    }
    printf("[+]Bind to the port number: %d\n", port);

    listen(server_sock, 5);
    printf("Listening...\n");

    // while(1){
    addr_size = sizeof(client_sock);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    printf("[+]Client connected.\n");
    
    bzero(buffer, 1024);
    recv(client_sock, buffer, sizeof(buffer), 0);
    printf("Client: %s\n", buffer); 

    strcpy(buffer, "0");
    while(strcmp(buffer, "-1")){

        bzero(buffer, 1024);
        strcpy(buffer, "HI, THIS IS SERVER. HAVE A NICE DAY!!!\n\nEnter -1 for exit:");
        send_and_recv(client_sock, buffer, strlen(buffer));

    }

    bzero(buffer, 1024);
    strcpy(buffer, "quit");
    send_and_recv(client_sock, buffer, strlen(buffer));

    close(client_sock);
    printf("[+]Client disconnected.\n\n");

// }//while ^^


    close(server_sock);
    printf("[+]Server disconnected.\n\n");

    return 0;
}

void send_and_recv(int client_sock, char* buffer, int size_buffer)
{
    printf("size_buffer: %d\n", size_buffer);
    send(client_sock, buffer, size_buffer, 0);
    printf("Server: %s\n", buffer);
    bzero(buffer, size_buffer);
    char this_buffer[1024] = {0};
    recv(client_sock, this_buffer, sizeof(this_buffer), 0);
    strcpy(buffer, this_buffer);
    printf("Client: %s\n", buffer); 
}
