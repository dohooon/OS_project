#include "isdir.h"

TreeNode* IsDir(DirTree* dirtree, char* path) {
    TreeNode* tmp = NULL;
    if (path[0] == '/') {  //������
        tmp = dirtree->root;  //��Ʈ ������ �̵�
        char* token = strtok(path, "/"); //ù��° ��ΰ� root���� Ȯ��
        if (strcmp(token, "root") != 0) {
            return NULL;
        }
        token = strtok(NULL, "/"); //�ι�° ��κ��� Ž�� child->(sibling->.....->sibling)->child->(sibling->...->sibling)->child ������ Ž���ϸ鼭 ��ο� �������� ��ġ�ϴ��� Ȯ��
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
            return NULL;  //��ġ�ϴ� ���丮�� ������ NULL ��ȯ
        }
    }
    else { //��� ���
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