#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "struct.h"
#include "init_struct.h"
#include "ispermission.h"
#include "isdir.h"
#include "cd.h"
#include "mkdir.h"
#include "ls.h"
#include "chmod.h"
#include "chown.h"
#include "mv.h"
#include "find.h"
#include "cat.h"
#include "grep.h"
#include "save_load.h"
#include "rm.h"

void main()
{
    char cmd[50];
    Users* users = init_user();
    DirTree* dirtree = loadTree("TreeFile.txt", "DataFile.txt");
    if (dirtree == NULL) {
        dirtree = init_Dir(users);
    }
    dirtree->current = dirtree->root;
    dirtree->current = dirtree->current->child;
    while(1){
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strlen(cmd)-1] = '\0';
        char* opt = strtok(cmd, " ");
        char* path = strtok(NULL, "");
        if (strcmp(opt,"cd") == 0){
            cd(dirtree, users, path);
            printf("\n");
        }
        else if(strcmp(opt,"mkdir") == 0){
            multithread_mkdir(dirtree, users, path);
            printf("\n");
        }
        else if(strcmp(opt,"ls") == 0){
            ls(dirtree, path);
            printf("\n");
        }
        else if(strcmp(opt,"chmod") == 0){
            chmod(dirtree, path);
            printf("\n");
        }
        else if(strcmp(opt,"chown") == 0){
            chown(dirtree, path);
            printf("\n");
        }
        else if(strcmp(opt,"mv")==0){
            mv(dirtree, users, path);
            printf("\n");
        }
        else if(strcmp(opt,"cat")==0){
            multithread_cat(dirtree, users, path);
            printf("\n");
        }
        else if(strcmp(opt,"grep")==0){
            grep(dirtree, users, path);
            printf("\n");
        }
        else if(strcmp(opt,"find")==0){
            find(dirtree, users, path);
            printf("\n");
        }
        else if (strcmp(opt, "rm") == 0) {
            multithread_rm(dirtree, users, path);
            printf("\n");
        }
        else if(strcmp(opt,"exit")==0){
            saveTree(dirtree, "TreeFile.txt", "DataFile.txt");
            break;
        }
        else if (cmd == NULL) {
            printf("\n ");
        }
    }
    free(dirtree);
    free(users);
}
//---------------------------------
