// 221231 현재: gcc main.c showlist.c double_linked_list.c -o main.exe
// 함수 추가 시, 각 함수의 "// 주석 처리 필요" 부분 주석 처리 필요.

//main.c 대비 변경점
// 1. Node 구조체 변경 (Node → stNode)
// 2. AddNewNodeSample, Search, ShowList, ShowGroup 함수를 매개변수를 받도록 변경: 예: AddNewNodeSample() → AddNewNodeSample(stList* address_of_list_variables)
// 3. 구조체 안에 문자열을 대입하기 위해, strcpy 함수 사용. 이를 위해 #include<string.h> 필요
// 4. #include "double_linked_list.h", #include "phonebook.h" 추가.

#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "double_linked_list.h"
#include "phonebook.h"

#define NAME_LENGTH 30
#define NUMBER_LENGTH 20
#define GROUP_LENGTH 20

// 아래 주석은 "double_linked_list.h"에서 이미 선언함.
/*
typedef struct __Node {    
    int id;             // 노드 고유의 번호 10001부터 시작
    int index;         // 정렬한 후 일렬번호
    char name[NAME_LENGTH];     // 영문 이름
    char number[NUMBER_LENGTH]; // 전화 번호
    char group[GROUP_LENGTH];
    bool search_hit; // 해당 노드가 검색조건을 만족한다면 이 flag를 1로 설정해서 다음함수로 넘겨줌 메인메뉴로 돌아갈 때 0으로 초기화 필요
    bool favorite; // 즐겨찾기
    
    struct __Node* pPrev;
    struct __Node* pNext;    
} stNode;  // 노드 구조체 

typedef struct __List {
    stNode* pHead;
    stNode* pTail;    
    bool sort_needs;
    int sort_order;
    int count_node;
} stList;   // 리스트 구조체
*/

stList list_variables;

// 주석 처리 필요
void AddNewNodeSample(stList* address_of_list_variables);     // 3개의 샘플 노드를 추가한다. 샘플파일의 10001~10003번 데이터와 같음.
stNode* Search(stList* address_of_list_variables);
void ShowNode(stNode* address_of_Node);
// stNode* ShowList(stList* address_of_list_variables);
stNode* ShowGroup(stList* address_of_list_variables);
void ImportExport();
void ChangeOrder();

void main(){                 // (나중에는 없어질 기능) 3개 샘플 노드를 추가할 것인지 물어보고, 입력에 따라 추가한/안한 후, 메인화면을 띄움.

	char c;
	printf("Do you want add hard-coded sample of nodes? [Y/N]\n");
	
	while(1){
		scanf(" %c", &c);
		if (c == 'Y' || c == 'y'){
			AddNewNodeSample(&list_variables);
			break;
		}
		else if(c == 'N' || c == 'n'){
			break;
		}
		else{
			printf("Wrong command. Type again.\n");
			continue;
		}
			
	}
     
	int command;
	while(1){                           // 메인 화면. 프로그램 동작 동안 계속 이 while 문 안에 있는 상태이다.
		printf("1. add a new node\n2. search\n3. show list\n4. show group\n5. import/export\n6. change order\n\n");
		printf("Input your command number: ");
		//scanf_s(%d, &command, sizeof(int));
		scanf("%d", &command);

		printf("your choice: %d\n", command);
		if (command == 1) {
			//AddNewNode();								//신규 노드 추가 함수 (JIJ)
			printf("AddNewNode();\n");
			continue;
		}
		else if (command == 2){
			ShowNode(Search(&list_variables));	            			// Search 함수를 호출 후, 사용자가 노드를 선택하면 ShowNode 함수 호출.
			//printf("ShowNode(Search());\n");                    // ?? 사용자가 노드를 선택하지 않고, 메인메뉴로 돌아가려면?
			continue;
		}
		else if (command == 3){
			ShowNode(ShowList(&list_variables));						// ShowList 함수를 호출 후, 사용자가 노드를 선택하면 ShowNode 함수 호출.
			//printf("ShowNode(ShowList());\n");                  // ?? 사용자가 노드를 선택하지 않고, 메인메뉴로 돌아가려면?
			continue;
		}
		else if (command == 4){
			ShowNode(ShowGroup(&list_variables));													
			//printf("ShowNode(ShowGroup());\n");
			continue;		
		}
        else if (command == 5){                          // import, export 함수 (NHM)
			ImportExport();													
			//printf("ImportExport();\n");
			continue;		
		}
        else if (command == 6){                          // 정렬 기준 바꾸기.
			ChangeOrder();													
			//printf("ChangeOrder();\n");
			continue;		
		}

		else {
			printf("Wrong command. Type again.\n");
			continue;															// 잘못 입력했을 경우에는 while문을 빠져나가지 않고, 입력을 계속해서 받는다.
		}
	}

}


void AddNewNodeSample(stList* address_of_list_variables){                                    // 3개 샘플 노드 강제 추가 함수.

	address_of_list_variables->pHead = (stNode*)malloc(sizeof(stNode));		// list_variables 구조체의 멤버인 pHead(주소)가 가리키게 한다.			// 1번째 노드의 영역을 생성해 주고, 전역변수인 p_head(주소)가 가리키게 한다.
	address_of_list_variables->pHead->id = 10001;
	address_of_list_variables->pHead->index = 1;	
	strcpy(address_of_list_variables->pHead->name, "KIM CheolMin");
	strcpy(address_of_list_variables->pHead->number, "010-5324-2342");
	strcpy(address_of_list_variables->pHead->group, "TEAM");
	address_of_list_variables->pHead->search_hit = 0;
	address_of_list_variables->pHead->favorite = 0;
	address_of_list_variables->pHead->pPrev = NULL;
	address_of_list_variables->pHead->pNext = NULL;
	//list_variables.pHead->pPrev = NULL;  ?? 이렇게 직접적으로 주고 받으면 단점?
	//list_variables.pHead->pNext = NULL;
	
	
	stNode* node_sample_2 = (stNode*)malloc(sizeof(stNode));		// 2번째 노드의 영역을 생성해 주고, node_sample_2(주소)가 가리키게 함.
	node_sample_2->id = 10002;
	node_sample_2->index = 2;	
	strcpy(node_sample_2->name, "NAM HyeMin");
	strcpy(node_sample_2->number, "010-3333-2222");
	strcpy(node_sample_2->group, "SECURITY");
	node_sample_2->search_hit = 0;
	node_sample_2->favorite = 1;
	node_sample_2->pPrev = address_of_list_variables->pHead;							// 2번째 노드이므로, 이 노드의 prev가 첫 번째 노드의 주소인 p_head가 되게 함.
	node_sample_2->pNext = NULL;
	
	address_of_list_variables->pHead->pNext = node_sample_2;							// 2번째 노드가 추가됐으므로, p_head가 가리키는 첫 번째 노드의 next에 node_sample_2(주소)를 넣음.
	

	address_of_list_variables->pTail = (stNode*)malloc(sizeof(stNode));		// 3번째 노드의 영역을 생성해 주고, 전역변수인 p_tail(주소)가 가리키게 한다.
	address_of_list_variables->pTail->id = 10003;
	address_of_list_variables->pTail->index = 3;	
	strcpy(address_of_list_variables->pTail->name, "YANG ChangMin");
	strcpy(address_of_list_variables->pTail->number, "010-5879-8156");
	strcpy(address_of_list_variables->pTail->group, "VEHICLE");
	address_of_list_variables->pTail->search_hit = 0;
	address_of_list_variables->pTail->favorite = 1;
	address_of_list_variables->pTail->pPrev = node_sample_2;							// 3번째 노드이므로, 이 노드의 prev가 2번째 노드의 주소인 node_sample_2가 되게 함.
	address_of_list_variables->pTail->pNext = NULL;
	
	node_sample_2->pNext = address_of_list_variables->pTail;							// 3번째 노드가 추가됐으므로, node_sample_2가 가리키는 2번째 노드의 next에 p_tail(주소)를 넣음.
	

	
	printf("------- below nodes were added -------\n");
	stNode* p = address_of_list_variables->pHead;										// 잘 들어갔는지 테스트 함수.
	while(p!=NULL){
		printf("%s\n", p->name);		
		//printf("%d\n", p->id);
		p = p->pNext;
	}
	printf("--------------------------------------\n");
}


// 주석 처리 필요
stNode* Search(stList* address_of_list_variables){                                                           // 테스트용.
    // return address_of_list_variables->pHead;
	return address_of_list_variables->pHead;
}

void ShowNode(stNode* address_of_Node){                                    // 테스트용.
    printf("%d      %d      %s      %s      %s      %d      %d\n", 
    address_of_Node->id, 
    address_of_Node->index,
    address_of_Node->name, 
    address_of_Node->number, 
    address_of_Node->group, 
    address_of_Node->search_hit, 
    address_of_Node->favorite 
    );
}

// showlist.c 와 함께 컴파일할 때는 아래를 주석처리해야 함.
/* 
stNode* ShowList(stList* address_of_list_variables){                                                        // 테스트용.
    return address_of_list_variables->pHead->pNext;
}
*/


stNode* ShowGroup(stList* address_of_list_variables){                                                        // 테스트용.
    return address_of_list_variables->pHead->pNext->pNext
	
	;
}

void ImportExport(){                                                       // 테스트용.
	printf("ImportExport();\n");
}

void ChangeOrder(){                                                         // 테스트용.
	printf("ChangeOrder();\n");
}

