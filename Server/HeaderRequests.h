
#pragma once

#ifndef HeaderRequests
#define HeaderRequests

#include "HeaderMain.h"
#include "HeaderTree.h"
#include "Globals.h"
#include "server_manager.h"
#include "CreatingManager.h"


// PClient createANewCellFromTheUser(char* line);//Creating a new client from the user
// void sortingByRequest(ListManager list);//Sort by request from the user
// int testFunction(PNode root, void* value, char opr, int (*testing)(void*, PClient));//Sorting and printing function according to the request
// void addingClientFromUser(ListManager* list, FILE* out);//Print a new line from the user to the file

/*Server*/
PClient create_a_new_cell_from_the_user(char** buffer, char** send_buffer);//Creating a new client from the user
void sorting_by_request(char* received_buffer);//Sort by request from the user
int test_function(PNode root, void* value, char opr, int (*testing)(void*, PClient));//Sorting and printing function according to the request
void adding_client_from_user(ListManager* list);//Print a new line from the user to the file

#endif