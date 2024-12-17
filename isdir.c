#include "isdir.h"

TreeNode* IsDir(DirTree* dirtree, char* path) {
    TreeNode* tmp = NULL;
    if (path[0] == '/') {  //절대경로
        tmp = dirtree->root;  //루트 폴더로 이동
        char* token = strtok(path, "/"); //첫번째 경로가 root인지 확인
        if (strcmp(token, "root") != 0) {
            return NULL;
        }
        token = strtok(NULL, "/"); //두번째 경로부터 탐색 child->(sibling->.....->sibling)->child->(sibling->...->sibling)->child 순으로 탐색하면서 경로와 폴더명이 일치하는지 확인
        while (token != NULL) {
            tmp = tmp->child;
            while (tmp != NULL) {
                if (strcmp(tmp->name, token) == 0) break;
                tmp = tmp->sibling;
            }
            if (tmp == NULL) break;
            token = strtok(NULL, "/");
        }
        if (tmp == NULL) {
            return NULL;  //일치하는 디렉토리가 없으면 NULL 반환
        }
    }
    else { //상대 경로
        tmp = dirtree->current->child;
        while (tmp != NULL) {
            if (strcmp(tmp->name, path) == 0) break;
            tmp = tmp->sibling;
        }
        if (tmp == NULL) {
            return NULL;
        }
    }
    return tmp;
}