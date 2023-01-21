// 230115 현재 통합 빌드 명령어: gcc main.c showlist.c double_linked_list.c newinsertlist.c searchDisplay.c showNode.c showGroup.c Import_Export.c ChangeOrder.c -o main.exe

// 변경이력
// 1. (221231) Node 구조체 변경 (Node → stNode)
// 2. AddNewNodeSample, Search, ShowList, ShowGroup 함수를 매개변수를 받도록 변경: 예: AddNewNodeSample() → AddNewNodeSample(stList* address_of_list_variables)
// 3. 구조체 안에 문자열을 대입하기 위해, strcpy 함수 사용. 이를 위해 #include<string.h> 필요
// 4. #include "double_linked_list.h", #include "phonebook.h" 추가.
// 5. (230108) Search, ShowList, ShowGroup 함수에서 NULL값 리턴 시, main의 while문으로 복귀. (NULL값이 아니라면, ShowNode 함수 호출)
// 6. stSearchedList 구조체 선언. (double_linked_list.h 안에)
// 7. (220115) 필요 없는 주석 처리 삭제. 1) 개별 파일로 만든 함수들, 2) 테스트용 문구들.
// 8. 시작 전에 hard-coded sample을 추가할 것인지 묻지 않고, 메인 메뉴에 곧바로 진입. (import 기능 권장)
// 9. 설명 필요한 주석 추가.
// 10. (220121) 맨 마지막 else문에 버퍼 비워주는 getchar() while문 추가.
// 11. your choice 보여주는 것을 각 command if문 안으로 이동 (틀렸을 때는 안 보여주기 위해).

#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "double_linked_list.h"
#include "phonebook.h"

#define NAME_LENGTH 30
#define NUMBER_LENGTH 20
#define GROUP_LENGTH 20
//#define FILE_NAME "phonebook_sample2.csv"

// 본 파일의 main 함수 아래에 있는 함수 선언부. 개별 파일로 만들고 나면, 주석 처리 필요.

void InitializeList1(stList* pList);   // CEB 님이 수정 후, 그것으로 변경 예정.


void main(){                 // 필요한 초기화 후, while 루프 진입. 프로그램 동작 동안 계속 while문 안에 있음.

	stList list_variables;				// 변수들을 담는 구조체 선언. pHead, pTail, sort_needs, sort_order, count_node.
	InitializeList1(&list_variables);	// 변수들을 초기화. 
	
	int command;						// 메인 메뉴에서 사용자 입력을 숫자로 받기 위해 선언.
	while(1){                           // 메인 화면. 프로그램 동작 동안 계속 이 while 문 안에 있는 상태이다.
		printf("------- Main Menu -------\n1. add a new node\n2. search\n3. show list\n4. show group\n5. import/export\n6. change order\n-------------------------\n\n");
		printf("Input your command number: ");

		scanf("%d", &command);
		
		if (command == 1) {
			printf("your choice: %d\n", command);
			AddNewNode(&list_variables);								// 신규 노드 추가 함수 (JIJ)
			continue;
		}
		else if (command == 2){
			printf("your choice: %d\n", command);

			// searchDisplay 함수를 호출 후, 1) 사용자가 노드를 선택하면 ShowNode 함수 호출. 2) 제대로 선택하지 않으면 (NULL을 리턴 받아서) 메인 메뉴로 돌아감.
			stNode* p_temp_node = searchDisplay(&list_variables);		// 검색 함수 (YTY)
			if (p_temp_node == NULL){									// 이 함수가 NULL값을 리턴하면, while문(메인 메뉴)으로 복귀.
				continue;
			}
			else {														// 이 함수가 stNode 주소값을 리턴하면, ShowNode 함수 호출.
				ShowNode(p_temp_node, &list_variables);
			}

			continue;
		}
		else if (command == 3){
			printf("your choice: %d\n", command);

			// ShowList 함수를 호출 후, 1) 사용자가 노드를 선택하면 ShowNode 함수 호출. 2) 제대로 선택하지 않으면 (NULL을 리턴 받아서) 메인 메뉴로 돌아감.
			stNode* p_temp_node = ShowList(&list_variables);      		// List 보여주는 함수 (CEB)
			if (p_temp_node == NULL){									// 이 함수가 NULL값을 리턴하면, while문(메인 메뉴)으로 복귀.
				continue;
			}
			else {														// 이 함수가 stNode 주소값을 리턴하면, ShowNode 함수 호출.
				ShowNode(p_temp_node, &list_variables);
			}
			
			continue;
		}
		else if (command == 4){
			printf("your choice: %d\n", command);

			// 어느 그룹을 보여줄 것인지 묻고, 문자열을 ShowGroup에 넘겨주는 기능 시작.			
			printf("------- Group list -------\n");
			printf("DOMAIN\nSECURITY\nTEAM\nVEHICLE\n");
			printf("--------------------------\n");
			printf("Type Group name correctly: ");
			char group_name[GROUP_LENGTH];
			scanf("%s", group_name);
			printf("%s\n", group_name);
			// 어느 그룹을 보여줄 것인지 묻고, 문자열을 ShowGroup에 넘겨주는 기능 완료.


			// ShowGroup 함수를 호출 후, 1) 사용자가 노드를 선택하면 ShowNode 함수 호출. 2) 제대로 선택하지 않으면 (NULL을 리턴 받아서) 메인 메뉴로 돌아감.
			stNode* p_temp_node = ShowGroup(group_name, &list_variables);	// Group 보여주는 함수 (JSY)
			if (p_temp_node == NULL){										// 이 함수가 NULL값을 리턴하면, while문(메인 메뉴)으로 복귀.
				continue;
			}
			else {															// 이 함수가 stNode 주소값을 리턴하면, ShowNode 함수 호출.
				ShowNode(p_temp_node, &list_variables);
			}			
			
			continue;		
		}
        else if (command == 5){   
			printf("your choice: %d\n", command);
			Import_Export(&list_variables);                       					// import, export 함수 (NHM)
			continue;		
		}
        else if (command == 6){
			printf("your choice: %d\n", command);
			ChangeOrder(&list_variables);		                         					 // 정렬 기준 바꾸기.											
			continue;		
		}
		
		else {																// (메인 메뉴 리스트의 숫자인 1~6이 아닌) 다른 문자를 입력했을 경우에는, while문(메인 메뉴)으로 복귀. 
			while(getchar()!='\n'){											// command를 정상적으로 입력하지 않았다면(문자 입력 포함), 입력값을 비워줌. 이게 없으면 문자 입력 시 무한루프 돎.

			}
			printf("Wrong command. Type again.\n");
			continue;														
		}
	}

}


// 아래는 개별 파일로 만들고 나면, 주석 처리 필요.

void InitializeList1(stList* pList) {
    //stList* list;
    pList->pHead = pList->pTail = NULL;
    pList->sort_needs = 1;
    pList->sort_order = 0;
    pList->count_node = 0;
}