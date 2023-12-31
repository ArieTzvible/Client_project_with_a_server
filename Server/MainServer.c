

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

int testing_first_name(void *value, PClient client)
{													 // First name check (specific)
	return strcmp((char *)value, client->firstName); // Comparison of the strings
}
int testing_last_name(void *value, PClient client)
{													// Last name check (specific)
	return strcmp((char *)value, client->lastName); // Comparison of the strings
}
int testing_ID(void *value, PClient client)
{											  // ID check (specific)
	return strcmp((char *)value, client->id); // Comparison of the strings
}
int testing_phone(void *value, PClient client)
{												 // Phone check (specific)
	return strcmp((char *)value, client->phone); // Comparison of the strings
}
int testing_debt(void *value, PClient client)
{ // Debt check (specific)
	if (*(float *)value < client->debt)
		return -1;
	if (*(float *)value > client->debt)
		return 1;
	return 0;
}
int testing_date(void *value, PClient client)
{														 // Date check (specific)
	return comparing_dates(*(Date *)value, client->date); // Debt comparison
}

int main()
{
	char *buffer = NULL;
	
	init_server();
	my_listen();

	crate_array_tree_and_array_func_sort();// Sending to create an array of sorting functions
	ListManager manager_client_list = init_a_new_list_manager(); // Creating a new manageme structure.
	create_list_of_customers_from_a_client(manager_client_list);
	creating_trees_from_linked_list(manager_client_list);
	printing_debtors_only(manager_client_list->head); // Debtors printing.
	printing_cells_with_errors(manager_client_list->headError); // Printing the cells with errors
	print_instructions();

	do
	{
		if (buffer)
			free(buffer);
		send_client("your request: ");
		buffer = get_recv();
		char *choice = strtok(buffer, " \0");
		if (is_the_string_correct(choice))
		{
			if (!(strncmp(buffer, "select", 6))) // Checks if he asked to sort
			{
				choice = strtok(NULL, "\0");
				sorting_by_request(choice); // Sending to a sort function
			}

			else if (!(strncmp(buffer, "set", 3)))
			{ // Checking whether he asked to add a new customer
				choice = strtok(NULL, "\0");
				adding_client_from_user(&manager_client_list, choice); // Sending to the function of adding a new client.
				send_client("PRINT");
				send_client("\tThe row was received successfully.\n\tThank you very much;\n");
			}

			else if (!(strncmp(buffer, "print", 5))) // Checking whether printing was requested.
			{
				send_client("PRINT");
				printing_debtors_only(manager_client_list->head); // Debtors printing.
			}
			else if (!(strncmp(buffer, "error", 5))) // Checking whether printing was errors.
			{
				send_client("PRINT");
				printing_cells_with_errors(manager_client_list->headError); // Printing the cells with errors
			}
			else if((strncmp(buffer, "quit", 4)))
			{
				send_client("Invalid input\n");
			}
		}
	} while ((strncmp(buffer, "quit", 4))); // Loop exit conditions
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
	send_client("quit");
	send_client("BYE BYE ;)\n");
	close(client_sock);
	return 0;
}
