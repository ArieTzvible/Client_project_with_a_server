
#include "ServerManager.h"
#include <string.h>

void init_server()
{
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
    server_addr.sin_port = PORT;
    server_addr.sin_addr.s_addr = inet_addr(IP);
    n = bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (n < 0)
    {
        perror("[-]Bind error");
        exit(1);
    }

    printf("[+]Bind to the port number: %d\n", PORT);
}

void my_listen()
{
    listen(server_sock, 5);
    printf("Listening...\n");

    addr_size = sizeof(client_sock);
    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
    printf("[+]Client connected.\nclient_sock = %d\n", client_sock);

    char buffer[50] = {0};
    recv(client_sock, buffer, sizeof(buffer), 0);
    printf("Client: %s\n", buffer);

    send_("HI, THIS IS SERVER.\n");
}

void send_(char *buffer)
{
    send(client_sock, buffer, strlen(buffer), 0);
}

void print_send(char *buffer)
{
    send_(buffer);
    char *trash = recv_();
    printf("sent: \n%s\n", buffer);
    if (trash)
    {
        free(trash);
        trash = NULL;
    }
}

void print_recv()
{
    char *buffer = recv_();
    if (buffer)
    {
        free(buffer);
        buffer = NULL;
    }
    send_("0");
}

char *get_recv()
{
    char *buffer = recv_();
    send_("0");
    return buffer;
}

void send_client(char *buffer)
{
    send_(buffer);
    char *trash = recv_();
    if (trash)
    {
        free(trash);
        trash = NULL;
    }
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
        chunk_size = recv(client_sock, chunk, BUFFER_SIZE, 0);
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

void creating_a_string_with_variables(char **buffer, const char *format, ...)
{
    va_list args;
    va_start(args, format); // Start the variable argument list

    // Calculate the required size for the new string
    int size = vsnprintf(NULL, 0, format, args);
    if (size > 0)
    {
        // Allocate memory for the new string
        char *new_str = (char *)malloc((size + 1) * sizeof(char));
        if (new_str)
        {
            // Format the string and store it in the new buffer
            vsprintf(new_str, format, args);

            if (*buffer)
            {
                // Calculate the total size including the existing content
                int total_size = strlen(*buffer) + size;

                // Reallocate memory for the combined string
                char *combined_str = (char *)realloc(*buffer, (total_size + 1) * sizeof(char));

                if (combined_str)
                {
                    // Concatenate the new string with the existing content
                    strcat(combined_str, new_str);
                    *buffer = combined_str;
                }
                else
                {
                    // Handle memory allocation error
                    printf("Not enough memory\n");
                    free(new_str); // Free the newly allocated string
                }
            }
            else
            {
                // If *buffer is NULL, simply copy the new string
                *buffer = strdup(new_str);
                if (!*buffer) 
                    printf("Not enough memory\n");// Handle memory allocation error
            }
            free(new_str); // Free the temporary new string
        }
        else
            printf("Not enough memory\n");// Handle memory allocation error
    }
    va_end(args); // End the variable argument list
}
