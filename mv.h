#ifndef MN_H
#define MV_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"
#include "ispermission.h"
#include "isdir.h"

void mv(DirTree* dirtree, Users* users, char* cmd);

#endif
