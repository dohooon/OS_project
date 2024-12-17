#ifndef RM_H
#define RM_H
#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "mkdir.h"
#include "isdir.h"

void remove_node(TreeNode* node, int o);
void rm(DirTree* dirtree, Users* users, char* cmd);
void* thread_rm(void* arg);
void multithread_rm(DirTree* dirtree, Users* users, char* dirs);

#endif
