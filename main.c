// 230109 현재: gcc main.c showlist.c double_linked_list.c newinsertlist.c searchDisplay.c showNode.c -o main.exe
// 				※ Import_Export.c는 자체 main 함수 포함하고 있어서, 통합 빌드하지 않음.
// 함수 추가 시, 각 함수의 "// 주석 처리 필요" 부분 주석 처리 필요.

//main.c 대비 변경점
// 1. (221231) Node 구조체 변경 (Node → stNode)
// 2. AddNewNodeSample, Search, ShowList, ShowGroup 함수를 매개변수를 받도록 변경: 예: AddNewNodeSample() → AddNewNodeSample(stList* address_of_list_variables)
// 3. 구조체 안에 문자열을 대입하기 위해, strcpy 함수 사용. 이를 위해 #include<string.h> 필요
// 4. #include "double_linked_list.h", #include "phonebook.h" 추가.
// 5. (230108) Search, ShowList, ShowGroup 함수에서 NULL값 리턴 시, main의 while문으로 복귀. (NULL값이 아니라면, ShowNode 함수 호출)
// 6. stSearchedList 구조체 선언. (double_linked_list.h 안에)

#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "double_linked_list.h"
#include "phonebook.h"

#define NAME_LENGTH 30
#define NUMBER_LENGTH 20
#define GROUP_LENGTH 20
#define FILE_NAME "phonebook_sample2.csv"

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

//stList list_variables; main() 안으로 이동함(230108).

// 다른 사람들이 작성한 c 파일과 함께 컴파일할 때는 아래 중 해당 함수를 주석처리해야 함.
void AddNewNodeSample(stList* address_of_list_variables);     // 3개의 샘플 노드를 추가한다. 샘플파일의 10001~10003번 데이터와 같음.
stNode* Search(stList* address_of_list_variables); // YTY. searchDisplay.C
// void ShowNode(stNode* address_of_Node);	// YM.
// stNode* ShowList(stList* address_of_list_variables);	// CEB.
// stNode* ShowGroup(char* group_name, stList* address_of_list_variables);	// JSY.
void ImportExport();
void ChangeOrder();
void getData(stList* pList, char* filename);
stNode* getNode(char* stringValue);
void InitializeList1(stList* pList);


void main(){                 // 샘플 파일에서 읽어올 것인지 물어보고, 입력에 따라 추가한/안한 후, 메인화면을 띄움.

	stList list_variables;
	InitializeList1(&list_variables);	// list_variables의 변수들을 초기화. 
	char c;
	printf("Do you want add hard-coded sample of nodes? [Y/N]\n");
	
	while(1){
		scanf(" %c", &c);
		if (c == 'Y' || c == 'y'){
			// AddNewNodeSample(&list_variables); // 테스트용.
			getData(&list_variables, FILE_NAME);
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
			AddNewNode(&list_variables);								//신규 노드 추가 함수 (JIJ)
			//printf("AddNewNode();\n");
			continue;
		}
		else if (command == 2){
			//ShowNode(Search(&list_variables)); 테스트용.
			
			// Search 함수를 호출 후, 1) 사용자가 노드를 선택하면 ShowNode 함수 호출. 2) 제대로 선택하지 않으면 (NULL을 리턴 받아서) 메인 메뉴로 돌아감.
			//stNode* p_temp_node = Search(&list_variables);
			stNode* p_temp_node = searchDisplay(&list_variables);
			if (p_temp_node == NULL){
				continue;
			}
			else {
				//ShowNode(p_temp_node);				
				ShowNode(p_temp_node, &list_variables);
			}

			continue;
		}
		else if (command == 3){
			//ShowNode(ShowList(&list_variables)); 테스트용.			

			// ShowList 함수를 호출 후, 1) 사용자가 노드를 선택하면 ShowNode 함수 호출. 2) 제대로 선택하지 않으면 (NULL을 리턴 받아서) 메인 메뉴로 돌아감.
			stNode* p_temp_node = ShowList(&list_variables);
			if (p_temp_node == NULL){
				continue;
			}
			else {
				//ShowNode(p_temp_node);
				ShowNode(p_temp_node, &list_variables);
			}
			
			continue;
		}
		else if (command == 4){
			// 어느 그룹을 보여줄 것인지 묻고, 문자열을 ShowGroup에 넘겨주는 기능 시작.			
			printf("------- Group list -------\n");
			printf("DOMAIN\nSECURITY\nTEAM\nVEHICLE\n");
			printf("--------------------------\n");
			printf("Type Group name correctly: ");
			//scanf_s(%d, &command, sizeof(int));
			char group_name[GROUP_LENGTH];
			scanf("%s", group_name);
			printf("%s\n", group_name);
			// 어느 그룹을 보여줄 것인지 묻고, 문자열을 ShowGroup에 넘겨주는 기능 완료.

			// ShowNode(ShowGroup(group_name, &list_variables), &list_variables);	// 테스트용.

			// ShowGroup 함수를 호출 후, 1) 사용자가 노드를 선택하면 ShowNode 함수 호출. 2) 제대로 선택하지 않으면 (NULL을 리턴 받아서) 메인 메뉴로 돌아감.
						
			stNode* p_temp_node = ShowGroup(group_name, &list_variables);
			if (p_temp_node == NULL){
				continue;
			}
			else {
				//ShowNode(p_temp_node);
				ShowNode(p_temp_node, &list_variables);
			}			
			
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


void AddNewNodeSample(stList* address_of_list_variables){                   // 3개 샘플 노드 강제 추가 함수.

	address_of_list_variables->pHead = (stNode*)malloc(sizeof(stNode));		// list_variables 구조체의 멤버인 pHead(주소)가 가리키게 한다.			// 1번째 노드의 영역을 생성해 주고, 전역변수인 p_head(주소)가 가리키게 한다.
	address_of_list_variables->pHead->id = 10001;
	address_of_list_variables->pHead->index = 1;	
	strcpy(address_of_list_variables->pHead->name, "KIM CheolMin");
	strcpy(address_of_list_variables->pHead->number, "010-5324-2342");
	strcpy(address_of_list_variables->pHead->group, "TEAM");
	address_of_list_variables->pHead->matchedValue = 0;
	address_of_list_variables->pHead->favorite = 0;
	address_of_list_variables->pHead->pPrev = NULL;
	address_of_list_variables->pHead->pNext = NULL;
	//list_variables.pHead->pPrev = NULL; 
	//list_variables.pHead->pNext = NULL;
	
	
	stNode* node_sample_2 = (stNode*)malloc(sizeof(stNode));		// 2번째 노드의 영역을 생성해 주고, node_sample_2(주소)가 가리키게 함.
	node_sample_2->id = 10002;
	node_sample_2->index = 2;	
	strcpy(node_sample_2->name, "NAM HyeMin");
	strcpy(node_sample_2->number, "010-3333-2222");
	strcpy(node_sample_2->group, "SECURITY");
	node_sample_2->matchedValue = 0;
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
	address_of_list_variables->pTail->matchedValue = 0;
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


// 다른 사람들이 작성한 c 파일과 함께 컴파일할 때는 아래 중 해당 함수를 주석처리해야 함.


stNode* Search(stList* address_of_list_variables){                                                           // 테스트용.
    // return address_of_list_variables->pHead;
	return address_of_list_variables->pHead;
}


/*
void ShowNode(stNode* address_of_Node){                                    // 테스트용.
    printf("%d      %d      %s      %s      %s      %d      %d\n", 
    address_of_Node->id, 
    address_of_Node->index,
    address_of_Node->name, 
    address_of_Node->number, 
    address_of_Node->group, 
    address_of_Node->matchedValue, 
    address_of_Node->favorite 
    );
}
*/

/* 
stNode* ShowList(stList* address_of_list_variables){                                                        // 테스트용.
    return address_of_list_variables->pHead->pNext;
}
*/

/*
stNode* ShowGroup(char* group_name, stList* address_of_list_variables){                                                        // 테스트용.
    return address_of_list_variables->pHead->pNext->pNext
	
	;
}
*/


void ImportExport(){                                                       // 테스트용.
	printf("ImportExport();\n");
}

void ChangeOrder(){                                                         // 테스트용.
	printf("ChangeOrder();\n");
}

void getData(stList* pList, char* filename){
    FILE* fp;
    char buffer[256];
    
    if((fp = fopen(filename,"r")) == NULL){
        printf("Cannot open the file\n");
    } // 파일을 열지 못하면 에러 메시지를 띄운다.
        
    while(fgets(buffer,256,fp) != NULL){   // 데이터의 한줄을 읽고 buffer에 저장한다.
        stNode* newNode = getNode(buffer); // 데이터의 한줄을 getNode 함수에 전달하고, getNode 함수에서 파싱해서 새로운 stNode를 생성한다.
        AddtoTailNode(pList, newNode); // 생성된 stNode를 pList Tail에 연결한다.
    }
}

stNode* getNode(char* stringValue){
    int tmpCount = 0; // 파싱되는 순서대로 stNode의 각 필드에 저장하기 위해 파싱 순서를 저장하는 변수
    char* temp; // 파싱되는 문자 데이터 저장 변수
    stNode* newNode = (stNode*) malloc(sizeof(stNode)); // 임의의 stNode 1개를 메모리 할당 받는다.
    newNode->pNext = NULL; // 할당받은 stNode의 pNext를 초기화 한다.
    newNode->pPrev = NULL; // 할당받은 stNode의 pNext를 초기화 한다.
    newNode->matchedValue = 0;
        
    temp = strtok(stringValue,","); // 입력받은 데이터 한줄을 ','를 기준으로 파싱한다.

    if(tmpCount == 0){
        newNode->id = atoi(temp); 
    } // 첫번째 파싱 값은 id에 입력한다.
    while(temp != NULL){
        tmpCount++;
        temp = strtok(NULL,","); // 파싱할 값이 없을 때까지 연속해서 파싱
        if(tmpCount == 1){
            newNode->index = atoi(temp); // 두번째 파싱 값은 index에 저장한다.
        }
        else if(tmpCount == 2){
            strcpy(newNode->name,temp); // 세번째 파싱 값은 name에 저장한다.
        }
        else if(tmpCount == 3){
            strcpy(newNode->number,temp); // 네번째 파싱 값은 number에 저장한다.
        }
        else if(tmpCount == 4){
            strcpy(newNode->group,temp); // 다섯번째 파싱 값은 group에 저장한다.
        }
        else if(tmpCount == 5){
        //    newNode->search_hit = atoi(temp); // 여섯번째 파싱 값은 검색 플래그에 저장한다.
		    newNode->matchedValue = atoi(temp); // 여섯번째 파싱 값은 검색 플래그에 저장한다. search_hit → matchedValue
        }
        else if(tmpCount == 6){
            newNode->favorite = atoi(temp); // 일곱번째 파싱 값은 즐겨찾기에 저장한다.
        }
        else{
            //newNode->matchedValue = 0;
            continue;
        }
    }
    return newNode; // 파싱된 stNode 1개를 리턴한다.
}


void InitializeList1(stList* pList) {
    //stList* list;
    pList->pHead = pList->pTail = NULL;
    pList->sort_needs = 1;
    pList->sort_order = 0;
    pList->count_node = 0;
}