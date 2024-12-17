#include "mkdir.h"

void make_dir(TreeNode* node, Users* users, char* dir_name, char type) { //������ ������ ����, ���ϸ�, Ÿ���� �޾� �����ϴ� �Լ�
    TreeNode* New = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode* tmp = node;
    if (tmp->type != 'd') {
        printf("%s is not a directory\n", tmp->name);
        return;
    }
    if (IsPermission(tmp, users, 'w') != 0) {
        printf("access denied.\n");
        free(New);
        return;
    }
    if ((dir_name == '.') || (strcmp(dir_name, "..") == 0)) {
        free(New);
        printf("can't use '.' or '..' as directory name.\n");
        return;
    }
    if (tmp->child == NULL) {
        tmp->child = New;
    }
    else {
        tmp = node->child;
        if (strcmp(tmp->name, dir_name) == 0) {
            printf("a file with the same name exists in the directory.\n");
            free(New);
            return;
        }
        while (1) {
            if (tmp->sibling == NULL) break;
            if (strcmp(tmp->sibling, dir_name) == 0) {
                printf("a file with the same name exists in the directory.\n");
                free(New);
                return;
            }
            tmp = tmp->sibling;
        }
        tmp->sibling = New;
    }
    time_t timer = time(NULL);
    struct tm* t = localtime(&timer);
    New->parent = node;
    New->child = NULL;
    New->sibling = NULL;
    strncpy(New->name, dir_name, NAME_LEN);
    if (type == 'd') {  //���丮
        New->type = 'd';
        int per[9] = { 1,1,1,1,0,1,1,0,1 }; //rwxr-xr-x
        memcpy(New->permission, per, sizeof(per));
        New->size = 4096;
    }
    else if (type == 'f') {  //�Ϲ� ����
        New->type = 'f';
        int per[9] = { 1,1,0,1,0,0,1,0,0 }; //rw-r--r--
        memcpy(New->permission, per, sizeof(per));
        New->size = 0;
    }
    New->User = users->current->User;
    New->Group = users->current->Group;
    New->Year = t->tm_year + 1900;
    New->Month = t->tm_mon + 1;
    New->Day = t->tm_mday;
    New->Hour = t->tm_hour;
    New->Minute = t->tm_min;
    strncpy(New->contents, "\n", MAX_LINES * CON_LEN);
    return;
}

void mkdir(DirTree* dirtree, Users* users, char* dir_name) { // makedir �Լ��� �̿��� ��ο� ���� ����
    TreeNode* tmp = NULL;
    TreeNode* parent = NULL;
    char* token;
    if (dir_name == NULL) {
        printf("wrong directory\n");
        return;
    }
    if (dir_name[0] == '-') { //�ɼ� ���� ��
        token = strtok(dir_name, " "); // token = option
        if (strcmp(token, "-p") == 0) {
            char* path = strtok(NULL, " "); // token = path
            if (path[0] == '/') {  //���� ��η� ����
                tmp = dirtree->root;
                parent = dirtree->root;
                token = strtok(path, "/"); // token == root
                if (strcmp(token, "root") != 0) {  //���� ��� ù ��ġ�� root�� �ƴϸ� ���� �޼��� ���
                    printf("wrong directory\n");
                    return;
                }
                token = strtok(NULL, "/");  //  '/'������ ���� �̸��� token�� �����ϸ鼭 ���� Ž��
                while (token != NULL) {
                    tmp = tmp->child;
                    while (tmp != NULL) {
                        if (strcmp(tmp->name, token) == 0 && tmp->type == 'd') {
                            parent = tmp;  // �̸��� ������ ������ ã���� Ż��
                            break;
                        }
                        tmp = tmp->sibling;
                    }
                    if (tmp == NULL) {
                        while (token != NULL) {
                            make_dir(parent, users, token, 'd');
                            parent = parent->child;
                            while (parent->sibling != NULL) parent = parent->sibling;
                            token = strtok(NULL, "/");
                        }
                        return;
                    }
                    token = strtok(NULL, "/");
                }
                printf("directory %s is already exist\n", dir_name);
            }
            else { // ���� ���丮�� ����
                tmp = dirtree->current;
                token = strtok(path, "/");
                while (token != NULL) {
                    make_dir(tmp, users, token, 'd');
                    tmp = tmp->child;
                    while (tmp->sibling != NULL) tmp = tmp->sibling;
                    token = strtok(NULL, "/");
                }
                return;
            }
        }
        else {  //�ٸ� �ɼ��� ������ ���� �޼���
            printf("wrong command\n");
            return;
        }
    }
    else { //�ɼ� ����
        if (dir_name[0] == '/') {  //���� ��η� ����
            tmp = dirtree->root;
            parent = dirtree->root;
            token = strtok(dir_name, "/"); // token == root
            if (strcmp(token, "root") != 0) {  //���� ��� ù ��ġ�� root�� �ƴϸ� ���� �޼��� ���
                printf("wrong directory\n");
                return;
            }
            token = strtok(NULL, "/");  //  '/'������ ���� �̸��� token�� �����ϸ鼭 ���� Ž��
            while (token != NULL) {
                tmp = tmp->child;
                while (tmp != NULL) {
                    if (strcmp(tmp->name, token) == 0 && tmp->type == 'd') {
                        parent = tmp;  // �̸��� ������ ������ ã���� Ż��
                        break;
                    }
                    tmp = tmp->sibling;
                }
                if (tmp == NULL) {
                    if (strtok(NULL, "/") != NULL) {  //�����ϰ��� �ϴ� ���ϸ��� file/file2 ���̸� ���� �޼��� ���
                        printf("wrong directory\n");
                        return;
                    }
                    make_dir(parent, users, token, 'd');
                    return;
                }
                token = strtok(NULL, "/");
            }
            printf("directory %s is already exist\n", dir_name);
        }
        else { // ���� ���丮�� ����
            tmp = dirtree->current;
            token = strtok(dir_name, "/");
            if (token == NULL) {
                printf("wrong directory\n");
                return;
            }
            token = strtok(NULL, "/");
            if (token != NULL) { //�����ϰ��� �ϴ� ���ϸ��� file/file2 ���̸� ���� �޼��� ���
                printf("wrong directory\n");
                return;
            }
            make_dir(tmp, users, dir_name, 'd');
            return;
        }
    }
    return;
}

void* thread_mkdir(void* arg) {
    thread_data* data = (thread_data*)arg;
    mkdir(data->dirtree, data->users, data->dir_name);
    free(arg);
    return NULL;
}

void multithread_mkdir(DirTree* dirtree, Users* users, char* dirs) {
    pthread_t thread_ids[50];
    int i = 0;
    if (dirs[0] == '-') {
        mkdir(dirtree, users, dirs);
        return;
    }
    char* token = strtok(dirs, " ");
    while (token != NULL) {
        thread_data* data = (thread_data*)malloc(sizeof(thread_data));
        data->dirtree = dirtree;
        data->users = users;
        strncpy(data->dir_name, token, 50);
        pthread_create(&thread_ids[i], NULL, thread_mkdir, data);
        i++;
        token = strtok(NULL, " ");
    }

    for (int j = 0; j < i; j++) {
        pthread_join(thread_ids[j], NULL);
    }
}