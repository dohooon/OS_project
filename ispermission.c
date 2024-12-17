#include "ispermission.h"

int IsPermission(TreeNode* node, Users* users, char rwx) {
    if (users->current->User == node->User) {
        if (rwx == 'r') {
            if (node->permission[0] == 0) return -1;
            else return 0;
        }
        else if (rwx == 'w') {
            if (node->permission[1] == 0) return -1;
            else return 0;
        }
        else {
            if (node->permission[2] == 0) return -1;
            else return 0;
        }
    }
    else if (users->current->Group == node->Group) {
        if (rwx == 'r') {
            if (node->permission[3] == 0) return -1;
            else return 0;
        }
        else if (rwx == 'w') {
            if (node->permission[4] == 0) return -1;
            else return 0;
        }
        else {
            if (node->permission[5] == 0) return -1;
            else return 0;
        }
    }
    else {
        if (rwx == 'r') {
            if (node->permission[6] == 0) return -1;
            else return 0;
        }
        else if (rwx == 'w') {
            if (node->permission[7] == 0) return -1;
            else return 0;
        }
        else {
            if (node->permission[8] == 0) return -1;
            else return 0;
        }
    }
    return 1;
}