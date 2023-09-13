
#pragma once

#ifndef HeaderServer
#define HeaderServer

#include "Globals.h"

void init_server();
void my_listen();
char* recv_();
void send_(char* buffer);
void creating_a_string_with_variables(char** buffer, const char* format, ...);
void print_send(char* buffer);
void send_client(char* buffer);
void print_recv();
char* get_recv();

#endif
