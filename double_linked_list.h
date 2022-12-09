#ifndef __Double_Linked_List__
#define __Double_Linked_List__

#define NAME_LENGTH 30
#define NUMBER_LENGTH 20
#define GROUP_LENGTH 20

typedef struct __Member {    
    int id;             // 노드 고유의 번호 10001부터 시작
    int index;         // 정렬한 후 일렬번호
    char name[NAME_LENGTH];     // 영문 이름
    char number[NUMBER_LENGTH]; // 전화 번호
    char group[GROUP_LENGTH];
    bool search_hit; // 해당 노드가 검색조건을 만족한다면 이 flag를 1로 설정해서 다음함수로 넘겨줌 메인메뉴로 돌아갈 때 0으로 초기화 필요
    bool favorite; // 즐겨찾기
    
} stMember;  // 노드의 데이터 구조체 

typedef struct __Node {
    struct __Node* pPrev;
    struct __Node* pNext;
    stMember stData;    
} stNode;  // 노드 구조체 

typedef struct __List {
    stNode* pHead;
    stNode* pTail;    
    bool sort_needs;
    int sort_order;
    int count_node;
} stList;   // 리스트 구조체

// 함수 선언
void InitializeList(stList* pList);              // 메모리 할당해서 리스트 만들기
stNode* MakeNode(stMember data);                //메모리 할당해서 노드 만들기
void AddtoTailNode(stList* pList, stMember data);  //Tail에 노드 추가
void AddtoHeadNode(stList* pList, stNode* node);   // Head에 노드 추가
void DeleteNode(stList* pList, int index);        // 현재 노드 삭제 하기 (id 기준)
void PrintList(stList* pList);                 // 전체 리스트 출력하기
int IsEmpty(stList *pList) ;
void CountNode(stList *pList);
void Renumbering(stList* pList);  //index번호를 다시 매김


#endif 