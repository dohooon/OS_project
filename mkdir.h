#ifndef MKDIR_H
#define MKDIR_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"

void make_dir(TreeNode* node, Users* users, char* dir_name, char type);
void mkdir(DirTree* dirtree, Users* users, char* dir_name);
void* thread_mkdir(void* arg);
void multithread_mkdir(DirTree* dirtree, Users* users, char* dirs);

#endif