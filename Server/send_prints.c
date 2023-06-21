#include "PrintingManager.h"

void print_instructions()
{
	send_("\t\tWELCOME!\n\tThis program displays the debts from the file.");
	send_("\n\tAbove in the table are all the debtors that exist in the file.");
	send_("\n\n\tYou can add a debt or payment by adding a line to the file.");
	send_("\n\tIn order to add, all the details of the customer must be entered First name, Last name, ID,");
	send_("\n\tPhone, Debt and date(two digits for the day, two digits for the month, four digits for the year).");
	send_("\n\tFor example : \"Set First name = Arie, Last name = Tzvible, ID = 123456789, Phone = 0548484848,");
	send_("\n\tDate = 05/07/2022, Debt = -250.36\".");
	send_("\n\n\tYou can also sort by any existing parameter and the system will print according to the request:");
	send_("\n\tFirst name, Last name, ID, Phone number, Debt and Date(two digits for the day,");
	send_("\n\ttwo digits for the month, four digits for the year)");
	send_("\n\tThe sorting options are : greater: > , less: < , equal : =, and different : !=.");
	send_("\n\tand then enter the value to sort.");
	send_("\n\tFor example : \"Select ID = 123456789\".");
	send_("\n\n\tIn addition, in order to print the list of debtors one more time, you must enter \"Print\".");
	send_("\n\n\tIn addition, in order to print the list of errors one more time, you must enter \"Error\".");
	send_("\n\n\tTo exit, enter \"Quit\".");
}

/*Creating a printable table header*/
void print_table_head(char* print) 
{
	send_("\n\n\t###################################################################################################\n");
	send_("\t#                                                                                                 #\n");
	send_("\t#    *****************************************************************************************    #\n\t#");
	//creating a header in the middle of the table *****
	for (int i = 0; i < (47 - (int)(strlen(print) / 2)); i++)
		send_(" ");
	send_format("%s", print);
	if (strlen(print) % 2 == 0)
		for (int i = 0; i < (49 - (int)(strlen(print) / 2)); i++)
			send_(" ");
	else
		for (int i = 0; i < (49 - (int)(strlen(print) / 2)); i++)
			send_(" ");
	send_("#\n\t#    *****************************************************************************************    #\n");
	send_("\t# =============================================================================================== #\n");//printing subheadings
	send_format("\t# | %-16s | %-15s | %-12s | %-13s | %-10s | %-10s | #\n", " First name:", " Last name:", " ID:",
		" Phon:", " Date:", " Debt:");
	send_("\t# |=============================================================================================| #\n");
}

/*printing a single cell*/
void print_cell(PClient cell) 
{
	send_format("\t# | %-16s | %-15s | %-12s | %-13s | %02d/%02d/%04d | %-10.2f | #\n",
		cell->firstName, cell->lastName, cell->id, cell->phone, cell->date.day,
		cell->date.month, cell->date.year, cell->debt);
}

/*printing a list of debtors*/
void printing_debtors_only(PClient head) 
{
	if (!head) {
		send_("\tThere are no debts in the current list;\n");//print error
		return;
	}
	print_list_debts_from_the_smallest_to_the_largest(head, "List of Debtors  ");//Sending to the function that prints the debt from the largest to the smallest
}

/*print the debt from the largest to the smallest*/
void print_list_debts_from_the_smallest_to_the_largest(PClient head, char* mainTitle) 
{
	PClient temp = head;//Creating a variable that will contain the head of the list
	int flag = 0;
	while (temp != NULL) {//Check that the cell is not empty
		if (temp->debt < 0) {
			if (!flag) {
				print_table_head(mainTitle);
				flag = 1;
			}
			print_cell(temp);//Send to cell print function
			send_("\t# |---------------------------------------------------------------------------------------------| #\n");
		}
		temp = temp->next;//Move the pointer to the next cell
	}
	send_("\t# =============================================================================================== #\n");
	send_("\t#                                                                                                 #\n");
	send_("\t###################################################################################################\n\n\n");
}

/*print the cells with errors*/
void printing_cells_with_errors(PClient head) 
{
	if (head) {
		print_table_head("ERRORS!!   ");//Send to create a table with a header
		PClient temp = head;//creating a pointer to the top of the list
		while (temp) {
			int printsThatWere = 0;//Creating a variable to maintain the integrity of the table
			print_cell(temp);//Cell printing
			if (temp->error.comparisonFirstName || temp->error.comparisonLastName) {
				if (temp->error.comparisonFirstName)
					send_format("\t# |  The first name does not match the ID number -> %s != %-16s               | #", temp->id, temp->firstName);// print error
				if (temp->error.comparisonFirstName && temp->error.comparisonLastName)
					send_("\n");
				if (temp->error.comparisonLastName)
					send_format("\t# |  The last name does not match the ID number -> %s != %-15s                 | #", temp->id, temp->lastName);// print error
			}
			else {
				if (temp->error.lacksValues)
					print_errors("lacks values", &printsThatWere);//Send to error print function
				if (temp->error.id)
					print_errors("I.D.", &printsThatWere);//Send to error print function 
				if (temp->error.firstName)
					print_errors("first name", &printsThatWere);//Send to error print function
				if (temp->error.lastName)
					print_errors("last name", &printsThatWere);//Send to error print function 
				if (temp->error.phone)
					print_errors("phone", &printsThatWere);//Send to error print function
				if (temp->error.date)
					print_errors("date", &printsThatWere);//Send to error print function
				if (temp->error.debt)
					print_errors("debt", &printsThatWere);//Send to error print function			
				if (printsThatWere > 0) {
					for (int i = printsThatWere; i < 92; i++)
						send_(" ");//print spaces until the end of the row in the table
					send_("| #");//closing the row in the table
				}
			}
			send_("\n\t# |---------------------------------------------------------------------------------------------| #\n");

			temp = temp->next;//Move the pointer to the next cell
		}
		send_("\t# =============================================================================================== #\n");
	}

	else if (!head) {//Print when there are no errors
		send_("\n\t###################################################################################################\n");
		send_("\t#                                                                                                 #\n");
		send_("\t#    *****************************************************************************************    #\n");
		send_("\t#                                                                                                 #\n");
		send_("\t#     $$$$$$$$$$$$$$$$$$$$$$$  There are no errors in the client list  $$$$$$$$$$$$$$$$$$$$$$     #\n");
		send_("\t#                                                                                                 #\n");
		send_("\t#    *****************************************************************************************    #\n");
	}
	send_("\t#                                                                                                 #\n");
	send_("\t###################################################################################################\n\n\n");
}

/*print the error*/
void print_errors(char* error, int* printsThatWere) 
{
	if (*printsThatWere == 0) {//print the beginning of the first line of the error notes
		send_("\t# | ERROR! ");
		*printsThatWere += 7;//added to the number of characters printed
	}
	if (*printsThatWere + (strlen(error) + 16) >= 86) {// check that it will not exceed the size of the row in the table
		for (int i = *printsThatWere; i < 86; i++)
			send_(" ");// print spaces until the end of the row in the table
		send_("       | #\n\t# | ");//creating a new row in the table
		*printsThatWere = 0;// Setting the number of printed characters to 0
	}
	if (*printsThatWere != 7) {// checking that it is not a first print
		send_(" and ");
		*printsThatWere += 5;//added to the number of characters printed
	}
	char* buffer = malloc(strlen(error) + strlen("uncorect  ,") + 1);
	        if (buffer != NULL)
        {
			sprintf(buffer, "uncorect %s,", error);
	send_(buffer);
	free(buffer);
	*printsThatWere += ((int)strlen(error) + 10);//added to the number of characters printed
}}

/*Getting for print the sort cell and checking if the flag is raised*/
void print_a_sorted_cell(PClient previousList, int flag) 
{
	if (!flag)//Checking if this is the first time
		print_table_head("Sorted List As Per Your Request");//Sending for printing the table header
	if (previousList->debt < 0) {//	Checking if there is a debt
		print_cell(previousList);//Send to cell print function
		send_("\t# |---------------------------------------------------------------------------------------------| #\n");
	}
}

int printing_similar_customers(PNode node, int flag) {
	if (!node)/*Check if the node is empty*/
		return 0;

	/*Sending the client to print*/
	print_a_sorted_cell(node->client, flag++);

	if (node->nextLike)/*Sending the Similar pointer to print*/
		return 1 + printing_similar_customers(node->nextLike, flag);

	return 1;
}

int printing_clients_in_descending_order(PNode root, int flag) {
	/*Check if the node is empty*/
	if ((!root) || (!root->client))
		return flag;

	if (root->left)/*Sending the right pointer to print*/
		flag += printing_clients_in_descending_order(root->left, flag);

	/*Sending the client and similar pointer to print*/
	flag += printing_similar_customers(root, flag);

	if (root->right)/*Sending the left pointer to print*/
		flag += printing_clients_in_descending_order(root->right, flag);

	return flag;
}

int printing_clients_in_ascending_order(PNode root, int flag) {
	/*check if the node is empty*/
	if ((!root) || (!root->client))
		return flag;

	if (root->right)/*sending the left pointer to print*/
		flag += printing_clients_in_ascending_order(root->right, flag);

	/*sending the client and similar pointer to print*/
	flag += printing_similar_customers(root, flag);

	if (root->left)/*sending the right pointer to print*/
		flag += printing_clients_in_ascending_order(root->left, flag);

	return flag;
}