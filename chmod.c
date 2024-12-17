#include "chmod.h"

int* str2int(char mode) {
    if (mode == '7') {
        static int result[3] = { 1,1,1 };
        return result;
    }
    else if (mode == '6') {
        static int result[3] = { 1,1,0 };
        return result;
    }
    else if (mode == '5') {
        static int result[3] = { 1,0,1 };
        return result;
    }
    else if (mode == '4') {
        static int result[3] = { 1,0,0 };
        return result;
    }
    else if (mode == '3') {
        static int result[3] = { 0,1,1 };
        return result;
    }
    else if (mode == '2') {
        static int result[3] = { 0,1,0 };
        return result;
    }
    else if (mode == '1') {
        static int result[3] = { 0,0,1 };
        return result;
    }
    else if (mode == '0') {
        static int result[3] = { 0,0,0 };
        return result;
    }
    else {
        return NULL;
    }
}

void chmod(DirTree* dirtree, char* cmd) {
    TreeNode* tmp = NULL;
    char* option;
    char* path;

    if ('0' <= cmd[0] && cmd[0] <= '7') {
        option = strtok(cmd, " "); // option
        path = strtok(NULL, " ");
	if (path == NULL){
	    printf("wrong directory\n");
	    return;
	}
        if (strlen(option) != 3) {
            printf("wrong command\n");
            return;
        }
        tmp = IsDir(dirtree, path);
        if (tmp == NULL) {
            printf("wrong directory\n");
            return;
        }
        for (int i = 0; i < 3; i++) {
            int* per = str2int(option[i]);
            for (int j = 0; j < 3; j++) tmp->permission[3 * i + j] = per[j];
        }
        return;
    }
    else {
        printf("wrong command\n");
        return;
    }
    return;
}
