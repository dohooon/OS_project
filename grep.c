#include "grep.h"


void grep(DirTree* dirtree, Users* users, char* cmd) {


    if (cmd[0] == '-') {
        char* opt;
        char* findword;
        char* path;
        opt = strtok(cmd, " ");
        findword = strtok(NULL, " ");
        path = strtok(NULL, "");
        if ((opt == NULL || findword == NULL) || path == NULL) {
            printf("wrong command\n");
            return;
        }
        // 옵션 처리
        int line_number = 0;
        int ignore_case = 0;
        int invert_match = 0;

        if (strcmp(opt, "-n") == 0) {
            line_number = 1;
        }
        else if (strcmp(opt, "-v") == 0) {
            invert_match = 1;
        }
        else if (strcmp(opt, "-i") == 0) {
            ignore_case = 1;
        }
        else {
            printf("wrong command\n");
            return;
        }
        TreeNode* tmpNode = NULL;

        tmpNode = IsDir(dirtree, path);
        if (tmpNode == NULL) {
            printf("Wrong directory\n");
            return;
        }

        if (tmpNode->type != 'f') {
            printf("%s is not a file\n", tmpNode->name);
            return;
        }

        // 검색어에 따라 파일 내용 처리
        char* line = NULL;
        int line_count = 1;
        char temp_line[CON_LEN];
        char temp_findword[256];
        char* result;

        strncpy(temp_findword, findword, 256);

        if (ignore_case) {
            for (int i = 0; temp_findword[i]; i++) {
                temp_findword[i] = tolower(temp_findword[i]);
            }
        }
        char temp[MAX_LINES * CON_LEN];
        strncpy(temp, tmpNode->contents, MAX_LINES * CON_LEN);
        strcat(temp, "\n");
        line = strtok(temp, "\n");

        while (line != NULL) {
            strncpy(temp_line, line, CON_LEN);

            if (ignore_case) {
                for (int i = 0; temp_line[i]; i++) {
                    temp_line[i] = tolower(temp_line[i]);
                }
            }

            result = strstr(temp_line, temp_findword);

            if (line_number) {
                if (result != NULL && !invert_match) {
                    printf("%d: %s\n", line_count, line);
                }
            }
            else if(invert_match){
                if ((result == NULL && invert_match) || (result != NULL && !invert_match)) {
                    printf("%s\n", line);
                }
            }
            else {
                if (result != NULL && !invert_match) {
                    printf("%s\n", line);
                }
            }

            line = strtok(NULL, "\n");
            line_count++;
        }
    }
    else {
        char* findword;
        char* path;
        findword = strtok(cmd, " ");
        path = strtok(NULL, "");
        if (findword == NULL || path == NULL) {
            printf("wrong command\n");
            return;
        }
        TreeNode* tmpNode = NULL;
        tmpNode = IsDir(dirtree, path);
        if (tmpNode == NULL) {
            printf("Wrong directory\n");
            return;
        }

        if (tmpNode->type != 'f') {
            printf("%s is not a file\n", tmpNode->name);
            return;
        }

        // 검색어에 따라 파일 내용 처리
        char* line = NULL;
        char temp_line[CON_LEN];
        char temp_findword[256];
        char* result;

        strncpy(temp_findword, findword, 256);

        char temp[MAX_LINES * CON_LEN];
        strncpy(temp, tmpNode->contents, MAX_LINES * CON_LEN);
        strcat(temp, "\n");
        line = strtok(temp, "\n");

        while (line != NULL) {
            strncpy(temp_line, line, CON_LEN);


            result = strstr(temp_line, temp_findword);

            if (result != NULL) {
                printf("%s\n", line);
            }

            line = strtok(NULL, "\n");
        }
        return;
    }
}