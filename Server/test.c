#include "PrintingManager.h"

/*Creating a printable table header*/
void print_table_head(char** buffer, char *print)
{
	creating_a_string_with_variables(buffer, "\
	\n\n\t###################################################################################################\
	\n\t#                                                                                                 #\
	\n\t#    *****************************************************************************************    #\n\t#");
	// creating a header in the middle of the table *****
	char* str_space = create_string_by_ch(48 - (int)(strlen(print) / 2), ' ');	
	creating_a_string_with_variables(buffer, "%s%s%s", str_space, print, str_space);
	free(str_space);
	creating_a_string_with_variables(buffer, "#\
	\n\t#    *****************************************************************************************    #\
	\n\t# =============================================================================================== #\
	\n\t# |  First name:     |  Last name:     |  ID:         |  Phon:        |  Date:     |  Debt:     | #\
	\n\t# |=============================================================================================| #\n");	
}

/*printing a single cell*/
void print_cell(PClient cell, char** buffer)
{
	creating_a_string_with_variables(buffer, "\t# | %-16s | %-15s | %-12s | %-13s | %02d/%02d/%04d | %-10.2f | #\n",\
	cell->firstName, cell->lastName, cell->id, cell->phone, cell->date.day,cell->date.month, cell->date.year, cell->debt);
}

/*printing a list of debtors*/
void printing_debtors_only(PClient head)
{
printf("printing_debtors_only\n");
	if (!head)
	{
		print_send("\tThere are no debts in the current list;\n"); // print 
		return;
	}
	print_list_debts_from_the_smallest_to_the_largest(head, "List of Debtors  "); // Sending to the function that prints the debt from the largest to the smallest
}

/*print the debt from the largest to the smallest*/
void print_list_debts_from_the_smallest_to_the_largest(PClient head, char *mainTitle)
{
//printf("print_list_debts_from_the_smallest_to_the_largest\n");
	PClient temp = head; // Creating a variable that will contain the head of the list
	char** buffer = (char**)malloc(sizeof(char*));
	*buffer = NULL;
	print_table_head(buffer, mainTitle);
	while (temp != NULL)
	{ // Check that the cell is not empty
		if (temp->debt < 0)
		{
//printf("print_list_debts_from_the_smallest_to_the_largest => print_cell\n");
			print_cell(temp, buffer); // Send to cell print function
			creating_a_string_with_variables(buffer, "\t# |---------------------------------------------------------------------------------------------| #\n");
		}
		temp = temp->next; // Move the pointer to the next cell
	}
//printf("print_list_debts_from_the_smallest_to_the_largest => creating_a_string_with_variables");
	creating_a_string_with_variables(buffer, "\t# =============================================================================================== #\
	\n\t#                                                                                                 #\
	\n\t###################################################################################################\n\n\n\0");
//printf("print_list_debts_from_the_smallest_to_the_largest => send\n%d\n%s",strlen(*buffer), *buffer);
	print_send(*buffer);
	if(*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	if(buffer)
	{
		free(buffer);
		buffer = NULL;
	}
}

/*Getting for print the sort cell and checking if the flag is raised*/
void print_a_sorted_cell(PClient previousList, int flag, char** buffer)
{
	if (!flag)												 // Checking if this is the first time
		print_table_head(buffer, "Sorted List As Per Your Request"); // Sending for printing the table header
	if (previousList->debt < 0)
	{							  //	Checking if there is a debt
		print_cell(previousList, buffer); // Send to cell print function
		creating_a_string_with_variables(buffer, "\t# |---------------------------------------------------------------------------------------------| #\n");
	}
}

int printing_similar_customers(PNode node, int flag, char** buffer)
{
	if (!node) /*Check if the node is empty*/
		return 0;

	/*Sending the client to print*/
	print_a_sorted_cell(node->client, flag++, buffer);

	if (node->nextLike) /*Sending the Similar pointer to print*/
		return 1 + printing_similar_customers(node->nextLike, flag, buffer);

	return 1;
}

int printing_clients_in_descending_order(PNode root, int flag, char** buffer)
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

int printing_clients_in_ascending_order(PNode root, int flag, char** buffer)
{
	/*check if the node is empty*/
	if ((!root) || (!root->client))
		return flag;

	if (root->right) /*sending the left pointer to print*/
		flag += printing_clients_in_ascending_order(root->right, flag, buffer);

	/*sending the client and similar pointer to print*/
	flag += printing_similar_customers(root, flag, buffer);

	if (root->left) /*sending the right pointer to print*/
		flag += printing_clients_in_ascending_order(root->left, flag, buffer);

	return flag;
}

char* create_string_by_ch(int size, char ch)
{
	printf("create_string_by_ch => %d\n", size);
	char *string = malloc(size);
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

