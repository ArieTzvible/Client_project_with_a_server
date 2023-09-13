#pragma once

#ifndef HeaderUtilities
#define HeaderUtilities

#include "ClientManager.h"

char* getting_line(FILE* file);//getting a complete line from the file
char* get_new_file_name(char* extension);//Requesting another file name
void sending_line_to_a_server(FILE* file);

#endif
