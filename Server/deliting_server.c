
#include "HeaderDelet.h"
#include "HeaderTree.h"
#include "Globals.h"

void deleting_a_cell_from_the_list(PClient* currentCell) {//deleting a cell from the list
	if (*currentCell) {
		if ((*currentCell)->firstName)
			free((*currentCell)->firstName);//Releasing a first name string
		if ((*currentCell)->lastName)
			free((*currentCell)->lastName);//Releasing last name string
		if ((*currentCell)->id)
			free((*currentCell)->id);//Releasing an ID string
		if ((*currentCell)->phone)
			free((*currentCell)->phone);//Releasing a phone string
		free(*currentCell);//release current cell
		*currentCell = NULL;
	}
}

void deleting_the_entire_list(ListManager manager) {//deleting the whole list
	while (manager->head) {//Checking the list is not empty
		PClient temp = manager->head;
		manager->head = manager->head->next;//Move the pointer to the next cell
		deleting_a_cell_from_the_list(&temp);//cell release
	}
	while (manager->headError) {//Checking the list is not empty
		PClient temp = manager->headError;
		manager->headError = manager->headError->next;//Move the pointer to the next cell
		deleting_a_cell_from_the_list(&temp);//cell release
	}
	free(manager);//Releasing the manager structure
}

void error_printing_and_deleting_a_cell(PClient* cell, char* str, char** buffer) {//printing an error and deleting a cell
	printf("%s", str);//printing an error
	creating_a_string_with_variables(buffer, str);
	deleting_a_cell_from_the_list(cell);//deleting a cell
}

void deleting_array_of_tree() {
	for (int i = 0; i < SIZE_ARRAY; i++) {
		deleting_tree(&(arrayTree[i]->root));
		free(arrayTree[i]);
		arrayTree[i] = NULL;
	}
}

void deleting_tree(PNode* root) {
	/*Check if the node is empty*/
	if (!(*root))
		return;

	/*Deleting the left tree*/
	if ((*root)->left)
		deleting_tree(&((*root)->left));

	/*Deleting the right tree*/
	if ((*root)->right)
		deleting_tree(&((*root)->right));

	if (!deleting_node_and_deleting_likeds(root))
		return;
}

PNode deleting_node_and_deleting_likeds(PNode* node) {
	/*Declaring the pointer variable Node*/
	PNode like = *node, temp;

	/*Check if the node is empty*/
	while (like) {
		temp = like;
		like = like->nextLike;
		free(temp);
		temp = NULL;
	}

	return NULL;
}

PNode deleting_node(PNode* node, void* val, int Enum) {

	/*Check if the node is empty*/
	if (!(*node))
		return NULL;

	/*Finding a replacement to the node*/
	PNode temp = finding_a_replacement_cell(*node, val, Enum);

	/*Deleting node*/
	free(*node);

	/*Applying the cell to NULL*/
	*node = NULL;

	/*Returning the replacement cell*/
	return temp;
}
