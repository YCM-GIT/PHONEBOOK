#ifndef __nodeHead__
#define __nodeHead__

#define NAME_LENGTH 100
#define NUMBER_LENGTH 100
#define GROUP_LENGTH 100

typedef struct Node
{
    /* data */
    int id;
    int index;
    char name[NAME_LENGTH];
    char number[NUMBER_LENGTH];
    char group[GROUP_LENGTH];
    int search_hit;
    int favorite;
    struct Node* Prev;
    struct Node* Next;
    int matchedValue;
} node;

typedef struct SearchedList
{
    /* data */
    struct SearchedList* NextNode;
    struct SearchedList* PrevNode;
    struct Node* node;
    int matchedWith;
} searchedList;

node* getData(char*);
node* getNode(char*);

node* searchDisplay(node*);
searchedList* SearchingValue(node*, char*);
int stringFind(char*, char*);

#endif