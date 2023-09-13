#pragma once

#ifndef HeaderTree
#define HeaderTree
#include "HeaderMain.h"

//*** A V L *******
PNode inspection_and_repair_of_AVL_tree(PNode root, void* val, int (*sort)(void*, PClient));
/*Finding the height of the tree*/
int hight_tree(PNode root);
/*Finding the balance factor*/
int balance_factor(PNode root);
/*Rotation to receive an AVL tree*/
PNode rotation(PNode root, int balance, void* val, int (*sort)(void*, PClient));
PNode left_rotate(PNode father);
PNode right_rotate(PNode father);

PNode finding_a_replacement_cell(PNode node, void* val, int Enum);
PNode finding_a_client_by_parameter(PNode root, void* value, int (*sort)(void*, PClient));
void taking_out_cell_and_insert_to_tree(PClient client, int Enum, void* prevVal, void* currVal);
void cell_update_in_trees(PClient* newCell, PClient* curr);
int max_(int a, int b);

#endif