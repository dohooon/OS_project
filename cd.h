#ifndef CD_H
#define CD_H
#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "isdir.h"
#include "ispermission.h"

void cd(DirTree* dirtree, Users* users, char* path);

#endif
