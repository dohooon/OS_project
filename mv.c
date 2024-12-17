#include "mv.h"

void mv(DirTree* dirtree, Users* users, char* cmd) {
    char* path1 = strtok(cmd, " "); // from
    char* path2 = strtok(NULL, ""); // to
    TreeNode* tmp1 = IsDir(dirtree, path1);
    TreeNode* tmp2 = IsDir(dirtree, path2);
    if (tmp1 == NULL) {
        printf("wrong directory\n");
        return;
    }
    TreeNode* parent = tmp1->parent;
    if (tmp2 != NULL) {
        if (IsPermission(tmp2, users, 'w') != 0) {
            printf("permission denied\n");
            return;
        }
    }
    if (tmp1 != NULL) {
        if (IsPermission(tmp1, users, 'r') != 0) {
            printf("permission denied\n");
            return;
        }
    }
    if (tmp1->type == 'd') {
        if (tmp2 == NULL) {
            char* tmp = strtok(path2, "/");
            char* filename = tmp;
            while (tmp != NULL) {
                filename = tmp;
                printf("%s\n", filename);
                tmp = strtok(NULL, "/");
            }
            strncpy(tmp1->name, filename, NAME_LEN);
            return;
        }
        else if (tmp2->type != 'd') {
            printf("wrong command\n");
            return;
        }

        if (parent->child == tmp1) {
            parent->child = tmp1->sibling;
            tmp1->sibling = NULL;
            tmp1->parent = NULL;
        }
        else {
            parent = parent->child;
            while (parent->sibling != tmp1) parent = parent->sibling;
            parent->sibling = tmp1->sibling;
            tmp1->sibling = NULL;
            tmp1->parent = NULL;
        }
        if (tmp2->child == NULL) {
            tmp2->child = tmp1;
            tmp1->parent = tmp2;
            return;
        }
        else {
            tmp1->parent = tmp2;
            tmp2 = tmp2->child;
            while (tmp2->sibling != NULL) tmp2 = tmp2->sibling;
            tmp2->sibling = tmp1;
            return;
        }
    }
    else if (tmp1->type == 'f') {
        if (tmp2 == NULL) {
            char* tmp = strtok(path2, "/");
            char* filename = tmp;
            while (tmp != NULL) {
                filename = tmp;

                tmp = strtok(NULL, "/");
            }
            printf("%s, %s\n", tmp1->name, filename);
            if (rename(tmp1->name, filename) == 0) {
                printf("success\n");
            }
            strncpy(tmp1->name, filename, NAME_LEN);
            return;
        }
        if (tmp2->type == 'd') {
            if (parent->child == tmp1) {
                parent->child = tmp1->sibling;
                tmp1->sibling = NULL;
                tmp1->parent = NULL;
            }
            else {
                parent = parent->child;
                while (parent->sibling != tmp1) parent = parent->sibling;
                parent->sibling = tmp1->sibling;
                tmp1->sibling = NULL;
                tmp1->parent = NULL;
            }
            if (tmp2->child == NULL) {
                tmp2->child = tmp1;
                tmp1->parent = tmp2;
                return;
            }
            else {
                tmp1->parent = tmp2;
                tmp2 = tmp2->child;
                while (tmp2->sibling != NULL) tmp2 = tmp2->sibling;
                tmp2->sibling = tmp1;
                return;
            }
        }
        else if (tmp2->type == 'f') {  //µ¤¾î ¾²±â
            strncpy(tmp2->name, tmp1->name, NAME_LEN);
            tmp2->type = tmp1->type;
            tmp2->User = tmp1->User;
            tmp2->Group = tmp1->Group;
	    strcpy(tmp2->contents, tmp1->contents);
            memcpy(tmp2->permission, tmp1->permission, sizeof(tmp1->permission));
            tmp2->size = tmp1->size;
            tmp2->Year = tmp1->Year;
            tmp2->Month = tmp1->Month;
            tmp2->Day = tmp1->Day;
            tmp2->Hour = tmp1->Hour;
            tmp2->Minute = tmp1->Minute;
            TreeNode* parent = tmp1->parent;
            if (parent->child == tmp1) parent->child = tmp1->sibling;
            else {
                parent = parent->child;
                while (parent->sibling != tmp1) parent = parent->sibling;
                parent->sibling = tmp1->sibling;
            }
            free(tmp1);
        }
    }
}
