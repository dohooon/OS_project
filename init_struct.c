#include "init_struct.h"

Users* init_user(){
    time_t timer = time(NULL);
    struct tm* t = localtime(&timer);
    Users* users = (Users*)malloc(sizeof(Users));
    UserNode* manager = (UserNode*)malloc(sizeof(UserNode));
    strncpy(manager->name, "Manager", NAME_LEN);
    manager->User = 1;
    manager->Group = 1;
    manager->Year = t->tm_year+1900;
    manager->Month = t->tm_mon+1;
    manager->Day = t->tm_mday;
    manager->Hour = t->tm_hour;
    manager->Minute = t->tm_min;
    manager->link = NULL;
    users->head = manager;
    users->tail = manager;
    users->current = manager;
    return users;
}

DirTree* init_Dir(Users* users){
    time_t timer = time(NULL);
    struct tm* t = localtime(&timer);
    DirTree* dirtree = (DirTree*)malloc(sizeof(DirTree));
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode* home = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode* text = (TreeNode*)malloc(sizeof(TreeNode));

    strncpy(root->name,"root",NAME_LEN);
    strncpy(home->name,"home",NAME_LEN);
    strncpy(text->name,"text.txt",NAME_LEN);

    root->type = 'd';
    home->type = 'd';
    text->type = 'f';

    root->User = users->current->User;
    home->User = users->current->User;
    text->User = users->current->User;
    root->Group = users->current->Group;
    home->Group = users->current->Group;
    text->Group = users->current->Group;

    int root_per[9] = {1,1,1,0,0,0,0,0,0};  //rwx------  root폴더는 manager만 읽기,쓰기,실행 가능
    int home_per[9] = {1,1,1,1,0,1,1,0,1};  //rwxr-xr-x
    memcpy(root->permission, root_per, sizeof(root_per));
    memcpy(home->permission, home_per, sizeof(home_per));
    memcpy(text->permission,home_per,sizeof(home_per));

    root->size = 4096;
    home->size = 4096;
    text->size = 4096;

    root->Year = t->tm_year+1900;
    root->Month = t->tm_mon+1;
    root->Day = t->tm_mday;
    root->Hour = t->tm_hour;
    root->Minute = t->tm_min;

    home->Year = t->tm_year+1900;
    home->Month = t->tm_mon+1;
    home->Day = t->tm_mday;
    home->Hour = t->tm_hour;
    home->Minute = t->tm_min;

    text->Year = t->tm_year+1900;
    text->Month = t->tm_mon+1;
    text->Day = t->tm_mday;
    text->Hour = t->tm_hour;
    text->Minute = t->tm_min;

    root->parent = NULL;
    root->child = home;
    root->sibling = NULL;

    home->parent = root;
    home->child = text;
    home->sibling = NULL;

    text->parent = home;
    text->child = NULL;
    text->sibling = NULL;

    strncpy(root->contents, "\n", MAX_LINES * CON_LEN);
    strncpy(home->contents, "\n", MAX_LINES * CON_LEN);
    strncpy(text->contents, "test file\n", MAX_LINES * CON_LEN);

    dirtree->root = root;
    dirtree->current = home;

    return dirtree;
}