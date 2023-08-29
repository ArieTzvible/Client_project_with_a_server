
#include "server_manager.h"
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
                buffer = (char *)realloc(buffer, (buffer_size + chunk_size) * sizeof(char));
                strcat(buffer, chunk);
            }
            else
            {
                buffer = NULL;
                buffer = strdup(chunk);
            }
            /* checking whether there is space in the memory*/
            if (!buffer)
            {
                // Error printing when there is no space in memory
                printf("Not enough memory\n");
            }
            else
                buffer_size = strlen(buffer);
        }
    } while (chunk_size == BUFFER_SIZE);
    return buffer;
}

void send_(char *buffer)
{
    send(client_sock, buffer, strlen(buffer), 0);
}

void creating_a_string_with_variables(char **buffer, const char *format, ...)
{
    va_list args;
    va_start(args, format); // Start the variable argument list
    int size = vsnprintf(NULL, 0, format, args); // Get the size of the formatted string

    if (size > 0)
    {
        int size_buffer = size;
        if (*buffer)
        {
            size_buffer += strlen(*buffer);
            *buffer = (char *)realloc(*buffer, size_buffer * sizeof(char));
        }
        char *created_buffer = (char *)malloc(size * sizeof(char)); // Allocate memory for the buffer
        vsprintf(created_buffer, format, args); // Format the string and store it in the buffer
        if (size != size_buffer)
        {
            strcat(*buffer, created_buffer);
            if (created_buffer)
            {
                free(created_buffer);
                created_buffer = NULL;
            }
        }
        else
        {
            *buffer = strdup(created_buffer);
            if(created_buffer){
                free(created_buffer);
                created_buffer = NULL;
            }
        }
    }
    va_end(args); // End the variable argument list
}

// void sending_a_cell_to_add_in_the_file(PClient client)
// {
//     send_("OPEN_FILE");

//     char *buffer;
//     int bufferSize;
//     bufferSize = snprintf(NULL, 0, "%s,%s,%s,%s,%.2f,%02d/%02d/%04d\n", client->firstName, client->lastName,
//                           client->id, client->phone, client->debt, client->date.day, client->date.month, client->date.year);
//     printf("%d", bufferSize);
//     if (bufferSize > 0)
//     {
//         buffer = malloc((bufferSize + 1) * sizeof(char));

//         if (buffer != NULL)
//         {
//             snprintf(buffer, bufferSize + 1, "%s,%s,%s,%s,%.2f,%02d/%02d/%04d\n", client->firstName, client->lastName, client->id, client->phone,
//                      client->debt, client->date.day, client->date.month, client->date.year);
//             printf("%s", buffer);
//             send(client_sock, buffer, strlen(buffer), 0);

//             free(buffer);
//         }
//     }
// }

// todo ****************************************

void print_send(char *buffer)
{
    send_(buffer);
    printf("sent: \n%s\n", buffer);
    char *trash = recv_();
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