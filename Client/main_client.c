// Built by Aryeh Zweibel
//**************************************************** **
// Managing debts in a business from a portfolio
//**************************************************** **
//
// The program sends a CSV file to the server. that in each row, the data appears in the next section:
// First name, last name, social security number, telephone, payment amount and date.
// Each customer can have more than one row, first name and last name must match another identity
// An error will be printed.
// The server returns a list of debtors as well as a list with the errors.
// If there are no errors the server will print this.
//
//************************************
//
// At this point the server will ask the user to enter a request.
// 1: The user can request a printout of all debtors.
// The user must enter "print".
//
//
// 2: The user can request printing according to a certain value with 4 ( = / != / < / > ) sorting options
// big small equal and different,
// For example: "select firstname != lion".
//
//
// 3: You can also add a new line to the customer list
//    Between a new customer and a customer with previous debt.
// All customer fields must be filled in:
// - First name,
// - Last Name,
// - ID,
// - Phone Number,
// - Amount of debt / payment,
// - date.
// For example: "set first name = lion, id = 123456789,..."
//
// -- There is no obligation to enter the values in a particular order.
// -- All details must be entered (otherwise the system will print an error).
//
// The server will send the new line in the file with all the customer details.
// The program will insert the line into the file.
// 4: To exit the program and finish, enter "exit".
// The program will release the list and close the program.
//
#include "HeaderMain.h"

int main()
{
	/*Booting and connecting the client to the server*/
	init_client();

	/*Open file*/
	int file_name_dynamic = 0;		  // Creating a variable to test whether the pointer to the file is dynamic.
	char *line = NULL;				  // Create a pointer to receive the user's selection.
	char *file_name = {0};			  // Create a pointer to get the file name
	char *temp_file_name = FILE_NAME; // Declaration of a variable containing the file name.
	FILE *debt_file;				  // Create a pointer to the file.
	file_name = temp_file_name;		  // Getting the file_name for the pointer
	char *buffer = NULL;

	while (!(debt_file = fopen(file_name, "r")))
	{ // Opening for reading only.
		if (file_name_dynamic)
			free(file_name);
		// Sending to the function of receiving a name from the user (it is not necessary to insert CSV).
		file_name = get_new_file_Name(FILE_NAME_EXTENSION);
		file_name_dynamic = 1; // Checking whether we received a dynamic string
	}
	/************/

	/*Sending the file line by line to the server*/
	sending_line_to_a_server(debt_file);
	fclose(debt_file); // Closing a folder.
	print_recv();//Printing a list of debtors
	print_recv();//printing errors
	print_recv();//Menu printing

	do
	{
		print_recv();
		line = GettingLine(stdin);
		send_server(line);

		if (buffer)
			free(buffer);
		buffer = get_recv();

		if (!strcmp(buffer, "OPEN_FILE"))
		{
			while (!(debt_file = fopen(file_name, "a")))
			{
				if (file_name_dynamic)
					free(file_name);
				file_name = getNewFileName(FILE_NAME_EXTENSION);
				file_name_dynamic = 1; // Checking whether we received a dynamic string
			}
			free(buffer);
			send_server("[+]THE FILE IS OPEN\n");
			buffer = get_recv();
			fprintf(debt_file, "%s", buffer);
			fclose(debt_file); // close file.
			free(buffer);
			buffer = NULL;
			buffer = get_recv();
		}
		if (!strcmp(buffer, "PRINT"))
		{
			print_recv();
		}
	} while ((strcmp(buffer, "quit")));

	/*Receiving a closing instruction from the server and printing them*/
	//****************************************************
	buffer = recv_();
	printf("SERVER: %s", buffer);
	if (buffer)
		free(buffer);
	buffer = NULL;
	close(sock);
	printf("Disconnected from the server.\n\n");
	//****************************************************

	if (file_name_dynamic) // Checking if the string is dynamic.
		free(file_name);   // Release the string.

	printf("\n\tBye Bye!!\n");

	return 0;
}
