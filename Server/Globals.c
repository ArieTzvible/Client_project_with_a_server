#include "Globals.h"

int (*arrSortfunc[SIZE_ARRAY])(void* value, PClient client);
PTree arrayTree[SIZE_ARRAY];

int server_sock;
int client_sock;
struct sockaddr_in server_addr;
struct sockaddr_in client_addr;
socklen_t addr_size;