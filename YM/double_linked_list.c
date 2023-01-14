#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "double_linked_list.h"

// �Լ� ����
extern void InitializeList(stList* pList) {
    stList* list = malloc(sizeof(stList));
    list->pHead = list->pTail = NULL;
    list->sort_needs = 1;
    list->sort_order = 0;
    list->count_node = 0;
}

extern stNode* MakeNode(stNode* data) {
    stNode* node = malloc(sizeof(stNode));
    node = data;
    node->pPrev = node->pNext = NULL;
    // id �ο��ϴ� ����� �߰� ���
    return node;
}  //��带 ����� ���� �޸� �Ҵ��ϰ� �ʱ�ȭ�ϱ�

extern void AddtoTailNode(stList* pList, stNode* data) {   // ��带 tail�� ��� �߰�
    stNode* node = MakeNode(data);
    if (IsEmpty(pList)) {
        pList->pHead = pList->pTail = node;
    }
    else {
        node->pPrev = pList->pTail;
        node->pNext = NULL;
        pList->pTail->pNext = node;
        pList->pTail = node;
    }
}  //List�� �ڿ� �ű� ��� �߰�

extern void AddtoHeadNode(stList* pList, stNode* data) { //��带 Head�� �߰�    
    stNode* node = MakeNode(data);
    if (IsEmpty(pList)) {
        pList->pHead = pList->pTail = node;
    }
    else {
        node->pNext = pList->pHead;
        pList->pHead->pPrev = node;
        pList->pHead = node;
        node->pPrev = NULL;
    }
}



extern void DeleteNode(stNode* Node) {
      
    Node->pNext->pPrev = Node->pPrev;
    Node->pPrev->pNext = Node->pNext;

    free(Node);
    Node->id = 0;
    return;    
}
  

/*// id�� �޾Ƽ� ���� id�� ���� ��� ���� �ϱ�
extern void DeleteNode(stList* pList, int index) {
    stNode* cur;
    if(IsEmpty(pList)) {
        printf("There is no member.\n");
    } else {
        cur = pList->pHead;
        while(cur->pNext !=NULL) {
            if (index == cur->index) {   // ����id�� ���� ��带 ����
                cur->pPrev->pNext = cur->pNext;
                cur->pNext->pPrev = cur->pPrev;
                free(cur);   // �޸� �Ҵ� ����
                break;
            }
            cur = cur->pNext;
        }
    }
}
*/

extern void PrintList(stList* pList) {
    stNode* cur;
    for (cur = pList->pHead; cur != NULL; cur = cur->pNext) {
        printf("%5d ", cur->id);
        printf("%3d ", cur->index);
        printf("%30s ", cur->name);
        printf("%20s ", cur->number);
        printf("%20s ", cur->group);
        printf("%3d", cur->favorite);
        printf("\n");
    }
    printf("\n");
}

extern int IsEmpty(stList* pList) {
    return (pList->pHead == NULL);
} // ����Ʈ�� ����ִ� �� Ȯ��

extern void CountNode(stList* pList) {
    int count = 0;
    stNode* cur;
    for (cur = pList->pHead; cur != NULL; cur = cur->pNext) {
        count++;
    }
    (*pList).count_node = count;
    //    printf("%d\n",count);
}
