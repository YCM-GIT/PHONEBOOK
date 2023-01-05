#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "double_linked_list.h"
#include "phonebook.h"

int main(int argc, char *argv[]){
    stList list = {0};  
    list.sort_needs = 1;   // 디폴트는 정렬 필요로 설정
    InitializeList(&list);

    char* fileName;
    char* matchedWith;
    

    if(argc < 2){
        fileName = "phonebook_sample2.csv";
    } // 별도로 argument를 입력하지 않으면 data.csv 파일의 데이터를 읽어온다.
    else if(argc > 3){
        printf("Usage Error\n" );
    }
    else{
        fileName = argv[1];
    } // 별도로 argument가 있으면 argument 값에 해당되는 파일의 데이터를 읽어온다.
    
    //stNode* searchedNode = (stNode*) malloc(sizeof(stNode));
    stNode* searchedNode;
    getData(&list, fileName); // 파일명을 전달하면 파일의 값을 읽어 데이터를 stNode로 만들고 stList로 연결한다.

    while(1){
        
        printf("\n=======================================\n");
        printf("              [Phone Book]             \n");
        printf("=======================================\n\n");
        printf("Index\t ID\t\t  Name\t\t       Number\t\t      Group\n");
        PrintList(&list);
        
        searchedNode = searchDisplay(&list); //현재 데이터 리스트를 전달하면 찾고자 하는 데이터의 stNode값을 리턴한다.
           
        if(&searchedNode != NULL){
                printf("Searched data...\n");
                printf("Index\t ID\t\t   Name\t\t\t   Number\t\t     Group\n");
                printf("%3d\t%5d\t%20s\t%20s\t%20s\t ",searchedNode->index,searchedNode->id,searchedNode->name,searchedNode->number,searchedNode->group);
                printf("\t-> matched with...");
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
                printf("%s\n\n",matchedWith);
                break;
        } // 찾는 값과 stNode값에서 어떤 필드에서 찾았는지 표시해 준다.
        else{
                printf("\nNo matched data\n");
                printf("Try again\n\n");
        }
    }
}