
#pragma once

#ifndef HeaderUtilities
#define HeaderUtilities
#define CHUNK 10

#include "Header.h"
#include "server_manager.h"

int is_num(char ch);
int is_int(char* num);//Checking the correctness of the int in the string
int is_float(char* num);//Checking the correctness of the float in the string
int is_negative_int(char* num);
int is_negative_float(char* num);
int is_letter(char* ch);
int is_the_string_correct(char* string);//Checking and changing uppercase to lowercase letters
float string_conversion_to_float(char* strFloat);//Convert a string to a valid debt amount
char* getting_line(FILE* file);//getting a complete line from the file
char* creating_a_dynamic_char_with_content(char* string);//Creating a dynamic variable with content
char* get_new_file_name(char* extension);//Requesting another file name

#endif