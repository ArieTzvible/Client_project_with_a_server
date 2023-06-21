
#include "client_manager.h"

void init_client()
{
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("[-]Socket error\n");
        exit(1);
    }

    printf("[+]TCP server socket created.\n");

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = PORT;
    addr.sin_addr.s_addr = inet_addr(IP);

    connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    printf("[+]Connected to the server.\n");

    send_("HELLO, THIS IS CLIENT.\n");

    char buffer[50] = {0};
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);

}

char *recv_()
{
    char *buffer = NULL;
    int buffer_size = 0;
    int chunk_size;
    char chunk[BUFFER_SIZE];

    do
    {
        bzero(chunk, BUFFER_SIZE);
        chunk_size = recv(sock, chunk, BUFFER_SIZE, 0);
        if (chunk_size > 0)
        {
            buffer = (char *)realloc(buffer, buffer_size + chunk_size);
            /* checking whether there is space in the memory*/
            if (!buffer)
            {
                // Error printing when there is no space in memory
                printf("Not enough memory\n");
            }
            strcat(buffer, chunk);
            buffer_size += strlen(buffer);
        }
    } while (chunk_size == BUFFER_SIZE);

    return buffer;
}

void send_(char *buffer)
{
    printf("send_ %s\n", buffer);
    send(sock, buffer, strlen(buffer), 0);
    printf("send_ DONE\n");
}

void print_from_recv()
{
    char *buffer = NULL;
    do
    {
        if (buffer)
            free(buffer);

        buffer = recv_();
        if(!strcmp(buffer, "0"))
        printf("%s", buffer);
    } while (!strcmp(buffer, "0"));
    free(buffer);
}
