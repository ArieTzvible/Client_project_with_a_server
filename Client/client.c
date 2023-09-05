
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

void send_(char *buffer)
{
    send(sock, buffer, strlen(buffer), 0);
}

void print_from_recv()
{
    char *buffer = NULL;
    do
    {
        if (buffer)
        {
            free(buffer);
            buffer = NULL;
        }

        buffer = recv_();
        if(!strcmp(buffer, "0"))
        printf("%s", buffer);
    } while (!strcmp(buffer, "0"));
    if (buffer)
        free(buffer);
    buffer = NULL;
}

void print_send(char* buffer)
{
    send_(buffer);
    char* trash = recv_();
    if(trash)
        free(trash);
}

void print_recv()
{
    char* buffer = recv_();
	printf("%s\n", buffer);
    if(buffer)
    {
    	free(buffer);
	    buffer = NULL;
    }
	send_("0");
}

char* get_recv()
{
    char* buffer = recv_();
	send_("0");
    return buffer;
}

void send_server(char* buffer)
{
    send_(buffer);
    char* trash = recv_();
    if(trash)
        free(trash);
    trash = NULL;
}

char *recv_()
{
    char *buffer = NULL;
    int buffer_size = 0;
    int chunk_size;
    char chunk[BUFFER_SIZE] = {'\0'};

    do
    {
        bzero(chunk, BUFFER_SIZE);
        chunk_size = recv(sock, chunk, BUFFER_SIZE, 0);
        if (chunk_size > 0)
        {
            if (buffer_size)
            {
                char *new_buffer = (char *)realloc(buffer, (buffer_size + chunk_size + 1) * sizeof(char));
                if (new_buffer)
                {
                    buffer = new_buffer;
                    strcat(buffer, chunk);
                    buffer_size += chunk_size;
                }
                else
                {
                    printf("Not enough memory\n");
                    free(buffer); // Free the previously allocated buffer
                    return NULL; // Return NULL to indicate an error
                }
            }
            else
            {
                buffer = strdup(chunk);
                if (!buffer)
                {
                    printf("Not enough memory\n");
                    return NULL; // Return NULL to indicate an error
                }
                buffer_size = chunk_size;
            }
        }
    } while (chunk_size == BUFFER_SIZE);
    return buffer;
}