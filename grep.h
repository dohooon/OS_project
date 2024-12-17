#ifndef GREP_H
#define GREP_H
#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "isdir.h"
#include "ispermission.h"

void grep(DirTree* dirtree, Users* users, char* cmd);

#endif