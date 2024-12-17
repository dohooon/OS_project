#include "rm.h"

void remove_node(TreeNode* node, int o) {
    if (o == 0) {
        TreeNode* Parent = node->parent;
        if (Parent->child == node) {
            Parent->child = node->sibling;
            return;
        }
        else {
            TreeNode* Sibling = Parent->child;
            while (Sibling->sibling != node) Sibling = Sibling->sibling;
            Sibling->sibling = node->sibling;
        }
        free(node);
    }
    else {
        while (node->child != NULL) {
            remove_node(node->child, 1);
        }
        TreeNode* Parent = node->parent;
        if (Parent->child == node) {
            Parent->child = node->sibling;
            return;
        }
        else {
            TreeNode* Sibling = Parent->child;
            while (Sibling->sibling != node) Sibling = Sibling->sibling;
            Sibling->sibling = node->sibling;
        }
        free(node);
    }
}

void rm(DirTree* dirtree, Users* users, char* cmd) {
    TreeNode* tmp = NULL;
    if (cmd[0] == '-') {
        char* opt = strtok(cmd, " ");
        char* path = strtok(NULL, "");
        if (strcmp(opt, "-r") == 0) {
            tmp = IsDir(dirtree, path);
            if (tmp == NULL) {
                printf("wrong directory\n");
                return;
            }
            remove_node(tmp, 1);
            return;
        }
        else {
            printf("wrong command\n");
            return;
        }
    }
    else {
        tmp = IsDir(dirtree, cmd);
        if (tmp == NULL) {
            printf("wrong directory\n");
            return;
        }
        if (tmp->child != NULL) {
            printf("This directory is not empty.\n");
            return;
        }
        remove_node(tmp, 0);
    }
}

void* thread_rm(void* arg) {
    thread_data* data = (thread_data*)arg;
    rm(data->dirtree, data->users, data->dir_name);
    free(arg);
    return NULL;
}

void multithread_rm(DirTree* dirtree, Users* users, char* dirs) {
    pthread_t thread_ids[50];
    int i = 0;
    if (dirs[0] == '-') {
        rm(dirtree, users, dirs);
        return;
    }
    char* token = strtok(dirs, " ");
    while (token != NULL) {
        thread_data* data = (thread_data*)malloc(sizeof(thread_data));
        data->dirtree = dirtree;
        data->users = users;
        strncpy(data->dir_name, token, 50);
        pthread_create(&thread_ids[i], NULL, thread_rm, data);
        i++;
        token = strtok(NULL, " ");
    }

    for (int j = 0; j < i; j++) {
        pthread_join(thread_ids[j], NULL);
    }
}