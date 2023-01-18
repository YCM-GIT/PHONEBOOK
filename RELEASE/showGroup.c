#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "double_linked_list.h"
#include "phonebook.h"

extern stNode* ShowGroup(char* group_name, stList* pList)
{
	//그룹별 보여주기를 위한 list 생성 (initializelist 변형)
	stList* group_list = (stList*) malloc(sizeof(stList));
	group_list->pHead = pList->pTail = NULL; // 첫,끝 노드 null로 설정
	group_list->sort_needs = 1;
	group_list->sort_order = 2;
	group_list->count_node = 0; // 현재 노트 수 : 0
	int selectedIndex;
	stNode* selectedNode;
	stNode* curr_node = NULL;
		
	for (curr_node = pList->pHead; curr_node != NULL; curr_node = curr_node->pNext)
	{
		if (strcmp(group_name, curr_node->group) == 0) //지나가면서 group명이 같다면
		{
			//group_list에 추가해주기 
			stNode* temp = malloc(sizeof(stNode));
			temp->id = curr_node->id;
			temp->index = curr_node->index;
			strcpy(temp->name, curr_node->name);
			strcpy(temp->number, curr_node->number);
			strcpy(temp->group, curr_node->group);
			temp->favorite = curr_node->favorite;
			AddtoTailNode(group_list, temp); //List의 뒤에 신규 노드 추가 
		}
	}
	//추가한 list를 정렬해주기(이름순으로)
	//SortList(group_list);
    PrintList(group_list); 
	
	curr_node = group_list->pHead;
	printf("\nSelect index...."); // 검색 결과 리스트 중 1개의 index값을 입력 받음
	printf("\n(If you want to come back Main Menu, Input '0')....");
	scanf("%d",&selectedIndex);

	while(curr_node != NULL)
	{
		if(selectedIndex == 0){
			selectedNode = NULL;
			break;
		}
		else{
			if(selectedIndex == curr_node->index){
				selectedNode = curr_node;
				break;
			}    
		}
		curr_node = curr_node->pNext;

	}
	
    return selectedNode; 
}