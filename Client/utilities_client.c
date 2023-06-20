#include "HeaderUtilities.h"


/*Sending a line from the file to the server*/
int getting_line(FILE* file, char* line) {//getting a complete line from the file
	char* input = NULL;//statement about a pointer to a row that the user entered
	char string[1024];//Declaration of a variable
	fgets(string, 1024, file);//Getting a string from the file
	if (feof(file)) return NULL;//Returning NULL when reaching the end of the file
	input = strdup(string);//Creating a variable and copying the string
	if (!input) {// checking whether there is space in the memory
		printf("Not enough memory\n");//Error printing when there is no space in memory
		return input;
	}
	if (input[strlen(input) - 1] == '\n' || input[strlen(input) - 1] == '\0') {//Checking whether the entire line was received
		input[strlen(input) - 1] = '\0';//Changing the last cell to \0
		return input;
	}

	char tempBuf[CHUNK] = { 0 };//Declaration of a variable to receive values from the user
	size_t tempLen = 0, inputLen = strlen(input);//declaration of variables to test the length of the received line
	do {
		fgets(tempBuf, CHUNK, file);// getting 10 cells from the row
		tempLen = (int)strlen(tempBuf);//put the number of characters received
		char* temp = (char*)realloc(input, (inputLen + tempLen + 1) * sizeof(char));//adding space to receive the string
		if (!temp) {// checking whether there is space in the memory
			printf("Not enough memory\n");//Error printing when there is no space in memory
			return input;
		}
		else
			input = temp;//getting the new length of the string
		strcpy(input + inputLen, tempBuf);// Copy from the last location we copied
		inputLen += tempLen;//Getting the current string length

	} while (tempLen == CHUNK - 1 && tempBuf[CHUNK - 2] != '\n');
	if (input[strlen(input) - 1] == '\n')// Checking if the last location contains '\n'
		input[strlen(input) - 1] = '\0';//set the last place to \0
	else {//
		char* temp = (char*)realloc(input, (strlen(input) + 1) * sizeof(char));//Add a space to the string
		if (!temp) {// checking whether there is space in the memory
			printf("Not enough memory\n");//Error printing when there is no space in memory
			return input;
		}
		else {//If the end of the file is reached (in the case of reading from a file)
			input = temp;//getting the new length of the string
			input[strlen(input)] = '\0'; // set the last place to \0
		}
	}
    line = input;
	return strlen(input);
}