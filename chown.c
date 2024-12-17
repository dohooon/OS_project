#include "chown.h"

void chown(DirTree* dirtree, char* cmd) {
    char* option = strtok(cmd, " ");
    char* path = strtok(NULL, "");
    if (path == NULL){
	printf("wrong directory\n");
	return;
    }
    TreeNode* tmp = IsDir(dirtree, path);
    if (tmp == NULL) {
        printf("wrong directory\n");
        return;
    }
    char* User = strtok(option, ":");
    char* Group = strtok(NULL, "");
    tmp->User = atoi(User);
    tmp->Group = atoi(Group);
    return;
}
