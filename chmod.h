#ifndef CHMOD_H
#define CHMOD_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "struct.h"
#include "isdir.h"

int* str2int(char mode);
void chmod(DirTree* dirtree, char* cmd);

#endif