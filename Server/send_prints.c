#include "PrintingManager.h"

int prints_that_were = 0;

void print_instructions()
{
	print_send("\t\tWELCOME!\n\tThis program displays the debts from the file.\
		\n\tAbove in the table are all the debtors that exist in the file.\
		\n\n\tYou can add a debt or payment by adding a line to the file.\
		\n\tIn order to add, all the details of the customer must be entered First name, Last name, ID,\
		\n\tPhone, Debt and date(two digits for the day, two digits for the month, four digits for the year).\
		\n\tFor example : \"Set First name = Arie, Last name = Tzvible, ID = 123456789, Phone = 0548484848,\
		\n\tDate = 05/07/2022, Debt = -250.36\".\
		\n\n\tYou can also sort by any existing parameter and the system will print according to the request:\
		\n\tFirst name, Last name, ID, Phone number, Debt and Date(two digits for the day,\
		\n\ttwo digits for the month, four digits for the year)\
		\n\tThe sorting options are : greater: > , less: < , equal : =, and different : !=.\
		\n\tand then enter the value to sort.\
		\n\tFor example : \"Select ID = 123456789\".\
		\n\n\tIn addition, for to print, you must enter \"print\" or \"error\" to print the errors.\
		\n\n\tTo exit, enter \"Quit\".");
}

/*Creating a printable table header*/
void print_table_head(char **buffer, char *print)
{
	creating_a_string_with_variables(buffer, "\
		\n\t###################################################################################################\
		\n\t#                                                                                                 #\
		\n\t#    *****************************************************************************************    #\n\t#");
	// creating a header in the middle of the table
	char *str_space = create_string_by_ch(48 - (int)(strlen(print) / 2), ' ');
	creating_a_string_with_variables(buffer, "%s%s%s", str_space, print, str_space);
	free(str_space);
	creating_a_string_with_variables(buffer, "#\
		\n\t#    *****************************************************************************************    #\
		\n\t# =============================================================================================== #\
		\n\t# |  First name:     |  Last name:     |  ID:         |  Phon:        |  Date:     |  Debt:     | #\
		\n\t# |=============================================================================================| #\n");
}

/*printing a single cell*/
void print_cell(PClient cell, char **buffer)
{
	creating_a_string_with_variables(buffer, "\t# | %-16s | %-15s | %-12s | %-13s | %02d/%02d/%04d | %-10.2f | #\n",
									 cell->firstName, cell->lastName, cell->id, cell->phone, cell->date.day, cell->date.month, cell->date.year, cell->debt);
}

/*printing a list of debtors*/
void printing_debtors_only(PClient head)
{
	if (!head)
	{
		print_send("\tThere are no debts in the current list;\n"); // print error
		return;
	}
	print_list_debts_from_the_smallest_to_the_largest(head, "List of Debtors  "); // Sending to the function that prints the debt from the largest to the smallest
}

/*print the debt from the largest to the smallest*/
void print_list_debts_from_the_smallest_to_the_largest(PClient head, char *mainTitle)
{
	PClient temp = head; // Creating a variable that will contain the head of the list
	char **buffer = (char **)malloc(sizeof(char *));
	*buffer = NULL;
	print_table_head(buffer, mainTitle);
	while (temp != NULL)
	{ // Check that the cell is not empty
		if (temp->debt < 0)
		{
			print_cell(temp, buffer); // Send to cell print function
			creating_a_string_with_variables(buffer, "\t# |---------------------------------------------------------------------------------------------| #\n");
		}
		temp = temp->next; // Move the pointer to the next cell
	}
	creating_a_string_with_variables(buffer, "\t# =============================================================================================== #\
		\n\t#                                                                                                 #\
		\n\t###################################################################################################\n\0");
	print_send(*buffer);
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
}

/*Getting for print the sort cell and checking if the flag is raised*/
void print_a_sorted_cell(PClient previousList, int flag, char **buffer)
{
	if (!flag)														 // Checking if this is the first time
		print_table_head(buffer, "Sorted List As Per Your Request"); // Sending for printing the table header
	if (previousList->debt < 0)										 // Checking if there is a debt
	{
		print_cell(previousList, buffer); // Send to cell print function
		creating_a_string_with_variables(buffer, "\t# |---------------------------------------------------------------------------------------------| #\n");
	}
}

int printing_similar_customers(PNode node, int flag, char **buffer)
{
	if (!node) /*Check if the node is empty*/
		return 0;

	/*Sending the client to print*/
	print_a_sorted_cell(node->client, flag++, buffer);

	if (node->nextLike) /*Sending the Similar pointer to print*/
		return 1 + printing_similar_customers(node->nextLike, flag, buffer);

	return 1;
}

int printing_clients_in_descending_order(PNode root, int flag, char **buffer)
{
	/*Check if the node is empty*/
	if ((!root) || (!root->client))
		return flag;

	if (root->left) /*Sending the right pointer to print*/
		flag += printing_clients_in_descending_order(root->left, flag, buffer);

	/*Sending the client and similar pointer to print*/
	flag += printing_similar_customers(root, flag, buffer);

	if (root->right) /*Sending the left pointer to print*/
		flag += printing_clients_in_descending_order(root->right, flag, buffer);

	return flag;
}

int printing_clients_in_ascending_order(PNode root, int flag, char **buffer)
{
	if ((!root) || (!root->client)) /*check if the node is empty*/
		return flag;

	if (root->right) /*sending the left pointer to print*/
		flag += printing_clients_in_ascending_order(root->right, flag, buffer);

	/*sending the client and similar pointer to print*/
	flag += printing_similar_customers(root, flag, buffer);

	if (root->left) /*sending the right pointer to print*/
		flag += printing_clients_in_ascending_order(root->left, flag, buffer);

	return flag;
}

char *create_string_by_ch(int size, char ch)
{
	char *string = malloc(size + 1);
	if (!string)
	{
		printf("Not enough memory\n");
		return NULL;
	}
	int i;
	for (i = 0; i < size; i++)
		string[i] = ch;
	string[i] = '\0';
	return string;
}

/*print the cells with errors*/
void printing_cells_with_errors(PClient head)
{
	char **buffer = (char **)malloc(sizeof(char *));
	*buffer = NULL;
	PClient temp = head; // creating a pointer to the top of the list

	if (head)
	{
		print_table_head(buffer, "ERRORS!!   "); // Send to create a table with a header
		while (temp)
		{
			prints_that_were = 0;
			print_cell(temp, buffer); // Cell printing
			if (temp->error.comparisonFirstName || temp->error.comparisonLastName)
			{
				if (temp->error.comparisonFirstName)
					creating_a_string_with_variables(buffer, "\t# |  The first name does not match the ID number -> %s != %-16s               | #", temp->id, temp->firstName); // print error
				if (temp->error.comparisonFirstName && temp->error.comparisonLastName)
					creating_a_string_with_variables(buffer, "\n");
				if (temp->error.comparisonLastName)
					creating_a_string_with_variables(buffer, "\t# |  The last name does not match the ID number -> %s != %-15s                 | #", temp->id, temp->lastName); // print error
			}
			else
			{
				if (temp->error.lacksValues)
					print_errors(buffer, "lacks values"); // Send to error print function
				if (temp->error.id)
					print_errors(buffer, "ID"); // Send to error print function
				if (temp->error.firstName)
					print_errors(buffer, "first name"); // Send to error print function
				if (temp->error.lastName)
					print_errors(buffer, "last name"); // Send to error print function
				if (temp->error.phone)
					print_errors(buffer, "phone"); // Send to error print function
				if (temp->error.date)
					print_errors(buffer, "date"); // Send to error print function
				if (temp->error.debt)
					print_errors(buffer, "debt"); // Send to error print function
				if (prints_that_were > 0)
				{

					char *str_space = create_string_by_ch(92 - prints_that_were, ' ');
					creating_a_string_with_variables(buffer, "%s%s", str_space, "| #");
					if (str_space)
						free(str_space);
				}
			}
			creating_a_string_with_variables(buffer, "\
			\n\t# |---------------------------------------------------------------------------------------------| #\n");
			temp = temp->next; // Move the pointer to the next cell
		}
		creating_a_string_with_variables(buffer, "\t# =============================================================================================== #\n");
	}

	else if (!head)
	{ // Print when there are no errors
		creating_a_string_with_variables(buffer, "\
			\n\t###################################################################################################\
			\n\t#                                                                                                 #\
			\n\t#    *****************************************************************************************    #\
			\n\t#                                                                                                 #\
			\n\t#     $$$$$$$$$$$$$$$$$$$$$$$  There are no errors in the client list  $$$$$$$$$$$$$$$$$$$$$$     #\
			\n\t#                                                                                                 #\
			\n\t#    *****************************************************************************************    #\n");
	}
	creating_a_string_with_variables(buffer, "\t#                                                                                                 #\
		\n\t###################################################################################################\n");

	print_send(*buffer);
	free(*buffer);
	*buffer = NULL;
	free(buffer);
	buffer = NULL;
}

void print_errors(char **buffer, char *error)
{
	/*print the beginning of the first line of the error notes*/
	if (prints_that_were == 0)
	{
		creating_a_string_with_variables(buffer, "\t# | ERROR! \0");
		prints_that_were += 7;
	}
	/*check that it will not exceed the size of the row in the table*/
	if (prints_that_were + (strlen(error) + 16) >= 86)
	{
		char *str_space = create_string_by_ch(86 - prints_that_were, ' ');
		creating_a_string_with_variables(buffer, "%s", str_space);
		if (str_space)
			free(str_space);
		creating_a_string_with_variables(buffer, "%s", "       | #\n\t# | ");
		prints_that_were = 0;
	}
	if (prints_that_were != 7) // checking that it is not a first print
	{
		creating_a_string_with_variables(buffer, "%s", " and ");
		prints_that_were += 5; // added to the number of characters printed
	}
	creating_a_string_with_variables(buffer, "%s", "uncorect ");
	creating_a_string_with_variables(buffer, "%s ", error);
	prints_that_were += ((int)strlen(error) + 10); // added to the number of characters printed
}
