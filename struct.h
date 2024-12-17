#ifndef STRUCT_H
#define STRUCT_H
#define NAME_LEN 100
#define DIR_LEN 100
#define CON_LEN 200
#define MAX_LINES 10
#define SIZE 100
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>

typedef struct User_node
{
    char name[NAME_LEN];
    int User;
    int Group;
    int Year;
    int Month;
    int Day;
    int Hour;
    int Minute;
    struct User_node* link;
}UserNode;

typedef struct User
{
    int topUser;
    int topGroup;
    UserNode* head;
    UserNode* tail;
    UserNode* current;
}Users;

typedef struct Tree_Node
{
    char name[NAME_LEN];
    char type;
    char contents[MAX_LINES * CON_LEN];
    int User;
    int Group;
    int permission[9];
    int size;
    int Year;
    int Month;
    int Day;
    int Hour;
    int Minute;
    struct Tree_Node* parent;
    struct Tree_Node* child;
    struct Tree_Node* sibling;
}TreeNode;

typedef struct Dir_Tree
{
    TreeNode* root;
    TreeNode* current;
}DirTree;

typedef struct thread_data {
    DirTree* dirtree;
    Users* users;
    char dir_name[50];
} thread_data;

#endif