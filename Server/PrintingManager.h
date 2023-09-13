
#pragma once

#ifndef PrintingManager
#define PrintingManager

#include "Header.h"
#include "Globals.h"
#include"server_manager.h"
void print_instructions();//Printing instructions for the program.
void print_table_head(char** buffer, char* print);//Creating a printable table header
void print_cell(PClient cell, char** buffer);//Single client printing
void printing_debtors_only(PClient head);//Printing a list of debts only.
void printing_cells_with_errors(PClient head);//Client printing with errors
void print_errors(char** buffer, char* error);//Print the error
void print_a_sorted_cell(PClient previousList, int flag, char** buffer);//Print a sorted cell
int printing_similar_customers(PNode node, int flag, char** buffer);

int printing_clients_in_descending_order(PNode root, int flag, char** buffer);//Printing clients from sorted tree froms small to large
int printing_clients_in_ascending_order(PNode root, int flag, char** buffer);//Printing clients from sorted tree from big to small 
void print_list_debts_from_the_smallest_to_the_largest(PClient head, char* mainTitle);//Printing the list from the smallest debt to the largest
char* create_string_by_ch(int size, char ch);

#endif