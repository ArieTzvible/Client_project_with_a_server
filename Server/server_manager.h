
#pragma once

#ifndef HeaderServer
#define HeaderServer

#include "Globals.h"

void init_server();

void my_listen();

char* recv_();

void send_(char* buffer);

void send_format(const char* format, ...);

// void print_from_recv();


#endif
