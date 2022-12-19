#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

int main(int argc, char *argv[]){
    while(1){
        char* fileName;
        char* matchedWith;
        node* dataHead = NULL;
        node* stData = NULL;
        node* searchedNode = NULL;    
        
        if(argc < 2){
            fileName = "data.csv";
        }
        else if(argc > 3){
            printf("Usage Error\n" );
        }
        else{
            fileName = argv[1];
        }

        dataHead = getData(fileName);   
        stData = dataHead;
    
        searchedNode = searchDisplay(dataHead);

        if(searchedNode != NULL){
                printf("Searched data\n");
                printf("Index\tID\tName\tNumber\t\tGroup\n");
                printf("%d\t%d\t%s\t%s\t%s",searchedNode->index,searchedNode->id,searchedNode->name,searchedNode->number,searchedNode->group);
                printf("\t->  matched with...%d ",searchedNode->matchedValue);
                matchedWith = " ";
                switch (searchedNode->matchedValue)
                {
                case 1 :
                    matchedWith = "Index";
                    break;
                case 2 :
                    matchedWith = "ID";
                    break;
                case 3 :
                    matchedWith = "Name";
                    break;
                case 4 :
                    matchedWith = "Number";
                    break;
                case 5 :
                    matchedWith = "Group";
                    break;

                default:
                    break;
                }
                printf("%s\n",matchedWith);
                break;
        }
        else{
                printf("\nNo matched data\n");
                printf("Try again\n");
        }
    }
}
    /*
    while (stData != NULL)
    {
            printf("%d %d %s %s %s %d %d\n",stData->id,stData->index,stData->name,stData->number,stData->group,stData->search_hit,stData->favorite);
            stData = stData->Next;
    }

                dataHead = NULL;
                stData = NULL;
                searchedNode = NULL;
                dataHead = getData(fileName);   
                stData = dataHead;
                searchedNode = searchDisplay(dataHead);
    */