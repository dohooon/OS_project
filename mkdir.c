#include "mkdir.h"

void make_dir(TreeNode* node, Users* users, char* dir_name, char type) { //파일을 생성할 노드와, 파일명, 타입을 받아 생성하는 함수
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
    if (type == 'd') {  //디렉토리
        New->type = 'd';
        int per[9] = { 1,1,1,1,0,1,1,0,1 }; //rwxr-xr-x
        memcpy(New->permission, per, sizeof(per));
        New->size = 4096;
    }
    else if (type == 'f') {  //일반 파일
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

void mkdir(DirTree* dirtree, Users* users, char* dir_name) { // makedir 함수를 이용해 경로에 파일 생성
    TreeNode* tmp = NULL;
    TreeNode* parent = NULL;
    char* token;
    if (dir_name == NULL) {
        printf("wrong directory\n");
        return;
    }
    if (dir_name[0] == '-') { //옵션 있을 때
        token = strtok(dir_name, " "); // token = option
        if (strcmp(token, "-p") == 0) {
            char* path = strtok(NULL, " "); // token = path
            if (path[0] == '/') {  //절대 경로로 생성
                tmp = dirtree->root;
                parent = dirtree->root;
                token = strtok(path, "/"); // token == root
                if (strcmp(token, "root") != 0) {  //절대 경로 첫 위치가 root가 아니면 오류 메세지 출력
                    printf("wrong directory\n");
                    return;
                }
                token = strtok(NULL, "/");  //  '/'단위로 폴더 이름을 token에 저장하면서 파일 탐색
                while (token != NULL) {
                    tmp = tmp->child;
                    while (tmp != NULL) {
                        if (strcmp(tmp->name, token) == 0 && tmp->type == 'd') {
                            parent = tmp;  // 이름이 동일한 폴더를 찾으면 탈출
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
            else { // 현재 디렉토리에 생성
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
        else {  //다른 옵션이 들어오면 오류 메세지
            printf("wrong command\n");
            return;
        }
    }
    else { //옵션 없이
        if (dir_name[0] == '/') {  //절대 경로로 생성
            tmp = dirtree->root;
            parent = dirtree->root;
            token = strtok(dir_name, "/"); // token == root
            if (strcmp(token, "root") != 0) {  //절대 경로 첫 위치가 root가 아니면 오류 메세지 출력
                printf("wrong directory\n");
                return;
            }
            token = strtok(NULL, "/");  //  '/'단위로 폴더 이름을 token에 저장하면서 파일 탐색
            while (token != NULL) {
                tmp = tmp->child;
                while (tmp != NULL) {
                    if (strcmp(tmp->name, token) == 0 && tmp->type == 'd') {
                        parent = tmp;  // 이름이 동일한 폴더를 찾으면 탈출
                        break;
                    }
                    tmp = tmp->sibling;
                }
                if (tmp == NULL) {
                    if (strtok(NULL, "/") != NULL) {  //생성하고자 하는 파일명이 file/file2 꼴이면 오류 메세지 출력
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
        else { // 현재 디렉토리에 생성
            tmp = dirtree->current;
            token = strtok(dir_name, "/");
            if (token == NULL) {
                printf("wrong directory\n");
                return;
            }
            token = strtok(NULL, "/");
            if (token != NULL) { //생성하고자 하는 파일명이 file/file2 꼴이면 오류 메세지 출력
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