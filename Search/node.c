#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "node.h"

node* getNode(char* s){
    int tmpCount = 0;
    node* newNode = (node*) malloc(sizeof(node));
    newNode->Next = NULL;
    newNode->Prev = NULL;
    char* temp;
    
    temp = strtok(s,",");

    if(tmpCount == 0){
        newNode->id = atoi(temp);
    }      
    while(temp != NULL){
        tmpCount++;
        temp = strtok(NULL,",");
        if(tmpCount == 1){
            newNode->index = atoi(temp);
        }
        else if(tmpCount == 2){
            strcpy(newNode->name,temp);
        }
        else if(tmpCount == 3){
            strcpy(newNode->number,temp);
        }
        else if(tmpCount == 4){
            strcpy(newNode->group,temp);
        }
        else if(tmpCount == 5){
            newNode->search_hit = atoi(temp);
        }
        else if(tmpCount == 6){
            newNode->favorite = atoi(temp);
        }
        else{
            newNode->matchedValue = 0;
            continue;
        }
    }
    return newNode;
}

node* getData(char* filename){
    FILE* fp;
    char buffer[256];
    node* Head = NULL;
    node* Tail = NULL;
    node* Current = NULL;
    
    if((fp = fopen(filename,"r")) == NULL){
        printf("Cannot open the file\n");
    }
        
    while(fgets(buffer,256,fp) != NULL){
        
        node* newNode = getNode(buffer);
        
        if(Head == NULL){
            Head = newNode;
            Current = Head;
        }
        else{
            if(Current->Next != NULL){
                Current = Current->Next;
            }
            Current->Next = newNode;
            newNode->Prev = Current;
        }
    }
    return Head;
}

node* searchDisplay(node* data){
    
    char searchingValue[256];
    
    printf("\n=======================================\n");
    printf("              [Phone Book]             \n");
    printf("=======================================\n\n");
    printf("               Searching               \n\n");
    printf("Input any values to search....");
    scanf("%s",searchingValue);

    searchedList* sList = NULL; 
    searchedList* cList = NULL;
    node* selectedNode = NULL;
    char* selectedIndex;

    sList = SearchingValue(data, searchingValue);
    cList = sList;

    if(cList != NULL){
        printf("\nIndex\tID\tName\tNumber\t\tGroup\n");
    }
    
//    else{
//        printf("\nNo Mached Value\n");
//    }

    while(cList != NULL){
        node* tmp = cList->node;
        printf("%d\t%d\t%s\t%s\t%s\t%d\n",tmp->index,tmp->id,tmp->name,tmp->number,tmp->group,cList->matchedWith);
        cList = cList->NextNode;
    }

    cList = sList;

    if(cList != NULL){
        printf("\nSelect index that you searched....");
        scanf("%s",selectedIndex);
        while(cList != NULL){
            if(atoi(selectedIndex) == (cList->node)->index){
                //printf("Searched Success\n");
                selectedNode = (cList->node);
                selectedNode->matchedValue = cList->matchedWith;
                printf("Matched Value %d \n",selectedNode->matchedValue);
                break;
            }
            cList = cList->NextNode;
        }
    }

//    else{
//        printf("searched Fail\n");
//    }

//    if(selectedNode != NULL){
//        printf("%d\t%d\t%s\t%s\t%s\t%d\n",selectedNode->id,selectedNode->index,selectedNode->name,selectedNode->number,selectedNode->group,cList->matchedWith);
//        //printf("%p\n",selectedNode);
//    }  
    return selectedNode;
}

searchedList* SearchingValue(node* dataNode, char* searchingValue){
    
    int searchedFlag = 0;
    node* currentNode = dataNode;
        
    searchedList* HeadList = NULL;
    searchedList* tmpList = NULL;
    searchedList* CurrentList = NULL;

    while(currentNode !=NULL){
        if(currentNode->index == atoi(searchingValue)){
            if(searchedFlag==0){
                searchedFlag = 1;
            }            
            currentNode->search_hit = 1;
        }
        else if (currentNode->id == atoi(searchingValue)){
            if(searchedFlag==0){
                searchedFlag = 2;
            }
            currentNode->search_hit = 1;
        }
        else if (stringFind(currentNode->name, searchingValue) >= 0){
            if(searchedFlag==0){
                searchedFlag = 3;
            }
            currentNode->search_hit = 1;
        }
        else if (stringFind(currentNode->number, searchingValue) >= 0){
            if(searchedFlag==0){
                searchedFlag = 4;
            }
            currentNode->search_hit = 1;
        }
        else if (stringFind(currentNode->group,searchingValue) >= 0){
            if(searchedFlag==0){
                searchedFlag = 5;
            }
            currentNode->search_hit = 1;
        }
        else{
            searchedFlag = 0;
            currentNode->search_hit = 0;
        } 
    
        if(searchedFlag > 0){
            searchedList* newList = NULL;         
            newList = (searchedList*) malloc(sizeof(searchedList)); 
            newList->NextNode = NULL;
            newList->PrevNode = NULL;
            newList->node = NULL;
           
            if(HeadList == NULL){
                HeadList = newList;
                CurrentList = HeadList; 
                CurrentList->node = currentNode;
                CurrentList->matchedWith = searchedFlag;
                (CurrentList->node)->matchedValue = searchedFlag;
               // searchedFlag = 0;
            }
            else{
                if(CurrentList->NextNode != NULL){
                    CurrentList = CurrentList->NextNode;
                }
                CurrentList->NextNode = newList;
                newList->PrevNode = CurrentList;
                newList->node = currentNode;
                newList->matchedWith = searchedFlag;
            }
        }
        searchedFlag = 0;
        currentNode = currentNode->Next;
    }
    return HeadList;
}

int stringFind(char* a, char* b){
    int i;
    bool ok;
    int returnValue;

    for(i=0 ; a[i] != '\0' && !ok ; i++){
        ok = true;
        for(int j=0 ; b[j] != '\0' && ok ; j++){
            if(a[i+j] != b[j]) ok = false;
        }
    }
    return ok ? i-1 : -1;
}