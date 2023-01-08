#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "double_linked_list.h"
#include "phonebook.h"

extern stNode* ShowGroup(char* group_name, stList* pList)
{
	//그룹별 보여주기를 위한 list 생성 (initializelist 변형)
	stList* group_list = malloc(sizeof(stList));
	group_list->pHead = pList->pTail = NULL; // 첫,끝 노드 null로 설정
	group_list->sort_needs = 1;
	group_list->sort_order = 2;
	group_list->count_node = 0; // 현재 노트 수 : 0

	//pList 를 지나가면서 같은 group name이 있을때 group list에 추가
	stNode* curr_node;
	for (curr_node = pList->pHead; curr_node->pNext != NULL; curr_node = curr_node->pNext)
	{
		if (strcmp(group_name, curr_node->group) == 0) //지나가면서 group명이 같다면
		{
			//group_list에 추가해주기 
			AddtoTailNode(group_list, curr_node); //List의 뒤에 신규 노드 추가 
		}
	}

	//추가한 list를 정렬해주기(이름순으로)
	SortList(group_list);

	// 이름으로 정렬된 group_list를 리턴하기
	//showNode(group_list->pHead);
	return group_list->pHead;
}
