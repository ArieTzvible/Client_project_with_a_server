
#pragma once

#ifndef CreatingManager
#define CreatingManager

#include "HeaderTest.h"
#include "HeaderMain.h"
#include "HeaderTree.h"
#include "Globals.h"

PTree init_root();//Root initialization
PClient init_errors_in_a_new_cell();//Creating a structure of a new client
void create_string(char* buffer, const char* format, ...);
void add_to_head_the_list(PClient* head, PClient newCell);//add to the top of the list
void adding_a_sorted_customer_to_the_list(PClient* head, PClient newCell);//Sorting and adding to the list
void crate_array_tree_and_array_func_sort();

/*Creating a trees*/
void creating_trees_from_linked_list(ListManager manager);
PNode finding_and_applying_a_similar_cell(PNode node);
PNode finding_and_applying_a_subsequent_cell(PNode node, void* val, int Enum);
PNode create_node_tree(PClient client);
PNode income_for_the_tree(PNode root, PClient client, void* value, int (*sort)(void*, PClient));
void nserting_a_client_into_all_sorting_trees(PClient client);

/*Creating a client*/
void filling_in_a_first_name(PClient curr, char* string);
void filling_in_a_last_name(PClient curr, char* string);
void fillin_in_a_ID(PClient curr, char* string);
void filling_in_a_phone(PClient curr, char* string);
void filling_in_a_debt(PClient curr, char* string);
void filling_in_a_date(PClient curr, char* string);
PClient creating_a_deep_copy_of_a_client(PClient curr);
PClient create_new_client_from_file(char* line);//Create a new cell from the file
Date creating_a_new_date_structure(char* date);//Create a new date
ListManager init_a_new_list_manager();//Creating a new manager structure
void create_list_of_customers_from_a_client(ListManager manager);//creating a list from the file

#endif