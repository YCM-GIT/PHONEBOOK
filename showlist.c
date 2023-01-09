#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "double_linked_list.h"
#include "phonebook.h"

extern stNode* ShowList(stList* pList);
extern int SortList(stList* pList);
int SortPhonebook(stList* pList);
int SortFavorite(stList* pList);
void Renumbering(stList* pList);


extern stNode* ShowList(stList* pList) {
    // 변수 선언
    stNode* selected_node, *cur;
    int i, user_choice=0, limit_ask=3; 
    char user_choice_char;
    if(IsEmpty(pList)==1) {   // list가 NULL 이면 NULL 리턴
        printf("This list is empty.\n");
        return NULL;  
    }     
    CountNode(pList);
    if (pList->sort_needs==1) {  //sort_needs=1 정렬이 필요하면 정렬시작        

        //정렬기준에 따른 정렬하는 함수 콜
        //printf("*** sort by name ***\n");
        SortList(pList);    // sort_order를 통해 정렬 기준을 바꿀 수 있어야 함. 지금은 디폴트 name 만 실행
        //PrintList(pList);     //        
    }
    // 현재의 리스트를 print하고
    PrintList(pList);    
    
    // 사용자가 index를 선택하도록 하는 기능 추가
    while(limit_ask > 0) {
        printf("\nWhich number would you like to select? (to main menu : 'q') : ");
        scanf("%c",&user_choice_char);
        user_choice = (int)user_choice_char - 48;
        if(user_choice_char=='q') {
            // printf("quit\n");
            return NULL;    // q를 입력받으면 NULL을 리턴함
        }        
        if(user_choice <= pList->count_node && user_choice > 0) {
            break;
        } else {
            printf("\nwrong number!\n");
            limit_ask--;
        }        
    }
    printf("\n");
    if (limit_ask <= 0) {
        return NULL; // 사용자가 index 선택을 2번 잘못했을 경우 NULL을 리턴
    }
    // 사용자가 선택한 index에 해당하는 노드의 주소값을 찾아서 리턴값 설정
    cur = pList->pHead;    
    for (i=1; i <= pList->count_node; i++) {        
        if(cur->index == user_choice) {
            selected_node = cur;
            break;
        }
        cur=cur->pNext;
    }    
    //printf("\nselected node is %s\n", selected_node->name);
    return selected_node;          

}
extern int SortList(stList* pList) {
    SortPhonebook(pList);        
    SortFavorite(pList);
    // 인덱스 다시 넘버링
    //printf("*** renumbering ***\n");              
    Renumbering(pList);
    return 0;
}

int SortPhonebook(stList* pList) {
// 버블정렬
    stNode* cur, *cur_next, *tmp1, *tmp2;    
    char *cur_sort, *cur_next_sort;
    int i,j;
    bool switching_position=false;
        
    CountNode(pList); // 노드의 개수를 세기
    
    if ((*pList).count_node <= 1 ) {
        printf("The number of nodes is not enough.\n");
        return -1;
    }

    for (i=0 ; i < (*pList).count_node + 1 ; i++) {    //버블 정렬 : 이전노드tmp와 현재노드cur를 비교하여 스위치or그대로
        cur = pList->pHead;
        for (j=1 ; j < (*pList).count_node - i ; j++) { 
            cur_next = cur->pNext; 

            switch (pList->sort_order) {
                case 1:     cur_sort = cur->number;
                            cur_next_sort = cur->pNext->number;
                            break;
                case 2:     cur_sort = cur->group;
                            cur_next_sort = cur->pNext->group;
                            break;
                default:    cur_sort = cur->name;     // 0은 name, 1은 전화번호, 2는 그룹, 3 이상은 name
                            cur_next_sort = cur->pNext->name;
                            break;
            }
               
            if(cur==pList->pHead) {  // 바로 이전 노드가 head일 때는 tmp의 이전노드가 NULL
                //printf("1111\n");  

                if (strcmp(cur_sort, cur_next_sort)==1) {  // 자리를 스위치     
                  
                    tmp2 = cur_next->pNext; //tmp2는 cur의 다음다음 노드를 의미함.  노드2개일때는 tmp2가 NULL
                                            // cur_next와 cur의 위치를 바꿈
                    cur->pNext = tmp2;  // cur의다음주소 기존 cur다음다음노드의 주소,
                    cur->pPrev = cur_next;    // cur의 이전주소는 기존 cur다음노드의 주소   

                    cur_next->pPrev = NULL;
                    cur_next->pNext = cur;
                    if(cur_next->pNext!=NULL) {  // tmp2가 NULL이 아닐 경우에만 실행
                        tmp2->pPrev = cur;   // 기존cur다음다음노드의 이전주소는 cur  
                    }
                    pList->pHead = cur_next;

                    switching_position=true;                    
                    //PrintList(pList);
                }                 
            } else if (cur_next==pList->pTail) {
                //printf("3333\n");
                if (strcmp(cur_sort, cur_next_sort)==1) {  // 자리를 스위치        

                    tmp1 = cur->pPrev;    //tmp는 cur의 이전노드를 의미함
                                          // cur_next와 cur의 위치를 바꿈
                    cur->pNext = NULL;  // cur의다음주소 기존 cur다음다음노드의 주소,
                    cur->pPrev = cur_next;    // cur의 이전주소는 기존 cur다음노드의 주소   

                    cur_next->pPrev = tmp1;
                    cur_next->pNext = cur;

                    tmp1->pNext = cur_next;  // 기존 cur 이전노드의 다음주소는 기존cur의 다음노드   
                    pList->pTail = cur;                                 

                    switching_position=true; 
                    //PrintList(pList);
                }                    
            } else {
                //printf("2222\n");
                if (strcmp(cur_sort, cur_next_sort)==1) {  // 자리를 스위치   
                    
                    tmp1 = cur->pPrev;    //tmp는 cur의 이전노드를 의미함
                    tmp2 = cur_next->pNext; //tmp2는 cur의 다음다음 노드를 의미함.
                                            // cur_next와 cur의 위치를 바꿈
                    cur->pNext = tmp2;  // cur의다음주소 기존 cur다음다음노드의 주소,
                    cur->pPrev = cur_next;    // cur의 이전주소는 기존 cur다음노드의 주소   

                    cur_next->pPrev = tmp1;
                    cur_next->pNext = cur;

                    tmp1->pNext = cur_next;  // 기존 cur 이전노드의 다음주소는 기존cur의 다음노드          
                    tmp2->pPrev = cur;   // 기존cur다음다음노드의 이전주소는 cur

                    switching_position=true;
                    //PrintList(pList);
                }              
            }
            if(cur == pList->pTail) {
                //printf("Tail\n");                
            } else if (switching_position==false) { // 자리가 바뀐 경우에는 cur가 뒷쪽으로 오므로 바꿀 필요가 없음         
                cur = cur->pNext;                   // 자리가 바뀌지 않으면 다음노드로 cur를 변경해서 반복문 실행     
            }
            switching_position=false;          
        }    
    }
    printf("\n");
}

int SortFavorite(stList* pList) {
//tail부터 검색해서 head에 삽입
    stNode* cur, *tmp;
    int count;
    cur = pList->pTail;
    CountNode(pList);
    if((*pList).count_node<2) {
        printf("The number of nodes is not enough.\n");
        return -1;
    }
//    printf("%d\n", (*pList).count_node);
    for (count=(*pList).count_node ; count > 0; count--) {
        // tail에서 거꾸로 주소타고 올라가야 하는데, cur->pPrev를 유지하기 위해 tmp이용
        tmp = cur->pPrev;   
        if(cur->favorite==1) {
           // cur의 앞과 뒤 노드를 연결 
            if(cur==pList->pTail) {
                pList->pTail = tmp;                
                tmp->pNext = NULL;       
            }    
            else {
                cur->pNext->pPrev = tmp;   
                tmp->pNext = cur->pNext;                         
            }
           // cur는 head에 삽입   (double linked list head 삽입 기능 사용)  
           AddtoHeadNode(pList, cur);                      
        }
        //PrintList(pList);
        cur = tmp;   
    }
    return 0;
}

void Renumbering(stList* pList) {
    int count=1;   //넘버링 시작은 1번부터
    stNode* cur;
    for (cur = pList->pHead; cur !=NULL ; cur=cur->pNext) {
        cur->index = count;
        count++;
    } 
}
