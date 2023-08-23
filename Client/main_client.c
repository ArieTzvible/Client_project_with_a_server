

//   Built by Arie Tzvible
//***********************************************
// Managing debts in a business from a portfolio
//***********************************************
//
// The program reading a CSV file.That in every row, the data appears in the following section:
// First name, last name, social security number, telephone, amount dueand date.
// Any customer can receivemore than one line, first nameand last name must match ID otherwise
// will be printed Error.
//
// The program builds a linked list where each customer has one cell that is updated with all
// debts or the payments and also updates the date to the most recent date, the customer's phone
// is also updated according to the most recent date.
// In addition, the system checks whether there is an error in each lineand updates it in the error list.
//
// The program then print the list of customers who have a debt.
// In addition, the program will be printing list with the errorsand notes where the errors are,
// if there are no errors the system will notify.
//
//***********************************
//
// At this point the system will issue a request to the user to enter a request.
// The user can request a to wiil print of of all debtors.
// The user must log in "print".
//
//
// Another option is printing according to a certain value with 4 ( = / != / < / > ) sorting options
// big small equal and different,
//     For example: "Select First name != Arie".
//
//
// You can also add a new line to the customer list.
// All customer fields must be filled in:
// - first name,
// - last name,
// - ID,
// - phone number,
// - amount of debt / payment,
// - date.
// For example : "set first name = Arie, ID = 123456789,..."
//
// -- There is no obligation to enter the values in a particular order.
// -- All details must be entered(otherwise the system will print an error).
//
// The system will print a new line in the file with all the customer's details.
// If the customer exists, we will add the debt, if necessary we will update the details(date and phone).
// If the client does not exist we will add the client to the list.
//
// In order to exit the program and finish, enter "Quit".
// The program will release the list and close the program.
//
#include "HeaderMain.h"

int main()
{
	/*Booting and connecting the client to the server*/
	init_client();
	/**************************/

	/*Open file*/
	// char str_user[7] = {0};		  // Create a variable to receive the user's selection.
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
	printf("sending_line_to_a_server\n");
	sending_line_to_a_server(debt_file);
printf("fclose(debt_file)\n");
	fclose(debt_file); // Closing a folder.


printf("\nprint:\n");
	print_recv();

printf("error\n");
	// print_recv();


printf("menu\n");
	// print_recv();


	do
	{
printf("while choice\n");
		print_recv();

		// scanf("%s", str_user);
		// send_server(str_user);
		// // if()
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
//! **********************************************
printf("buffer: %s\n", buffer);
	} while ((strcmp(buffer, "quit")));
	buffer = recv_();
	printf("SERVER: %s", buffer);
	free(buffer);
	buffer = NULL;
	close(sock);
	printf("Disconnected from the server.\n\n");

	if (file_name_dynamic) // Checking if the string is dynamic.
		free(file_name);   // Release the string.
	printf("\n\tBye Bye!!\n");

	return 0;
}
