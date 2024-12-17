#include "cd.h"

void cd(DirTree* dirtree, Users* users, char* path)
{
    TreeNode* tmp = dirtree->current;
    if (((path == NULL) || (strcmp(path, ".") == 0)) || (strcmp(dirtree->current->name, path) == 0)) {  //���� ���丮 ȣ��
        dirtree->current = tmp;
        printf("current directory is %s\n", dirtree->current->name);
    }
    else if (strcmp(path, "..") == 0) {  //���� ���丮 ȣ��
        if (strcmp(tmp->name, "root") == 0) {  //��Ʈ�� �������丮�� ����
            printf("current directory is %s\n", dirtree->current->name);
            return;
        }
        else if (IsPermission(tmp->parent, users, 'r') == 0) { //���� ���丮�� ���� �������� Ȯ��
            dirtree->current = tmp->parent;
            printf("current directory is %s\n", dirtree->current->name);
            return;
        }
        else printf("can not access\n");
    }
    else {
        tmp = IsDir(dirtree, path); //. ..�� �ƴ϶� path�� �������� ��
        if (tmp == NULL) {
            printf("wrong directory\n");
            return;
        }
        else {
            if (tmp->type != 'd') {
                printf("%s is not a directory.\n", tmp->name); //ã�� ������ ���丮���� Ȯ��, �ƴϸ� ���� ������� ����
                return;
            }
            if (IsPermission(tmp, users, 'r') == 0) { //NULL�� ��ȯ���� �ʾ����� �ش� ���丮�� ���� �������� Ȯ��
                dirtree->current = tmp;
                printf("current directory is %s\n", dirtree->current->name);
            }
            else printf("access denied.\n");
        }
    }
    return;
}