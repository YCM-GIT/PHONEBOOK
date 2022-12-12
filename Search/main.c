#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

node* getData(char*);

int main(int argc, char *argv[]){

    char* fileName;
     
    if(argc < 2){
        fileName = "data.csv";
    }
    else if(argc > 3){
        printf("Usage Error\n" );
    }
    else{
        fileName = argv[1];
    }
    
   node* stData = getData(fileName);   

   while (stData != NULL)
   {
        printf("%d %d %s %s %s %d %d\n",stData->id,stData->index,stData->name,stData->number,stData->group,stData->search_hit,stData->favorite);
        stData = stData->Next;
   }
}