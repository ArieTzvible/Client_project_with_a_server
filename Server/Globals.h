
#pragma once

#ifndef Globals
#define Globals

#include "Header.h"

extern int (*arrSortfunc[SIZE_ARRAY])(void* value, PClient client);
extern PTree arrayTree[SIZE_ARRAY];

/*Server&Client*/
extern int server_sock;
extern int client_sock;
extern struct sockaddr_in server_addr;
extern struct sockaddr_in client_addr;
extern socklen_t addr_size;

#endif