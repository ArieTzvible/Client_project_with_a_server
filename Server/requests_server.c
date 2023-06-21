
#include "HeaderRequests.h"

PClient create_a_new_cell_from_the_user(char *buffer)
{ // Create a new cell from the user
	if (!*buffer)
		return NULL;						  // Checking that the string is not empty
	PClient cellNew = initErrorsinAnewCell(); // Creating a new client
	if (!cellNew)
		return NULL;												  // Checking that the allocation was successful
	char *parameter, *value, *strDate = NULL;						  // Declaration of variables that will hold parenter and test value
	parameter = creatingADynamicCharWithContent(strtok(buffer, "=")); // Accepting the test parameter without spaces
	do
	{
		value = creatingADynamicCharWithContent(strtok(NULL, ",")); // Receiving the value without profits
		if (value)
		{
			if (isTheStringCorrect(parameter))
			{
				if (!strcmp(parameter, "first name"))
				{									// testing to which object in the cell we will add
					if (isTheStringCorrect(value))	// Checking the value of the first name
						cellNew->firstName = value; // Getting a first name for the new cell
					if (!(cellNew->firstName))
					{
						error_printing_and_deleting_a_cell(&cellNew, "\tERROR! It looks like you entered an invalid first name;\n"); // printing an error and deleting a cell
						free(value);																							// Release a value
					}
				}
				else if (!strcmp(parameter, "last name"))
				{								   // testing to which object in the cell we will add
					if (isTheStringCorrect(value)) // Checking the value of the last name
						cellNew->lastName = value; // Getting a last name for the new cell
					if (!(cellNew->lastName))
					{
						error_printing_and_deleting_a_cell(&cellNew, "\tERROR! It looks like you entered an invalid last name;\n"); // printing an error and deleting a cell
						free(value);																						   // Release a value
					}
				}
				else if (!strcmp(parameter, "id"))
				{ // testing to which object in the cell we will add
					if (isInt(value) && strlen(value) == ID)
					{						 // Checking the value of the ID
						cellNew->id = value; // Getting a ID for the new cell
					}
					if (!(cellNew->id))
					{
						error_printing_and_deleting_a_cell(&cellNew, "\tERROR! It looks like you entered an invalid ID;\n"); // printing an error and deleting a cell
						free(value);																					// Release a value
					}
				}
				else if (!strcmp(parameter, "phone"))
				{ // testing to which object in the cell we will add
					if (isInt(value) && strlen(value) == PHONE)
					{							// Checking the value of the phone
						cellNew->phone = value; // Getting a phone for the new cell
					}
					if (!cellNew->phone)
					{
						error_printing_and_deleting_a_cell(&cellNew, "\tERROR! It looks like you entered an invalid phone;\n"); // printing an error and deleting a cell
						free(value);																					   // Release a value
					}
				}
				else if (!strcmp(parameter, "debt"))
				{														// testing to which object in the cell we will add
					if (isNegativeFloat(value))							// Checking the value of the debt
						cellNew->debt = stringConversionToFloat(value); // Receiving the number for the client
					if (!(cellNew->debt))
						error_printing_and_deleting_a_cell(&cellNew, "\tERROR! It looks like you entered an invalid debt;\n"); // printing an error and deleting a cell
					free(value);																						  // Release a value
				}
				else if (!strcmp(parameter, "date"))
				{							 // testing to which object in the cell we will add
					strDate = strdup(value); // Creating a pointer to the head of the string
					free(value);			 // Release a value
				}
				else
				{
					error_printing_and_deleting_a_cell(&cellNew, "\tERROR! There seems to be a mistake in typing the variable;\n"); // printing an error and deleting a cell
					free(value);																							   // Release a value
				}
			}
			else
			{
				error_printing_and_deleting_a_cell(&cellNew, "\tERROR! There seems to be a mistake in typing the request;\n"); // printing an error and deleting a cell
				free(value);																							  // Release a value
			}
		}
		free(parameter); // Release a parameter
		parameter = creatingADynamicCharWithContent(strtok(NULL, "="));
	} while ((parameter != NULL) && (cellNew != NULL));

	if (strDate)
	{
		cellNew->date = creatingANewDateStructure(strDate); // Send to create a date
		if ((!cellNew->date.day || !cellNew->date.month || !cellNew->date.year))
			error_printing_and_deleting_a_cell(&cellNew, "\tERROR! It looks like you entered an invalid date;\n"); // printing an error and deleting a cell
		free(strDate);
	}
	if (cellNew != NULL)
	{ // Checking that there are all values
		if (cellNew->firstName == NULL || cellNew->lastName == NULL ||
			cellNew->id == NULL || cellNew->phone == NULL ||
			cellNew->debt == 0 || cellNew->date.day == 0 ||
			cellNew->date.month == 0 || cellNew->date.year == 0)
		{
			error_printing_and_deleting_a_cell(&cellNew, "\tERROR! It seems that not enough values have been entered;\n"); // printing an error and deleting a cell
		}
	}
	if (parameter)
		free(parameter);
	free(buffer); // Release a buffer
	return cellNew;
}

int test_function(PNode root, void *value, char opr, int (*testing)(void *, PClient))
{ // Sorting and printing function according to the request
	/*Check if the node is empty*/
	if ((!root) || (!root->client))
		return 0;

	PNode temp = root;					 // Create a pointer to the first cell in the existing list
	int test;							 // Create a variable to receive the test value
	int flag = 0;						 // Declaration of a variable that checks whether the table header has been printed
	test = testing(value, temp->client); // getting the test value

	if (opr == '!')
	{
		flag += test_function(temp->left, value, opr, testing);

		/*Sending the client and similar pointer to print*/
		flag += printing_similar_customers(temp, flag);

		/*Sending the left tree to print*/
		flag += printing_clients_in_ascending_order(temp->right, flag);
	}

	else if (test < 0)
	{
		if (temp->left)
		{
			flag += test_function(temp->left, value, opr, testing);
		}
		if (opr == '=')
			return flag;
		if (opr == '>')
		{
			/*Sending the client and similar pointer to print*/
			flag += printing_similar_customers(temp, flag);

			/*Sending the right tree to print*/
			flag += printing_clients_in_ascending_order(temp->right, flag);
		}
	}
	else if (test > 0)
	{
		flag += test_function(temp->right, value, opr, testing);
		if (opr == '=')
			return flag;
		if (opr == '<')
		{
			/*Sending the client and similar pointer to print*/
			flag += printing_similar_customers(temp, flag);
			/*Sending the left tree to print*/
			flag += printing_clients_in_ascending_order(temp->left, flag);
		}
	}

	else if (test == 0)
	{
		if (opr == '=')
		{
			/*Sending the client and similar pointer to print*/
			flag += printing_similar_customers(temp, flag);
			return flag;
		}
	}

	return flag;
}

void sorting_by_request()
{ // Sort by request from the user
	int Bool = 0;
	char *buffer, *parameter, opr, *value;
	buffer = recv_(); // Receiving a row from the user
	if (!*buffer)
	{
		free(buffer);
		return; // Test that the string is not empty
	}
	// Acceptance of the test operator
	if (strstr(buffer, "!="))
		opr = '!';
	else if (strstr(buffer, "="))
		opr = '=';
	else if (strstr(buffer, ">"))
		opr = '>';
	else if (strstr(buffer, "<"))
		opr = '<';
	else
		opr = '\0';

	parameter = creatingADynamicCharWithContent(strtok(buffer, "!=<>"));		  // Receiving the request
	if (!isTheStringCorrect(parameter))											  // Entered an incorrect title
		send_("\tERROR!  It seems there was an error entering the parameter;\n"); // print error
	else
	{
		value = strtok(NULL, "\n"); // receiving the value
		if (value)
		{
			if (opr == '!')
				value++; // Move the pointer to the next cell
			value = creatingADynamicCharWithContent(value);
			if (!(strcmp(parameter, "first name")))										  // Checking whether the sorting request is by first name
				if (!isTheStringCorrect(value))											  // checking the correctness of the name and changing it from lowercase to uppercase
					send_("\tERROR! It looks like you entered an invalid first name;\n"); // print error
				else
					Bool = test_function(arrayTree[EnFirst]->root, value, opr, arrSortfunc[EnFirst]); // Sending to a sorting function and printing according to the request
			else if (!(strcmp(parameter, "last name")))												 // Checking whether the sorting request is by last name
				if (!isTheStringCorrect(value))														 // checking the correctness of the name and changing it from lowercase to uppercase
					printf("\tERROR! It looks like you entered an invalid last name;\n");			 // print error
				else
					Bool = test_function(arrayTree[EnLast]->root, value, opr, arrSortfunc[EnLast]); // Sending to a sorting function and printing according to the request
			else if (!(strcmp(parameter, "id")))												   // Checking whether the sorting request is by ID
				if (strlen(value) != ID || !isInt(value))
					send_("\tERROR! It looks like you entered an invalid id; \n"); // print error
				else
					Bool = test_function(arrayTree[EnID]->root, value, opr, arrSortfunc[EnID]); // Sending to a sorting function and printing according to the request
			else if (!(strcmp(parameter, "phone")))											   // Checking whether the sorting request is by phone
				if (strlen(value) != PHONE || !isInt(value))
					send_("\tERROR! It looks like you entered an invalid phone;\n"); // print error
				else
					Bool = test_function(arrayTree[EnPhone]->root, value, opr, arrSortfunc[EnPhone]); // Sending to a sorting function and printing according to the request
			else if (!(strcmp(parameter, "debt")))
			{ // Checking whether the sorting request is by debt
				if (!isNegativeFloat(value))
					send_("\tERROR! It looks like you entered an invalid debt;\n"); // print error
				else
				{
					float sumDebt = stringConversionToFloat(value);									  // creating a variable to receive the debt from the string
					Bool = test_function(arrayTree[EnDebt]->root, &sumDebt, opr, arrSortfunc[EnDebt]); // Sending to a sorting function and printing according to the request
				}
			}
			else if (!(strcmp(parameter, "date")))
			{												  // Checking whether the sorting request is by date
				Date date = creatingANewDateStructure(value); // send to create a date
				if (!date.day || !date.month || !date.year)
					send_("\tERROR! It looks like you entered an invalid date;\n"); // print error
				else
					Bool = test_function(arrayTree[EnDate]->root, &date, opr, arrSortfunc[EnDate]); // Sending to a sorting function and printing according to the request
			}
			else
				send_("\tERROR! It seems there was an error entering the request;\n"); // print error
		}
		else
			send_("\tERROR! It seems there was an error entering the request;\n"); // print error
		free(value);															   // Release a value
	}

	if (!Bool)
		send_("\tThere are no debts in the current list;\n"); // Print error

	else
	{
		send_("\t# =============================================================================================== #\n");
		send_("\t#                                                                                                 #\n");
		send_("\t###################################################################################################\n\n\n");
	}
	free(parameter); // Release a parameter
	free(buffer);	 // Release a buffer
}

void adding_client_from_user(ListManager *list)
{							// printing a buffer from the user to the file
	char *buffer = recv_(); // Receiving a row from the user
	PClient cellNew, temp, prev = NULL;
	cellNew = create_a_new_cell_from_the_user(buffer); // Create a new cell
	temp = (*list)->head;						 // creating a pointer to the first cell
	if (cellNew)
	{
		int Comparison = 0; // variable that will contain the comparison between two cells
		if (!(*list)->head)
		{							 // checking whether the first cell is empty
			(*list)->head = cellNew; // Put the beginning and end of the list in the new cell
		}
		else
		{
			do
			{
				Comparison = comparisonOfCells(&cellNew, &temp);
				if (Comparison) // Checking whether the ID exists
					break;
				prev = temp;
				temp = temp->next; // Move the pointer to the next cell

			} while (temp && cellNew && !cellNew->error.ERROR);
			// checking that the list is not at the end or that the cell is empty or that there is an error in the cell
		}
		if (cellNew)
		{
			if (cellNew->error.ERROR)
			{
				send_("PRINT");
				send_("\t ERROR! The");
				// printing an error and deleting a cell in case the names and names do not match
				if (cellNew->error.comparisonFirstName && cellNew->error.comparisonLastName)
					send_(" first and last ");
				else if (cellNew->error.comparisonFirstName)
					send_(" first ");
				else if (cellNew->error.comparisonLastName)
					send_(" last ");
				error_printing_and_deleting_a_cell(&cellNew, "name you entered does not seem to match the ID you entered");
				send_("0");
			}
			else
			{
				send_("OPEN_FILE");
				send_format("%s,%s,%s,%s,%.2f,%02d/%02d/%04d\n", cellNew->firstName, cellNew->lastName,
					  cellNew->id, cellNew->phone, cellNew->debt, cellNew->date.day, cellNew->date.month, cellNew->date.year);
				send_("0");
				if (Comparison && temp)
				{										// Checking whether the ID is vequal to one of the existing customers
					cellUpdateInTrees(&cellNew, &temp); // updating the cell and releasing the new cell
					if (prev)
					{
						prev->next = temp->next;
					}
					else
					{
						(*list)->head = temp->next;
					}
					temp->next = NULL;
					addingASortedCustomerToTheList(&(*list)->head, temp); // Sending for sorting and adding to the list
					deleting_a_cell_from_the_list(&cellNew);
				}
				else
				{
					addingASortedCustomerToTheList(&(*list)->head, cellNew); // Sending for sorting and adding to the list
					nsertingAClientIntoAllSortingTrees(cellNew);
				}
			}
		}
	}
}