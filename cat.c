#include "cat.h"

void concatenate(DirTree* dirTree, Users* users, char* filename, int mode)
{
    TreeNode* tmpNode = NULL;

    if (mode != 0) {
        tmpNode = IsDir(dirTree, filename);
        if (tmpNode == NULL) {
            printf("wrong directory\n");
            return;
        }
        if (tmpNode->type != 'f') {
            printf("%s is not a file\n", tmpNode->name);
            return;
        }
        if (tmpNode == NULL) {
            printf("wrong directory\n");
            return;
        }
        if (mode == 1) {
            printf("%s\n", tmpNode->contents);
        }
        else {
            int line_count = 1;
            char* tmp = malloc(sizeof(char) * (MAX_LINES * CON_LEN + 1));
            strncpy(tmp, tmpNode->contents, MAX_LINES * CON_LEN);
            char* line = strtok(tmp, "\n");
            while (line != NULL) {
                printf("%d: %s\n", line_count, line);
                line_count++;
                line = strtok(NULL, "\n");
            }
            free(tmp);
        }
        return;
    }
    else
    {
        char line[CON_LEN];
        char contents[MAX_LINES * CON_LEN] = "";

        for (int i = 0; i < MAX_LINES; i++) {
            fgets(line, sizeof(line), stdin);
            if (strncmp(line, ":wq", 3) == 0) break;
            strncat(contents, line, CON_LEN);
        }

        tmpNode = IsDir(dirTree, filename);

        if (tmpNode != NULL) {
            time_t timer = time(NULL);
            struct tm* t = localtime(&timer);

            tmpNode->Month = t->tm_mon + 1;
            tmpNode->Day = t->tm_mday;
            tmpNode->Hour = t->tm_hour;
            tmpNode->Minute = t->tm_min;
            strncpy(tmpNode->contents, contents, MAX_LINES * CON_LEN);
        }
        //파일이 없을 시
        else {
            make_dir(dirTree->current, users, filename, 'f');
        }

        tmpNode = IsDir(dirTree, filename);
        strncpy(tmpNode->contents, contents, MAX_LINES * CON_LEN);
    }
    return;
}

void cat(DirTree* dirtree, Users* users, char* cmd)
{
    TreeNode* currentNode = NULL;
    TreeNode* tmpNode = NULL;
    TreeNode* tmpNode2 = NULL;

    if (cmd == NULL)
    {
        printf("wrong command\n");
        return;
    }
    currentNode = dirtree->current;

    if (cmd[0] == '>') {  //make file
        char* opt = strtok(cmd, " ");
        char* path = strtok(NULL, "");
        char fpath[100];
        strncpy(fpath, path, 100);
        char* fname;
        if (fpath == NULL) {
            printf("wrong directory\n");
            return;
        }
        if (fpath[0] == '/') {  //절대경로
            char* token = strtok(path, "/");
            if (strcmp(token, "root") != 0) {
                printf("wrong directory\n");
                return;
            }
            char* ptr = strrchr(fpath, '/');
            if (ptr != NULL) {
                fname = ptr + 1;
                *ptr = '\0';
            }
            tmpNode = IsDir(dirtree, fpath);
            if (tmpNode == NULL) {
                printf("wrong directory\n");
                return;
            }
        }
        else {  //상대경로
            fname = path;
            tmpNode = dirtree->current;
        }

        if (IsPermission(tmpNode, users, 'w') != 0) {
            printf("permission deny\n");
            return;
        }
        dirtree->current = tmpNode;
        concatenate(dirtree, users, fname, 0);
        return;
    }
    else if (cmd[0] == '-') {
        char* opt = strtok(cmd, " ");
        char* path = strtok(NULL, "");
        char fpath[100];
        char* fname;
        strncpy(fpath, path, 100);
        if (strcmp(opt, "-n") != 0) {
            printf("wrong command\n");
            return;
        }
        if (fpath == NULL) {
            printf("wrong directory\n");
            return;
        }
        if (fpath[0] == '/') {  //절대경로
            char* token = strtok(path, "/");
            if (strcmp(token, "root") != 0) {
                printf("wrong directory\n");
                return;
            }
            char* ptr = strrchr(fpath, '/');
            if (ptr != NULL) {
                fname = ptr + 1;
                *ptr = '\0';
            }
            tmpNode = IsDir(dirtree, fpath);
            if (tmpNode == NULL) {
                printf("wrong directory\n");
                return;
            }
        }
        else {  //상대경로
            fname = path;
            tmpNode = dirtree->current;
        }

        if (IsPermission(tmpNode, users, 'r') != 0) {
            printf("permission deny\n");
            return;
        }
        dirtree->current = tmpNode;
        concatenate(dirtree, users, fname, 2);
        return;
    }
    else {
        char* path = strtok(cmd, "");
        char* fpath[100];
        char* fname;
        strncpy(fpath, path, 100);

        if (fpath == NULL) {
            printf("wrong directory\n");
            return;
        }
        if (path[0] == '/') {  //절대경로
            char* token = strtok(path, "/");
            if (strcmp(token, "root") != 0) {
                printf("wrong directory\n");
                return;
            }
            char* ptr = strrchr(fpath, '/');
            if (ptr != NULL) {
                fname = ptr + 1;
                *ptr = '\0';
            }
            tmpNode = IsDir(dirtree, fpath);
            if (tmpNode == NULL) {
                printf("wrong directory\n");
                return;
            }
        }
        else {  //상대경로
            fname = fpath;
            tmpNode = dirtree->current;
        }

        if (IsPermission(tmpNode, users, 'r') != 0) {
            printf("permission deny\n");
            return;
        }
        dirtree->current = tmpNode;
        concatenate(dirtree, users, fname, 1);
        return;
    }
}

void* thread_cat(void* arg) {
    thread_data* data = (thread_data*)arg;
    cat(data->dirtree, data->users, data->dir_name);
    free(arg);
    return NULL;
}

void multithread_cat(DirTree* dirtree, Users* users, char* dirs) {
    pthread_t thread_ids[50];
    int i = 0;
    if (dirs[0] == '-' || dirs[0] == '>') {
        cat(dirtree, users, dirs);
        return;
    }
    char* token = strtok(dirs, " ");
    while (token != NULL) {
        thread_data* data = (thread_data*)malloc(sizeof(thread_data));
        data->dirtree = dirtree;
        data->users = users;
        strncpy(data->dir_name, token, 50);
        pthread_create(&thread_ids[i], NULL, thread_cat, data);
        i++;
        token = strtok(NULL, " ");
    }

    for (int j = 0; j < i; j++) {
        pthread_join(thread_ids[j], NULL);
    }
}