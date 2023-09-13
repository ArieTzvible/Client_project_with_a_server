
#include "HeaderTree.h"
#include "Globals.h"

//**** AVL *******
PNode inspection_and_repair_of_AVL_tree(PNode root, void* val, int (*sort)(void*, PClient))
{
	/*Finding the balance factor*/
	int balance = balance_factor(root);
	if (balance > 1 || balance < -1) 
		return rotation(root, balance, val, sort);
	return root;
}

/*Finding the height of the tree*/
int hight_tree(PNode root) 
{
	if (!root)
		return -1;
	if ((!root->left) && (!root->right))
		return 0;
	return 1 + max_(hight_tree(root->left), hight_tree(root->right));
}

int max_(int a, int b)
{
	return a > b ? a : b;
}

/*Finding the balance factor*/
int balance_factor(PNode root) 
{
	if (!root)
		return 0;
	return hight_tree(root->left) - hight_tree(root->right);
}

/*Left Rotate*/
PNode left_rotate(PNode Father) 
{
	if (!Father)
		return NULL;
	Node* movingAxis = Father->right;
	Node* Adoption = movingAxis->left;
	// Perform rotation
	movingAxis->left = Father;
	Father->father = movingAxis;
	Father->right = Adoption;
	if (Adoption)
		Adoption->father = Father;
	movingAxis->father = NULL;
	// Return new root
	return movingAxis;
}

/*Right Rotate*/
PNode right_rotate(PNode Father) 
{
	if (!Father)
		return NULL;
	PNode movingAxis = Father->left;
	PNode Adoption = movingAxis->right;
	// Perform rotation
	movingAxis->right = Father;
	Father->father = movingAxis;
	Father->left = Adoption;
	if (Adoption)
		Adoption->father = Father;
	movingAxis->father = NULL;
	// Return new root
	return movingAxis;
}

/*Rotation to receive an AVL tree*/
PNode rotation(PNode root, int balance, void* val, int (*sort)(void*, PClient)) 
{
	if (!root)
		return NULL;
	int isValBigger;	
	if (balance > 1) 
	{
		/*Checking whether the val is greater than the left pointer*/
		isValBigger = sort(val, root->left->client);		
		if (isValBigger < 0)// Left Left Case
			return right_rotate(root);		
		if (isValBigger > 0)// Left Right Case
		{
			root->left = left_rotate(root->left);
			return right_rotate(root);
		}
	}
	else 
	{
		/*Checking whether the val is greater than the right pointer*/
		isValBigger = sort(val, root->right->client);
		if (isValBigger > 0)// Right Right Case
			return left_rotate(root);
		// Right Left Case
		if (isValBigger < 0)
		{
			root->right = right_rotate(root->right);
			return left_rotate(root);
		}
	}
	return root;
}

PNode finding_a_replacement_cell(PNode node, void* val, int Enum) 
{
	if (!node)
		return NULL;
	if (node->nextLike)
		return finding_and_applying_a_similar_cell(node);
	return finding_and_applying_a_subsequent_cell(node, val, Enum);
}

void cell_update_in_trees(PClient* newCell, PClient* currCell) 
{
	//***    Cell update   **********
	float prevDebt = (*currCell)->debt;
	(*currCell)->debt += (*newCell)->debt;
	taking_out_cell_and_insert_to_tree(*currCell, EnDebt, &prevDebt, &((*newCell)->debt));
	if (comparing_dates((*newCell)->date, (*currCell)->date) > 0)
	{
		Date prevDate = {0};
		prevDate.day = (*currCell)->date.day;
		prevDate.month = (*currCell)->date.month;
		prevDate.year = (*currCell)->date.year;
		(*currCell)->date = (*newCell)->date;
		taking_out_cell_and_insert_to_tree(*currCell, EnDate, &prevDate, &((*newCell)->date));		
		if (strcmp((*currCell)->phone, (*newCell)->phone))//Update the phone in the current cell
		{
			char prevPhone[11];
			strcpy(prevPhone, (*currCell)->phone);
			free((*currCell)->phone);
			/*Getting a new string for the phone*/
			(*currCell)->phone = creating_a_dynamic_char_with_content((*newCell)->phone);
			taking_out_cell_and_insert_to_tree(*currCell, EnPhone, prevPhone, (*currCell)->phone);
		}
	}
}

void taking_out_cell_and_insert_to_tree(PClient client, int Enum, void* prevVal, void* currVal) 
{
	PNode nodeCurr, temp;
	nodeCurr = finding_a_client_by_parameter(arrayTree[Enum]->root, prevVal, arrSortfunc[Enum]);
	if (!nodeCurr)
		return;
	temp = nodeCurr;
	while (arrSortfunc[EnID](temp->client->id, client)) 
		temp = temp->nextLike;

	// Inspectionand repair of AVL tree.
	while (temp) 
	{
		temp = inspection_and_repair_of_AVL_tree(temp, currVal, arrSortfunc[Enum]);
		temp = temp->father;
	}
	if (nodeCurr->father->left == nodeCurr)
		nodeCurr->father->left = NULL;
	else if (nodeCurr->father->right == nodeCurr)
		nodeCurr->father->right = NULL;
	free(nodeCurr);
	nodeCurr = NULL;
	arrayTree[Enum]->root = income_for_the_tree(arrayTree[Enum]->root, client, currVal, arrSortfunc[Enum]);

}

PNode finding_a_client_by_parameter(PNode root, void* value, int (*sort)(void*, PClient)) 
{
	if (!root)
		return NULL;
	int test = sort(value, root->client);//getting the test value
	if (test < 0)
		return finding_a_client_by_parameter(root->left, value, sort);
	else if (test > 0)
		return finding_a_client_by_parameter(root->right, value, sort);
	else
		return root;
}