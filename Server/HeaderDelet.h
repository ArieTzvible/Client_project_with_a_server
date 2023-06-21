
#pragma once

#ifndef HeaderDelet
#define HeaderDelet

#include "Header.h"

// void deletingACellFromTheList(PClient* currentCell);//Deleting a cell from the list
// void deletingTheEntireList(ListManager  manager);//Deleting the entire list
// void errorPrintingandDeletingACell(PClient* cell, char* str);//print an error and delete the cell
// void deletingArrayOfTree();
// void deletingTree(PNode* root);
// PNode deletingNodeAndDeletingLikeds(PNode* node);
// PNode deletingNode(PNode* node, void* val, int Enum);

/*Server*/
void deleting_a_cell_from_the_list(PClient* currentCell);//Deleting a cell from the list
void deleting_the_entire_list(ListManager  manager);//Deleting the entire list
void error_printing_and_deleting_a_cell(PClient* cell, char* str);//print an error and delete the cell
void deleting_array_of_tree();
void deleting_tree(PNode* root);
PNode deleting_node_and_deleting_likeds(PNode* node);
PNode deleting_node(PNode* node, void* val, int Enum);

#endif