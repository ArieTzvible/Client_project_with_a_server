
#pragma once

#ifndef HeaderRequests
#define HeaderRequests

#include "HeaderMain.h"
#include "HeaderTree.h"
#include "Globals.h"
#include "server_manager.h"
#include "CreatingManager.h"

/*Creating a new client from the user*/
PClient create_a_new_cell_from_the_user(char* buffer, char** send_buffer);
/*Sort by request from the user*/
void sorting_by_request(char* received_buffer);
/*Sorting and printing function according to the request*/
int test_function(PNode root, void* value, char opr, int (*testing)(void*, PClient), char** buffer);
/*Print a new line from the user to the file*/
void adding_client_from_user(ListManager* list, char* received_buffer);

#endif