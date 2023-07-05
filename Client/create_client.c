#include "CreatingManager.h"

char* get_new_file_Name(char* extension) {//Requesting another file name
	printf("\n\tEnter a file name: ");
	char* string = GettingLine(stdin);//getting a line from the user includes creating a dynamic string
	if (strcmp((string + (strlen(string) - strlen(extension))), extension)) {// check that there is no file name at the end(CSV)		
		char* str = (char*)malloc((strlen(string) + strlen(extension) + 1) * sizeof(char));//creating a string that will also contain the document extension
		if (!str)//testing whether the allocation was successful
			printf("Not enough memory\n");//print error;//Error printing when there is no space in memory
		else {
			strcpy(str, string);//copy the string received from the user
			strcat(str, extension);//copy the file extension
			strcat(str, "\0");//adding 0\ at the end of the string
			free(string);//release the string we received from the user
			string = str;//setting the string to the string to send
		}
	}
	return string;//sending a pointer with the file name
}

void sending_line_to_a_server(FILE* file) {//creating a list from the file
	char* line = NULL;
	char* trash = NULL;
	while (!(feof(file))) {// checking whether the end of the file has been reached
	printf("sending_line_to_a_server => GettingLine\n");
        line = GettingLine(file);//send to get a line from the file
		if (line != NULL && *line != '\n') {
			printf("sending_line_to_a_server => send\n");
            send(sock, line, strlen(line), 0);
			trash = recv_();
			free(trash);
		}
        if(line)
        {
            free(line);
            line = NULL;
        }
	}
	printf("send_(0)");
    send_("0");
	printf("recv_(0)");
	trash = recv_();
	free(trash);
}