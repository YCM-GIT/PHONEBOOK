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
} node;

typedef struct SearchedList
{
    /* data */
    struct Node* Current;
    struct Node* Head;
    struct node* Tail;
    int numberSearched;
} searchedList;

node* getData(char*);
node* getNode(char*);