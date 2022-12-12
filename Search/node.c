#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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