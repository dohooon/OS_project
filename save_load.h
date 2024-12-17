#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"

void setParentPointers(TreeNode* node, TreeNode* parent);
void writeTreeToFile(TreeNode* node, FILE* file, FILE* Data);
TreeNode* readTreeFromFile(FILE* file, FILE* Data);
void saveTree(DirTree* dirtree, char* filename, char* dataname);
DirTree* loadTree(char* filename, char* dataname);

#endif
