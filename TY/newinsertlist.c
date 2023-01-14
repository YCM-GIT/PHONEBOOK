#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "double_linked_list.h"
#include "phonebook.h"


//함수선언 : ID 빈자리 찾기, 새로운 노드에 인댁스 추가 하기
extern void AddNewNode(stList* pList);
int searchVacantIDadd(stList* pList);
int addedIndex(stList* pList);



extern void AddNewNode(stList* pList) {
	char sName[NAME_LENGTH];
	char sPhoneNumber[NUMBER_LENGTH];
	char sGroup[GROUP_LENGTH]; //헤더에서 정의된 값을 사용
	stNode* newData = malloc(sizeof(stNode)); //변수 형으로 생성생성되는 데이터는 1개 이므로 노드변수 하나만 생성
	char favorite;
	
	printf("** Welcome Phonebook input form           **\n");
	printf("** please press the enter key after input **\n");
	printf("Name : ");
	scanf(" %[^\n]s", sName);
	printf("Phone numbers : ");
	scanf(" %[^\n]s", sPhoneNumber);
	printf("Group : ");
	scanf(" %[^\n]s", sGroup);
	
	printf("Is favorite? : (y/n) :");
	favorite = getchar();
	
	while(1) { //즐겨찾기 입력 y 또는 n 입력을 받고 그 외의 문자는 루프에서 돈다. 
		//scanf("%c",&favorite);
		favorite = getchar();
		if(favorite == 'y') {
			newData->favorite = 1;
			break;
		}else if (favorite == 'n') {
			newData->favorite = 0;
			break;
		}else {
			printf("Please input 'y' or 'n'\n");
			printf("Is favorite? : (y/n) :");
			continue;
		}
	}
	
	
	strcpy(newData->name, sName);
	strcpy(newData->number, sPhoneNumber);
	strcpy(newData->group, sGroup); // 새로운 데이터 노드에 입력된 값을 추가
	
	
	newData->id = searchVacantIDadd(pList); //id 빈자리 찾아서 전 노드 id+1 추가하기
	newData->index = addedIndex(pList); //index 마지막 번호+1 
	
	AddtoTailNode(pList, newData);  // 새로운 데이터가 들어간 구조체 노드를 tail에 노드 추가, double_linked_list에 정의됨.
	pList->sort_order = 1; //다시 소팅하는 플래그 넣기
	
}

int searchVacantIDadd(stList* pList) {
	int newID = 0;
	//int cnt = 0 ;
	int i = 0;
	int chkID[10000] = {0,}; //0으로 초기화
	stNode* cur;

    for (cur = pList->pHead; cur !=NULL ; cur=cur->pNext) { //배열에 현재 ID를 담는다.
        chkID[cur->id % 10000] = cur->id; //ID 구조가 10001의 숫자의 구조이므로 10000으로 나눈 나머지를 배열 인덱스로 활용
	//	printf("%d\n",chkID[cur->id % 10000]);
	} 
	
	for(i = 1; i < 10000 ; i++) { //배열의 시작을 1부터 했기 때문에 1부터 시작한다. 
		
	
		if(chkID[i] == 0) { // 1부터 카운트 해서 비어있는 칸의 첫번째 칸을 찾는다. 모두 차있다면 
			newID = i + 10000; //ID의 구조는 1xxxx이므로 저장된 배열에 인덱스 값을 넣으면 ID완성
			return newID;
		}
	}
	
}



int addedIndex(stList* pList) {
	int newIndex;
	
	//현재 리스트에서 tail 노드의 다음 숫자를 새로운 인덱스로 지정함
	newIndex = pList->pTail->index + 1;

	return newIndex;
}