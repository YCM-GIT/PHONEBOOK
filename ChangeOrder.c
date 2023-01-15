#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "double_linked_list.h"
#include "phonebook.h"

extern void ChangeOrder(stList* pList){                                                         // 테스트용.
	int command;
	printf("-------- sort by --------\n1. number\n2. group\n3(or else). name\n-------------------------\n\n");
	printf("Input your command number: ");
		scanf("%d", &command);
	//printf("your choice: %d\n", command);
	
	switch (command) {
                case 1: printf("your choice is: by number\n");
						break;
                case 2: printf("your choice is: by group\n");
						break;
                default: printf("your choice is: by name\n");
						break;
            }
	pList->sort_order = command;
}
