

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

int testingFirstName(void *value, PClient client)
{													 // First name check (specific)
	return strcmp((char *)value, client->firstName); // Comparison of the strings
}
int testingLastName(void *value, PClient client)
{													// Last name check (specific)
	return strcmp((char *)value, client->lastName); // Comparison of the strings
}
int testingID(void *value, PClient client)
{											  // ID check (specific)
	return strcmp((char *)value, client->id); // Comparison of the strings
}
int testingPhone(void *value, PClient client)
{												 // Phone check (specific)
	return strcmp((char *)value, client->phone); // Comparison of the strings
}
int testingDebt(void *value, PClient client)
{ // Debt check (specific)
	if (*(float *)value < client->debt)
		return -1;
	if (*(float *)value > client->debt)
		return 1;
	return 0;
}
int testingDate(void *value, PClient client)
{														 // Date check (specific)
	return comparingDates(*(Date *)value, client->date); // Debt comparison
}

int main()
{
	init_server();

	while (1)
	{
		char *buffer = NULL;

		my_listen();

		ListManager manager_client_list = init_a_new_list_manager(); // Creating a new manageme structure.
printf("create_list_of_customers_from_a_client\n");
		create_list_of_customers_from_a_client(manager_client_list);
printf("creatingTreesFromLinkedList\n");
		creatingTreesFromLinkedList(manager_client_list);
printf("printing_debtors_only\n");
		printing_debtors_only(manager_client_list->head);			// Debtors printing.
printf("printing_cells_with_errors\n");
		printing_cells_with_errors(manager_client_list->headError); // Printing the cells with errors
		send_("0");
printf("print_instructions\n");
		print_instructions();

		do
		{
			if (buffer)
				free(buffer);
			send_("Enter your request:\n");

			buffer = recv_();

			// Checking the correctness of the letters and changing uppercase letters to lowercase.
			if (isTheStringCorrect(buffer))
			{
				if (!(strcmp(buffer, "select"))) // Checks if he asked to sort
				{
					send_("PRINT");
					sorting_by_request(manager_client_list); // Sending to a sort function
					send_("0");
				}

				else if (!(strcmp(buffer, "set")))
				{ // Checking whether he asked to add a new customer
					send_("set");
					adding_client_from_user(&manager_client_list); // Sending to the function of adding a new client.
					send_("PRINT");
					send_("\tThe row was received successfully.\n\tThank you very much;\n");
					send_("0");
				}

				else if (!(strcmp(buffer, "print"))) // Checking whether printing was requested.
				{
					send_("PRINT");
					printing_debtors_only(manager_client_list->head); // Debtors printing.
					send_("0");
				}
				else if (!(strcmp(buffer, "error"))) // Checking whether printing was errors.
				{
					send_("PRINT");
					printing_cells_with_errors(manager_client_list->headError); // Printing the cells with errors
					send_("0");
				}
			}

		} while ((strcmp(buffer, "quit"))); // Loop exit conditions
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}
		close(client_sock);
	}

	return 0;
}

// todo *******************************************************************
// todo *******************************************************************
// todo *******************************************************************
// todo *******************************************************************
// todo *******************************************************************
// todo *******************************************************************

// int main_()
// {
// 	// _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//Memory release test

// 	crateArrayTreeAndArrayFuncSort(); // Sending to create an array of sorting functions

// 	char strUse[7] = {0};								   // Create a variable to receive the user's selection.
// 	int file_name_dynamic = 0;							   // Creating a variable to test whether the pointer to the file is dynamic.
// 	char *selection = {0};								   // Create a pointer to receive the user's selection.
// 	char *fileName = {0};								   // Create a pointer to get the file name
// 	char *tempFileName = FILE_NAME;						   // Declaration of a variable containing the file name.
// 	ListManager managerClientList = initANewListManager(); // Creating a new manageme structure.
// 	FILE *debtFile;										   // Create a pointer to the file.

// 	fileName = tempFileName; // Getting the filename for the pointer

// 	while (!(debtFile = fopen(fileName, "r")))
// 	{ // Opening for reading only.
// 		if (file_name_dynamic)
// 			free(fileName);
// 		// Sending to the function of receiving a name from the user (it is not necessary to insert CSV).
// 		fileName = getNewFileName(FILE_NAME_EXTENSION);
// 		file_name_dynamic = 1; // Checking whether we received a dynamic string
// 	}

// 	creatingListOfClientsFromAFile(managerClientList, debtFile); // Building a list from a file.

// 	fclose(debtFile); // Closing a folder.

// 	creatingTreesFromLinkedList(managerClientList);

// 	printingDebtorsOnly(managerClientList->head);		   // Debtors printing.
// 	printingCellsWithErrors(managerClientList->headError); // Printing the cells with errors

// 	printInstructions(); // Printing of instructions.

// 	do
// 	{
// 		printf("\n\n\t--> ");
// 		while (!scanf("%s", strUse))
// 		{ // Receive request from user
// 			printf("\n\n\t--> ");
// 		}
// 		selection = strUse; // Getting the string into a pointer.
// 		if (isTheStringCorrect(selection))
// 		{											 // Checking the correctness of the letters and changing uppercase letters to lowercase.
// 			if (!(strcmp(selection, "select")))		 // Checks if he asked to sort
// 				sortingByRequest(managerClientList); // Sending to a sort function
// 			else if (!(strcmp(selection, "set")))
// 			{ // Checking whether he asked to add a new customer
// 				while (!(debtFile = fopen(fileName, "a")))
// 				{ // Opening the file for writing.
// 					// Sending to the function of receiving a name from the user (it is not necessary to insert CSV).
// 					if (file_name_dynamic)
// 						free(fileName);
// 					fileName = getNewFileName(FILE_NAME_EXTENSION);
// 					file_name_dynamic; // Checking whether we received a dynamic string
// 				}
// 				addingClientFromUser(&managerClientList, debtFile); // Sending to the function of adding a new client.
// 				fclose(debtFile);									// close file.
// 			}
// 			else if (!(strcmp(selection, "print")))								// Checking whether printing was requested.
// 				printingDebtorsOnly(managerClientList->head);					// Debtors printing.
// 			else if (!(strcmp(selection, "error")))								// Checking whether printing was errors.
// 				printingCellsWithErrors(managerClientList->headError);			// Printing the cells with errors
// 			else if ((strcmp(selection, "quit")))								// A test that does not want to leave the program.
// 				printf("\tERROR! The category you requested was not found;\n"); // Error printing.
// 		}
// 		else
// 			printf("\tERROR! Probably characters other than letters appear in the request category;\n"); // Error printing.
// 	} while ((strcmp(selection, "quit")));																 // Loop exit conditions

// 	deletingArrayOfTree();

// 	deletingTheEntireList(managerClientList); // Deleting the list.
// 	if (file_name_dynamic)					  // Checking if the string is dynamic.
// 		free(fileName);						  // Release the string.
// 	printf("\n\tBye Bye!!\n");

// 	return 0;
// }
