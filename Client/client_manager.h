
#pragma once

#ifndef HeaderClient
#define HeaderClient

#include "Header.h"
#include "Globals.h"

/*Booting and connecting the client to the server*/
void init_client();

/*Receiving a string of unknown size*/
char* recv_();

void send_(char* buffer);

void print_from_recv();

//todo *****************************
void print_send(char* buffer);
void send_server(char* buffer);
void print_recv();
char* get_recv();

#endif
