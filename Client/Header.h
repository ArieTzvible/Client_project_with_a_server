
#pragma once

#ifndef Header
#define Header

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define BUFFER_SIZE 1024
#define IP "127.0.0.1"
#define PORT 5566

#define FILE_NAME "f.csv"
#define FILE_NAME_EXTENSION ".csv"// ending

extern int sock;

#endif