
#include "HeaderRequests.h"

PClient create_a_new_cell_from_the_user(char *buffer, char **send_buffer)
{ // Create a new cell from the user
	if (!buffer)
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
						error_printing_and_deleting_a_cell(&cellNew, "\tERROR! It looks like you entered an invalid first name;\n", send_buffer); // printing an error and deleting a cell
						free(value);																											  // Release a value
					}
				}
				else if (!strcmp(parameter, "last name"))
				{								   // testing to which object in the cell we will add
					if (isTheStringCorrect(value)) // Checking the value of the last name
						cellNew->lastName = value; // Getting a last name for the new cell
					if (!(cellNew->lastName))
					{
						error_printing_and_deleting_a_cell(&cellNew, "\tERROR! It looks like you entered an invalid last name;\n", send_buffer); // printing an error and deleting a cell
						free(value);																											 // Release a value
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
						error_printing_and_deleting_a_cell(&cellNew, "\tERROR! It looks like you entered an invalid ID;\n", send_buffer); // printing an error and deleting a cell
						free(value);																									  // Release a value
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
						error_printing_and_deleting_a_cell(&cellNew, "\tERROR! It looks like you entered an invalid phone;\n", send_buffer); // printing an error and deleting a cell
						free(value);																										 // Release a value
					}
				}
				else if (!strcmp(parameter, "debt"))
				{														// testing to which object in the cell we will add
					if (isNegativeFloat(value))							// Checking the value of the debt
						cellNew->debt = stringConversionToFloat(value); // Receiving the number for the client
					if (!(cellNew->debt))
						error_printing_and_deleting_a_cell(&cellNew, "\tERROR! It looks like you entered an invalid debt;\n", send_buffer); // printing an error and deleting a cell
					free(value);																											// Release a value
				}
				else if (!strcmp(parameter, "date"))
				{							 // testing to which object in the cell we will add
					strDate = strdup(value); // Creating a pointer to the head of the string
					free(value);			 // Release a value
				}
				else
				{
					error_printing_and_deleting_a_cell(&cellNew, "\tERROR! There seems to be a mistake in typing the variable;\n", send_buffer); // printing an error and deleting a cell
					free(value);																												 // Release a value
				}
			}
			else
			{
				error_printing_and_deleting_a_cell(&cellNew, "\tERROR! There seems to be a mistake in typing the request;\n", send_buffer); // printing an error and deleting a cell
				free(value);																												// Release a value
			}
		}
		free(parameter); // Release a parameter
		parameter = creatingADynamicCharWithContent(strtok(NULL, "="));
	} while ((parameter != NULL) && (cellNew != NULL));

	if (strDate)
	{
		cellNew->date = creatingANewDateStructure(strDate); // Send to create a date
		if ((!cellNew->date.day || !cellNew->date.month || !cellNew->date.year))
			error_printing_and_deleting_a_cell(&cellNew, "\tERROR! It looks like you entered an invalid date;\n", send_buffer); // printing an error and deleting a cell
		free(strDate);
	}
	if (cellNew != NULL)
	{ // Checking that there are all values
		if (cellNew->firstName == NULL || cellNew->lastName == NULL ||
			cellNew->id == NULL || cellNew->phone == NULL ||
			cellNew->debt == 0 || cellNew->date.day == 0 ||
			cellNew->date.month == 0 || cellNew->date.year == 0)
		{
			error_printing_and_deleting_a_cell(&cellNew, "\tERROR! It seems that not enough values have been entered;\n", send_buffer); // printing an error and deleting a cell
		}
	}
	if (parameter)
		free(parameter);
	free(buffer); // Release a buffer
	return cellNew;
}

/*Sorting and printing function according to the request*/
int test_function(PNode root, void *value, char opr, int (*testing)(void *, PClient), char **buffer)
{
	/*Check if the node is empty*/
	if ((!root) || (!root->client))
		return 0;

	PNode temp = root; // Create a pointer to the first cell in the existing list
	int test;		   // Create a variable to receive the test value
	int flag = 0;	   // Declaration of a variable that checks whether the table header has been printed

	test = testing(value, temp->client); // getting the test value

	if (opr == '!')
	{
		flag += test_function(temp->left, value, opr, testing, buffer);

		/*Sending the client and similar pointer to print*/
		flag += printing_similar_customers(temp, flag, buffer);

		/*Sending the left tree to print*/
		flag += printing_clients_in_ascending_order(temp->right, flag, buffer);
	}

	else if (test < 0)
	{
		if (temp->left)
		{
			flag += test_function(temp->left, value, opr, testing, buffer);
		}
		if (opr == '=')
			return flag;
		if (opr == '>')
		{
			/*Sending the client and similar pointer to print*/
			flag += printing_similar_customers(temp, flag, buffer);

			/*Sending the right tree to print*/
			flag += printing_clients_in_ascending_order(temp->right, flag, buffer);
		}
	}
	else if (test > 0)
	{
		flag += test_function(temp->right, value, opr, testing, buffer);
		if (opr == '=')
			return flag;
		if (opr == '<')
		{
			/*Sending the client and similar pointer to print*/
			flag += printing_similar_customers(temp, flag, buffer);
			/*Sending the left tree to print*/
			flag += printing_clients_in_ascending_order(temp->left, flag, buffer);
		}
	}

	else if (test == 0)
	{
		if (opr == '=')
		{
			/*Sending the client and similar pointer to print*/
			flag += printing_similar_customers(temp, flag, buffer);
			return flag;
		}
	}

	return flag;
}

void sorting_by_request(char *received_buffer)
{
	// Sort by request from the user
	int Bool = 0;
	char *buffer = NULL;
	char *parameter, *value, opr;
	print_send("PRINT");
	// Acceptance of the test operator
	if (strstr(received_buffer, "!="))
		opr = '!';
	else if (strstr(received_buffer, "="))
		opr = '=';
	else if (strstr(received_buffer, ">"))
		opr = '>';
	else if (strstr(received_buffer, "<"))
		opr = '<';
	else
		opr = '\0';

	parameter = creatingADynamicCharWithContent(strtok(received_buffer, "!=<>")); // Receiving the request
	if (!isTheStringCorrect(parameter))											  // Entered an incorrect title
		print_send("\tERROR!  It seems there was an error entering the parameter;\n");
	else
	{
		value = strtok(NULL, "\n"); // receiving the value
		if (value)
		{
			if (opr == '!')
				value++; // Move the pointer to the next cell
			value = creatingADynamicCharWithContent(value);
			if (!(strcmp(parameter, "first name"))) // Checking whether the sorting request is by first name
				if (!isTheStringCorrect(value))		// checking the correctness of the name and changing it from lowercase to uppercase
				{
					print_send("\tERROR! It looks like you entered an invalid first name;\n");
					return;
				}
				else // Sending to a sorting function and printing according to the request
					Bool = test_function(arrayTree[EnFirst]->root, value, opr, arrSortfunc[EnFirst], &buffer);
			else if (!(strcmp(parameter, "last name"))) // Checking whether the sorting request is by last name
				if (!isTheStringCorrect(value))			// checking the correctness of the name and changing it from lowercase to uppercase
				{
					print_send("\tERROR! It looks like you entered an invalid last name;\n");
					return;
				}
				else // Sending to a sorting function and printing according to the request
					Bool = test_function(arrayTree[EnLast]->root, value, opr, arrSortfunc[EnLast], &buffer);
			else if (!(strcmp(parameter, "id"))) // Checking whether the sorting request is by ID
				if (strlen(value) != ID || !isInt(value))
				{
					print_send("\tERROR! It looks like you entered an invalid id; \n");
					return;
				}
				else // Sending to a sorting function and printing according to the request
					Bool = test_function(arrayTree[EnID]->root, value, opr, arrSortfunc[EnID], &buffer);
			else if (!(strcmp(parameter, "phone"))) // Checking whether the sorting request is by phone
				if (strlen(value) != PHONE || !isInt(value))
				{
					print_send("\tERROR! It looks like you entered an invalid phone;\n");
					return;
				}
				else // Sending to a sorting function and printing according to the request
					Bool = test_function(arrayTree[EnPhone]->root, value, opr, arrSortfunc[EnPhone], &buffer);
			else if (!(strcmp(parameter, "debt")))
			{
				if (!isNegativeFloat(value)) // Checking whether the sorting request is by debt
				{
					print_send("\tERROR! It looks like you entered an invalid debt;\n");
					return;
				}
				else
				{
					float sumDebt = stringConversionToFloat(value); // creating a variable to receive the debt from the string
					// Sending to a sorting function and printing according to the request
					Bool = test_function(arrayTree[EnDebt]->root, &sumDebt, opr, arrSortfunc[EnDebt], &buffer);
				}
			}
			else if (!(strcmp(parameter, "date")))
			{
				Date date = creatingANewDateStructure(value); // send to create a date
				if (!date.day || !date.month || !date.year)
				{
					print_send("\tERROR! It looks like you entered an invalid date;\n");
					return;
				}
				else // Sending to a sorting function and printing according to the request
					Bool = test_function(arrayTree[EnDate]->root, &date, opr, arrSortfunc[EnDate], &buffer);
			}
			else
			{
				print_send("\tERROR! It seems there was an error entering the request;\n");
				return;
			}
		}
		else
		{
			print_send("\tERROR! It seems there was an error entering the request;\n");
			return;
		}
		free(value); // Release a value
	}

	if (!Bool)
	{
		print_send("\tThere are no debts in the current list;\n");
		return;
	}
	else
	{
		creating_a_string_with_variables(&buffer,
										 "\t# =============================================================================================== #\
			\n\t#                                                                                                 #\
			\n\t###################################################################################################\n\n\n");
	}
	free(parameter); // Release a parameter
	print_send(buffer);
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
}

// printing a buffer from the user to the file
void adding_client_from_user(ListManager *list, char *received_buffer)
{
	char **send_buffer = (char **)malloc(sizeof(char *));
	*send_buffer = NULL;
	PClient cellNew, temp, prev = NULL;
	cellNew = create_a_new_cell_from_the_user(received_buffer, send_buffer); // Create a new cell
	temp = (*list)->head;													 // creating a pointer to the first cell
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
		}
		if (cellNew)
		{
			if (cellNew->error.ERROR)
			{
				creating_a_string_with_variables(send_buffer, "\t ERROR! The");
				// printing an error and deleting a cell in case the names and names do not match
				if (cellNew->error.comparisonFirstName && cellNew->error.comparisonLastName)
					creating_a_string_with_variables(send_buffer, " first and last ");
				else if (cellNew->error.comparisonFirstName)
					creating_a_string_with_variables(send_buffer, " first ");
				else if (cellNew->error.comparisonLastName)
					creating_a_string_with_variables(send_buffer, " last ");
				deleting_a_cell_from_the_list(&cellNew);
				creating_a_string_with_variables(send_buffer, "name you entered does not seem to match the ID you entered;\n");
				send_client("PRINT");
				send_client(*send_buffer);
				free(*send_buffer);
			}
			else
			{
				send_client("OPEN_FILE");
				char **buffer = (char **)malloc(sizeof(char *));
				*buffer = get_recv(); // Receiving a row from the user
				free(*buffer);
				*buffer = NULL;
				creating_a_string_with_variables(buffer, "\n%s,%s,%s,%s,%.2f,%02d/%02d/%04d",
												 cellNew->firstName, cellNew->lastName, cellNew->id, cellNew->phone,
												 cellNew->debt, cellNew->date.day, cellNew->date.month, cellNew->date.year);
				send_client(*buffer);
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
					// Sending for sorting and adding to the list
					addingASortedCustomerToTheList(&(*list)->head, temp);
					deleting_a_cell_from_the_list(&cellNew);
				}
				else
				{
					// Sending for sorting and adding to the list
					addingASortedCustomerToTheList(&(*list)->head, cellNew);
					nsertingAClientIntoAllSortingTrees(cellNew);
				}
				free(*buffer);
				*buffer = NULL;
			}
		}
	}
	if (received_buffer)
		free(received_buffer);
}
