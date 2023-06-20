
#pragma once

#ifndef HeaderMain
#define HeaderMain

#include "HeaderUtilities.h"
#include "PrintingManager.h"
#include "CreatingManager.h"
#include "HeaderTest.h"
#include "HeaderRequests.h"
#include "Globals.h"


int testingFirstName(void* value, PClient client);//First name check (specific)
int testingLastName(void* value, PClient client);//Last name check (specific)
int testingID(void* value, PClient client);//ID check (specific)
int testingPhone(void* value, PClient client);//Phone check (specific)
int testingDebt(void* value, PClient client);//Debt check (specific)
int testingDate(void* value, PClient client);//Date check (specific)

/*Server&Client*/
void send_and_recv(char* buffer, int size_buffer);
void send_to_server(char* buffer, int size_buffer);
void recv_to_server(char* buffer);
void print_from_server();



#endif