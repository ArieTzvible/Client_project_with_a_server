
#pragma once

#ifndef PrintingManager
#define PrintingManager

#include "Header.h"
#include "Globals.h"
/*Server*/
#include"server_manager.h"


// int printingSimilarCustomers(PNode node, int flag);
// int printingClientsInDescendingOrder(PNode root, int flag);//Printing clients from sorted tree froms small to large
// int printingClientsInAscendingOrder(PNode root, int flag);//Printing clients from sorted tree from big to small 
// void printInstructions();//Printing instructions for the program.
// void printTableHead(char* print);//Creating a printable table header
// void printCell(PClient cell);//Single client printing
// void printingDebtorsOnly(PClient head);//Printing a list of debts only.
// void printListDebtsFromTheSmallestToTheLargest(PClient head, char* mainTitle);//Printing the list from the smallest debt to the largest
// void printingCellsWithErrors(PClient head);//Client printing with errors
// void printErrors(char* error, int* printsThatWere);//Print the error
// void printASortedCell(PClient previousList, int flag);//Print a sorted cell

/*Server*/
int printing_similar_customers(PNode node, int flag);
int printing_clients_in_descending_order(PNode root, int flag);//Printing clients from sorted tree froms small to large
int printing_clients_in_ascending_order(PNode root, int flag);//Printing clients from sorted tree from big to small 
void print_instructions();//Printing instructions for the program.
void print_table_head(char* print);//Creating a printable table header
void print_cell(PClient cell);//Single client printing
void printing_debtors_only(PClient head);//Printing a list of debts only.
void print_list_debts_from_the_smallest_to_the_largest(PClient head, char* mainTitle);//Printing the list from the smallest debt to the largest
void printing_cells_with_errors(PClient head);//Client printing with errors
void print_errors(char* error, int* printsThatWere);//Print the error
void print_a_sorted_cell(PClient previousList, int flag);//Print a sorted cell

#endif