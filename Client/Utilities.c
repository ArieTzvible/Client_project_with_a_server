#include "HeaderUtilities.h"

char *get_new_file_name(char *extension)
{ // Requesting another file name
    printf("\n\tEnter a file name: ");
    char *string = getting_line(stdin); // getting a line from the user includes creating a dynamic string
    if (strcmp((string + (strlen(string) - strlen(extension))), extension))
    {                                                                                        // check that there is no file name at the end(CSV)
        char *str = (char *)malloc((strlen(string) + strlen(extension) + 1) * sizeof(char)); // creating a string that will also contain the document extension
        if (!str)                                                                            // testing whether the allocation was successful
            printf("Not enough memory\n");                                                   // print error;//Error printing when there is no space in memory
        else
        {
            strcpy(str, string);    // copy the string received from the user
            strcat(str, extension); // copy the file extension
            strcat(str, "\0");      // adding 0\ at the end of the string
            free(string);           // release the string we received from the user
            string = str;           // setting the string to the string to send
        }
    }
    return string; // sending a pointer with the file name
}

void sending_line_to_a_server(FILE *file)
{ // creating a list from the file
    char *line = NULL;
    char *trash = NULL;
    /*checking whether the end of the file has been reached*/
    while (!(feof(file)))
    {
        line = getting_line(file); // send to get a line from the file
        if (line != NULL && *line != '\n')
        {
            send(sock, line, strlen(line), 0);
            trash = recv_();
            free(trash);
        }
        if (line)
        {
            free(line);
            line = NULL;
        }
    }
    send_("0");
    trash = recv_();
    free(trash);
}

/*Sending a line from the file to the server*/
char *getting_line(FILE *file) // getting a complete line from the file
{
    char *input = NULL;        // statement about a pointer to a row that the user entered
    char string[1024];         // Declaration of a variable
    fgets(string, 1024, file); // Getting a string from the file
    if (feof(file))
        return NULL;        // Returning NULL when reaching the end of the file
    input = strdup(string); // Creating a variable and copying the string
    if (!input)
    {                                  // checking whether there is space in the memory
        printf("Not enough memory\n"); // Error printing when there is no space in memory
        return input;
    }
    if (input[strlen(input) - 1] == '\n' || input[strlen(input) - 1] == '\0')
    {                                    // Checking whether the entire line was received
        input[strlen(input) - 1] = '\0'; // Changing the last cell to \0
        return input;
    }
    return input;
}
