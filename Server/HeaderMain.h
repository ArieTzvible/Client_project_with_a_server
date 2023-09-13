
#pragma once

#ifndef HeaderMain
#define HeaderMain

#include "HeaderUtilities.h"
#include "PrintingManager.h"
#include "CreatingManager.h"
#include "HeaderTest.h"
#include "HeaderRequests.h"
#include "Globals.h"
#include "server_manager.h"

int testing_first_name(void* value, PClient client);//First name check (specific)
int testing_last_name(void* value, PClient client);//Last name check (specific)
int testing_ID(void* value, PClient client);//ID check (specific)
int testing_phone(void* value, PClient client);//Phone check (specific)
int testing_debt(void* value, PClient client);//Debt check (specific)
int testing_date(void* value, PClient client);//Date check (specific)

#endif