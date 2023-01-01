#ifndef __Double_Linked_List__
#define __Double_Linked_List__

#define NAME_LENGTH 30
#define NUMBER_LENGTH 20
#define GROUP_LENGTH 20

typedef struct __Node {    
    int id;             // 노드 고유의 번호 10001부터 시작
    int index;         // 정렬한 후 일렬번호
    char name[NAME_LENGTH];     // 영문 이름
    char number[NUMBER_LENGTH]; // 전화 번호
    char group[GROUP_LENGTH];
    _Bool search_hit; // 해당 노드가 검색조건을 만족한다면 이 flag를 1로 설정해서 다음함수로 넘겨줌 메인메뉴로 돌아갈 때 0으로 초기화 필요
    _Bool favorite; // 즐겨찾기
    int matchedValue; // 검색시 어느 필드로 검색이 되었는지 표시
    
    struct __Node* pPrev;
    struct __Node* pNext;    
} stNode;  // 노드 구조체 

typedef struct __List {
    stNode* pHead;
    stNode* pTail;    
    _Bool sort_needs;
    int sort_order;
    int count_node;
} stList;   // 리스트 구조체

typedef struct __SearchedList
{
    struct __SearchedList* NextNode;
    struct __SearchedList* PrevNode;
    stNode* node;
    int matchedWith;
} stSearchedList;  // 검색된 리스트를 가지는 구조체

// 함수 선언
extern void InitializeList(stList* pList);              // 메모리 할당해서 리스트 만들기
stNode* MakeNode(stNode* data);                //메모리 할당해서 노드 만들기
extern void AddtoTailNode(stList* pList, stNode* data);  //Tail에 노드 추가
extern void AddtoHeadNode(stList* pList, stNode* data);   // Head에 노드 추가
extern void DeleteNode(stList* pList, int index);        // 현재 노드 삭제 하기 (id 기준)
extern void PrintList(stList* pList);                 // 전체 리스트 출력하기
extern int IsEmpty(stList *pList) ;
extern void CountNode(stList *pList);

extern void getData(stList* pList, char*); // CSV파일에서 데이터를 읽어 온다.
extern stNode* getNode(char*); // 데이터의 한줄을 파싱해서 stNode의 값 필드값으로 매핑하고 해당 노드 값을 리턴한다.
extern stNode* searchDisplay(stList*); // 검색 화면으로 넘어가서 검색 값을 입력 받고 최종 선택된 한개의 노드값을 리턴한다.
extern stSearchedList* SearchingValue(int mode, stList*, char*); // 데이터에서 찾고자 하는 값을 입력하면 매칭되는 값들의 리스트를 리턴한다.
int stringFind(char* a, char* b); // 문자열 2개를 비교해서 포함 여부를 확인하고 포함 시 1을 미포함시 0을 리턴한다.

#endif