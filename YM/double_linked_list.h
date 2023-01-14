
#ifndef __Double_Linked_List__
#define __Double_Linked_List__

#define NAME_LENGTH 30
#define NUMBER_LENGTH 20
#define GROUP_LENGTH 20

typedef struct __Node {
    int id;             // ��� ������ ��ȣ 10001���� ����
    int index;         // ������ �� �ϷĹ�ȣ
    char name[NAME_LENGTH];     // ���� �̸�
    char number[NUMBER_LENGTH]; // ��ȭ ��ȣ
    char group[GROUP_LENGTH];
    bool search_hit; // �ش� ��尡 �˻������� �����Ѵٸ� �� flag�� 1�� �����ؼ� �����Լ��� �Ѱ��� ���θ޴��� ���ư� �� 0���� �ʱ�ȭ �ʿ�
    bool favorite; // ���ã��

    struct __Node* pPrev;
    struct __Node* pNext;
} stNode;  // ��� ����ü 

typedef struct __List {
    stNode* pHead;
    stNode* pTail;
    bool sort_needs;
    int sort_order;
    int count_node;
} stList;   // ����Ʈ ����ü

// �Լ� ����

extern void InitializeList(stList* pList);              // �޸� �Ҵ��ؼ� ����Ʈ �����
stNode* MakeNode(stNode* data);                //�޸� �Ҵ��ؼ� ��� �����
extern void AddtoTailNode(stList* pList, stNode* data);  //Tail�� ��� �߰�
extern void AddtoHeadNode(stList* pList, stNode* data);   // Head�� ��� �߰�
//extern void DeleteNode(stList* pList, int index);        // ���� ��� ���� �ϱ� (id ����)
extern void PrintList(stList* pList);                 // ��ü ����Ʈ ����ϱ�
extern int IsEmpty(stList* pList);
extern void CountNode(stList* pList);
//extern void DeleteNode(stNode* Node, stList* pList, int index);
extern void DeleteNode(stNode* Node);

#endif 