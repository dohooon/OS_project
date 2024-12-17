#ifndef FIND_H
#define FIND_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"
#include "isdir.h"

void find_name(TreeNode* node, char* path, char* fname);
void find_type(TreeNode* node, char* path, char type);
void find(DirTree* dirtree, Users* users, char* cmd);

#endif
