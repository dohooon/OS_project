#include "ls.h"

void printpermission(TreeNode* node) {
    for (int i = 0; i < 9; i += 3) {
        if (node->permission[i] == 1) printf("r");
        else printf("-");
        if (node->permission[i + 1] == 1) printf("w");
        else printf("-");
        if (node->permission[i + 2] == 1) printf("x");
        else printf("-");
    }
}

void ls(DirTree* dirtree, char* op) {
    int cnt = 0;
    TreeNode* tmp = dirtree->current;
    if (op == NULL) {
        if (tmp->child == NULL) {
            printf("current directory is empty\n");
            return;
        }
        else {
            tmp = tmp->child;
            while (tmp->sibling != NULL) {
                printf("%s\t", tmp->name);
                tmp = tmp->sibling;
                cnt++;
                if (cnt >= 5) {
                    printf("\n");
                    cnt = 0;
                }
            }
            printf("%s\n", tmp->name);
            return;
        }
    }
    else if (strcmp(op, "-a") == 0) {
        if (tmp->child == NULL) {
            printf(".\t..\n");
            return;
        }
        else {
            printf(".\t..\t");
            cnt = 2;
            tmp = tmp->child;
            while (tmp->sibling != NULL) {
                printf("%s\t", tmp->name);
                tmp = tmp->sibling;
                cnt++;
                if (cnt >= 5) {
                    printf("\n");
                    cnt = 0;
                }
            }
            printf("%s\n", tmp->name);
            return;
        }
    }
    else if (strcmp(op, "-l") == 0) {
        tmp = tmp->child;
        while (tmp->sibling != NULL) {
            printf("%c", tmp->type);
            printpermission(tmp);
            printf("\t%d", tmp->User);
            printf("\t%d", tmp->Group);
            printf("\t%d", tmp->size);
            printf("\t%d", tmp->Year);
            printf(" %d", tmp->Month);
            printf(" %d", tmp->Day);
            printf(" %d:%d", tmp->Hour, tmp->Minute);
            printf("\t%s\n", tmp->name);
            tmp = tmp->sibling;
        }
        printf("%c", tmp->type);
        printpermission(tmp);
        printf("\t%d", tmp->User);
        printf("\t%d", tmp->Group);
        printf("\t%d", tmp->size);
        printf("\t%d", tmp->Year);
        printf(" %d", tmp->Month);
        printf(" %d", tmp->Day);
        printf(" %d:%d", tmp->Hour, tmp->Minute);
        printf("\t%s\n", tmp->name);
    }
}