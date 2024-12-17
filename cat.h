#ifndef CAT_H
#define CAT_H
#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "isdir.h"
#include "mkdir.h"
#include "ispermission.h"

void concatenate(DirTree* dirTree, Users* users, char* filename, int mode);
void cat(DirTree* dirtree, Users* users, char* cmd);
void* thread_cat(void* arg);
void multithread_cat(DirTree* dirtree, Users* users, char* dirs);

#endif
