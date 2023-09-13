
#pragma once

#ifndef HeaderTest
#define HeaderTest

#include "HeaderUtilities.h"
#include "HeaderDelet.h"
#include "CreatingManager.h"

void testing_the_new_cell(ListManager manager, PClient* newCell);// Checking whether the ID already exists
void cell_update_in_litst(PClient* newCell, PClient* temp);//Cell update
int comparison_of_cells(PClient* newCell, PClient* temp);//Cell comparison
int comparing_dates(Date nweCell, Date temp);//Comparing dates
void is_the_data_correct(PClient* client);

#endif