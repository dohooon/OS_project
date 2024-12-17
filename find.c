#include "find.h"

void find_name(TreeNode* node, char* path, char* fname) {
    if (strcmp(node->name, fname) == 0) printf("%s/%s\n", path, fname);

    if (node->child != NULL || node->sibling != NULL) {
        char newPath[50];
        strncpy(newPath, path, 50);

        if (node->child != NULL) {
            strcat(newPath, "/");
            strcat(newPath, node->name);
            find_name(node->child, newPath, fname);
        }
        if (node->sibling != NULL) find_name(node->sibling, path, fname);
    }
}

void find_type(TreeNode* node, char* path, char type) {
    if (node->type == type) printf("%s/%s\n", path, node->name);

    if (node->child != NULL || node->sibling != NULL) {
        char newPath[50];
        strncpy(newPath, path, 50);

        if (node->child != NULL) {
            strcat(newPath, "/");
            strcat(newPath, node->name);
            find_type(node->child, newPath, type);
        }
        if (node->sibling != NULL) find_type(node->sibling, path, type);
    }
}

void find(DirTree* dirtree, Users* users, char* cmd) {
    if (cmd == NULL) {
        TreeNode* tmp = dirtree->current;
        if (tmp->child == NULL) return;
        tmp = tmp->child;
        while (tmp != NULL) {
            printf("./%s\n", tmp->name);
            tmp = tmp->sibling;
        }
        return;
    }
    else {
        char* path = strtok(cmd, " ");
        char* opt = strtok(NULL, " ");
        char* fname = strtok(NULL, "");
        char start[50] = "";
        if (path[0] == '.') {
            if (strcmp(opt, "-name") == 0) {
                strncpy(start, "/", 50);
                strcat(start, dirtree->current->name);
                find_name(dirtree->current->child, start, fname);
                return;
            }
            else if (strcmp(opt, "-type") == 0) {
                strncpy(start, "/", 50);
                strcat(start, dirtree->current->name);
                find_type(dirtree->current->child, start, fname[0]);
                return;
            }
            else {
                printf("wrong command\n");
                return;
            }
        }
        else if (path[0] == '/' && strlen(path) == 1) {
            if (strcmp(opt, "-name") == 0) {
                find_name(dirtree->root, start, fname);
                return;
            }
            else if (strcmp(opt, "-type") == 0) {
                find_type(dirtree->root, start, fname[0]);
                return;
            }
            else {
                printf("wrong command\n");
                return;
            }
        }
        else {
            char path[50];
            strncpy(path, cmd, 50);
            TreeNode* tmp = IsDir(dirtree, cmd);
            if (tmp == NULL) {
                printf("wrong directory\n");
                return;
            }
            if (tmp->child == NULL) return;
            tmp = tmp->child;
            while (tmp != NULL) {
                printf("%s/%s\n", path, tmp->name);
                tmp = tmp->sibling;
            }
            return;
        }
    }
}
