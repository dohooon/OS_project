#include "save_load.h"

void setParentPointers(TreeNode* node, TreeNode* parent) {
    if (node != NULL) {
        node->parent = parent;
        setParentPointers(node->child, node);
        setParentPointers(node->sibling, parent);
    }
}
void writeTreeToFile(TreeNode* node, FILE* file, FILE* Data) {
    if (node == NULL) {
        fprintf(file, "%d ", -2);  // -2 is used to denote null nodes
    }
    else {
        fprintf(file, "%d ", 0);
        fprintf(file, "%s %c %d %d ", node->name, node->type, node->User, node->Group);
        for (int i = 0; i < 9; i++) {
            fprintf(file, "%d ", node->permission[i]);
        }
        fprintf(file, "%d %d %d %d %d %d ", node->size, node->Year, node->Month, node->Day, node->Hour, node->Minute);
        fprintf(Data, "%s", node->contents);
        fprintf(Data, "-- end of data --\n");
        writeTreeToFile(node->child, file, Data);
        writeTreeToFile(node->sibling, file, Data);
    }
}

TreeNode* readTreeFromFile(FILE* file, FILE* Data) {
    int data;
    if (fscanf(file, "%d", &data) == -1 || data == -2) {
        return NULL;
    }
    else {
        TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
        fscanf(file, "%s %c %d %d", node->name, &(node->type), &(node->User), &(node->Group));
        for (int i = 0; i < 9; i++) {
            fscanf(file, "%d", &(node->permission[i]));
        }
        fscanf(file, "%d %d %d %d %d %d ", &(node->size), &(node->Year), &(node->Month), &(node->Day), &(node->Hour), &(node->Minute));
        // load data
        char line[CON_LEN];
        fgets(line, sizeof(line), Data);
        strncpy(node->contents, line, sizeof(node->contents));
        while (1) {
            fgets(line, sizeof(line), Data);
            if (strcmp(line, "-- end of data --\n") == 0) break;
            strcat(node->contents, line);
        }
        //
        node->child = readTreeFromFile(file, Data);
        node->sibling = readTreeFromFile(file, Data);
        return node;
    }
}
void saveTree(DirTree* dirtree, char* filename, char* dataname) {
    FILE* file = fopen(filename, "w");
    FILE* data = fopen(dataname, "w");
    if (file == NULL) {
        printf("Cannot open file %s\n", filename);
        return;
    }
    writeTreeToFile(dirtree->root, file, data);
    fclose(file);
}

DirTree* loadTree(char* filename, char* dataname) {
    FILE* file = fopen(filename, "r");
    FILE* data = fopen(dataname, "r");
    if (file == NULL) {
        return NULL;
    }
    TreeNode* root = readTreeFromFile(file, data);
    fclose(file);
    setParentPointers(root, NULL);  // set parent pointers
    DirTree* dirtree = (DirTree*)malloc(sizeof(DirTree));
    dirtree->root = root;
    dirtree->current = root;
    return dirtree;
}