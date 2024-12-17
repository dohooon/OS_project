#include "cd.h"

void cd(DirTree* dirtree, Users* users, char* path)
{
    TreeNode* tmp = dirtree->current;
    if (((path == NULL) || (strcmp(path, ".") == 0)) || (strcmp(dirtree->current->name, path) == 0)) {  //현재 디렉토리 호출
        dirtree->current = tmp;
        printf("current directory is %s\n", dirtree->current->name);
    }
    else if (strcmp(path, "..") == 0) {  //상위 디렉토리 호출
        if (strcmp(tmp->name, "root") == 0) {  //루트는 상위디렉토리가 없음
            printf("current directory is %s\n", dirtree->current->name);
            return;
        }
        else if (IsPermission(tmp->parent, users, 'r') == 0) { //상위 디렉토리에 접근 가능한지 확인
            dirtree->current = tmp->parent;
            printf("current directory is %s\n", dirtree->current->name);
            return;
        }
        else printf("can not access\n");
    }
    else {
        tmp = IsDir(dirtree, path); //. ..이 아니라 path로 접근했을 때
        if (tmp == NULL) {
            printf("wrong directory\n");
            return;
        }
        else {
            if (tmp->type != 'd') {
                printf("%s is not a directory.\n", tmp->name); //찾은 파일이 디렉토리인지 확인, 아니면 폴더 변경없이 종료
                return;
            }
            if (IsPermission(tmp, users, 'r') == 0) { //NULL이 반환되지 않았으면 해당 디렉토리에 접근 가능한지 확인
                dirtree->current = tmp;
                printf("current directory is %s\n", dirtree->current->name);
            }
            else printf("access denied.\n");
        }
    }
    return;
}