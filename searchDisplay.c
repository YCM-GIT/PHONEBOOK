#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "double_linked_list.h"
#include "phonebook.h"

/* csv 파일명을 입력 받아서 파일의 값들을 stNode로 만들고 stNode를 stList로 연결한다. */
void getData(stList* pList, char* filename){
    FILE* fp;
    char buffer[256];
    
    if((fp = fopen(filename,"r")) == NULL){
        printf("Cannot open the file\n");
    } // 파일을 열지 못하면 에러 메시지를 띄운다.
        
    while(fgets(buffer,256,fp) != NULL){   // 데이터의 한줄을 읽고 buffer에 저장한다.
        stNode* newNode = getNode(buffer); // 데이터의 한줄을 getNode 함수에 전달하고, getNode 함수에서 파싱해서 새로운 stNode를 생성한다.
        AddtoTailNode(pList, newNode); // 생성된 stNode를 pList Tail에 연결한다.
    }
}

/* 데이터 한줄을 입력 받아서 파싱을 하고 stNode의 각 필드 값에 저장하고 해당 stNode를 리턴한다.*/
stNode* getNode(char* stringValue){
    int tmpCount = 0; // 파싱되는 순서대로 stNode의 각 필드에 저장하기 위해 파싱 순서를 저장하는 변수
    char* temp; // 파싱되는 문자 데이터 저장 변수
    stNode* newNode = (stNode*) malloc(sizeof(stNode)); // 임의의 stNode 1개를 메모리 할당 받는다.
    newNode->pNext = NULL; // 할당받은 stNode의 pNext를 초기화 한다.
    newNode->pPrev = NULL; // 할당받은 stNode의 pNext를 초기화 한다.
    newNode->matchedValue = 0;
        
    temp = strtok(stringValue,","); // 입력받은 데이터 한줄을 ','를 기준으로 파싱한다.

    if(tmpCount == 0){
        newNode->id = atoi(temp); 
    } // 첫번째 파싱 값은 id에 입력한다.
    while(temp != NULL){
        tmpCount++;
        temp = strtok(NULL,","); // 파싱할 값이 없을 때까지 연속해서 파싱
        if(tmpCount == 1){
            newNode->index = atoi(temp); // 두번째 파싱 값은 index에 저장한다.
        }
        else if(tmpCount == 2){
            strcpy(newNode->name,temp); // 세번째 파싱 값은 name에 저장한다.
        }
        else if(tmpCount == 3){
            strcpy(newNode->number,temp); // 네번째 파싱 값은 number에 저장한다.
        }
        else if(tmpCount == 4){
            strcpy(newNode->group,temp); // 다섯번째 파싱 값은 group에 저장한다.
        }
        else if(tmpCount == 5){
            newNode->search_hit = atoi(temp); // 여섯번째 파싱 값은 검색 플래그에 저장한다.
        }
        else if(tmpCount == 6){
            newNode->favorite = atoi(temp); // 일곱번째 파싱 값은 즐겨찾기에 저장한다.
        }
        else{
            //newNode->matchedValue = 0;
            continue;
        }
    }
    return newNode; // 파싱된 stNode 1개를 리턴한다.
}

/* 검색 화면으로 이동해서 검색한 1개의 stNode값을 리턴한다. */
extern stNode* searchDisplay(stList* datalist){
    
    char searchingValue[256]; // 검색할 값을 저장할 변수
    
    printf("\n\n               Searching               \n\n");
    printf("Input any values to search");
    printf("\n(If you want to come back Main Menu, Input <!q>)....");
    scanf("%s",searchingValue); // 검색할 값을 입력 받는다.

    stSearchedList* sList = NULL; // 검색 결과 stNode를 연결한 리스트의 Head 값 초기화
    stSearchedList* cList = NULL; // 검색 결과를 탐색하기 위해 사용할 현재 검색 결과 리스트를 가르키는 값 초기화
    stNode* selectedNode = NULL; // 최종 선택된 stNode 값 초기화
    //stNode* selectedNode = (stNode*) malloc(sizeof(stNode));
    int selectedIndex; // 어떤 필드값과 매칭되었는지를 저장하는 변수

    if(strcmp(searchingValue,"!q") == 0){
        selectedNode = NULL;
        return selectedNode;
    }

    sList = SearchingValue(0, datalist, searchingValue); //datalist 중 검색값과 매칭되는 stNode들의 리스트를 리턴 받음
    cList = sList; // 검색 결과를 탐색하기 위해 현재 리스트에 검색 결과 리스트의 Head 값으로 설정

    if(cList != NULL){
        printf("\nIndex\t ID\t\t   Name\t\t\t   Number\t\t     Group\n");
    }
    else{
        printf("\nNo Mached Value\n");
    }
    while(cList != NULL){
        stNode* tmp = cList->node;
        printf("%3d\t%5d\t%20s\t%20s\t%20s\t%3d\n",tmp->index,tmp->id,tmp->name,tmp->number,tmp->group,cList->matchedWith);
        cList = cList->NextNode;
    } // 검색된 결과 값들을 표시

    cList = sList; // 검색 결과를 탐색하기 위해 현재 리스트에 검색 결과 리스트의 Head 값으로 설정

    if(cList != NULL){
        printf("\nSelect index that you searched...."); // 검색 결과 리스트 중 1개의 index값을 입력 받음
        printf("\n(If you want to come back Main Menu, Input '0')....");
        scanf("%d",&selectedIndex);
        if(selectedIndex == 0){
            selectedNode = NULL;
            return selectedNode;
        }
        else{
            while(cList != NULL){
                if(selectedIndex == (cList->node)->index){
                    printf("Searched Success\n\n");
                    selectedNode = (cList->node); // 입력 값이 검색 결과 중 index 값과 매칭되면 최종 검색 결과 stNode에 주소값 저장
                    selectedNode->matchedValue = cList->matchedWith; // 어떤 필드값에서 매칭이 되었는지 stNode의 매칭된 필드 값을 저장
                    break;
                }
                cList = cList->NextNode;
            }    
        }        
    }
    else{
        selectedNode = NULL;
        printf("Searched Fail\n\n"); // 입력 값이 검색 결과 중 index값과 매칭이 안될 시 
    }

    return selectedNode; // 최종 선택된 stNode 값을 리턴
}

/* 데이터 리스트 중 검색 값을 입력하면 해당되는 stNode들의 리스트를 리턴*/
/* mode 값이 1이면 index 필드에서만 검색 */
/* mode 값이 2이면 id 필드에서만 검색 */
/* mode 값이 3이면 name 필드에서만 검색 */
/* mode 값이 4이면 number 필드에서만 검색 */
/* mode 값이 5이면 group 필드에서만 검색 */
/* mode 값이 위에 해당되는 값이 아니면 전체 필드에서 검색 */
stSearchedList* SearchingValue(int mode, stList* dataList, char* searchingValue){
    
    int searchedFlag = 0;
    
    stNode* currentNode; // 현재 stNode의 주소값 저장위한 변수
    stSearchedList* HeadList = NULL; // 검색 결과 stNode들만 연결할 리스트의 Head 변수
    stSearchedList* CurrentList = NULL; // 검색 결과 리스트의 현재 가르키는 리스트 변수

    /* mode 1, 2, 3, 4, 5의 설명은 else문 전체 필드 검색에서 참조 바람 */
    if(mode == 1){
         for (currentNode = dataList->pHead; currentNode !=NULL ; currentNode = currentNode->pNext){
            if(currentNode->index == atoi(searchingValue)){
                if(searchedFlag == 0){
                    searchedFlag = 1;
                }            
            }
            if(searchedFlag > 0){ // 검색 값이 어느 필드의 값과 매칭이 되었다면...
                stSearchedList* newList = (stSearchedList*) malloc(sizeof(stSearchedList)); //검색 결과 임의의 리스트의 메모리 할당
                newList->NextNode = NULL; // 초기화
                newList->PrevNode = NULL; // 초기화
                newList->node = NULL; // 초기화
                newList->matchedWith = 0; //초기화
                    
                if(HeadList == NULL){ // Head 값이 없다면
                    HeadList = newList; // 새로운 리스트를 헤드값으로 
                    CurrentList = HeadList; 
                    CurrentList->node = currentNode; // 검색된 stNode의 주소값을 저장
                    CurrentList->matchedWith = searchedFlag; // 어떤 검색 필드와 매칭이 되었는지 저장
                    searchedFlag = 0; // 검색 필드 값 리셋
                }
                else{ // 검색 결과 리스트를 연결
                    if(CurrentList->NextNode != NULL){
                        CurrentList = CurrentList->NextNode;
                    }
                    CurrentList->NextNode = newList;
                    newList->PrevNode = CurrentList;
                    newList->node = currentNode; // 검색된 stNode의 주소값을 저장
                    newList->matchedWith = searchedFlag; // 어떤 검색 필드와 매칭이 되었는지 저장
                    searchedFlag = 0; // 검색 필드 값 리셋
                }
            }
            searchedFlag = 0;
         }
    }
    else if(mode == 2){
        for (currentNode = dataList->pHead; currentNode !=NULL ; currentNode = currentNode->pNext){
            if (currentNode->id == atoi(searchingValue)){
                if(searchedFlag == 0){
                    searchedFlag = 2;
                }
            }
            if(searchedFlag > 0){ // 검색 값이 어느 필드의 값과 매칭이 되었다면...
                stSearchedList* newList = (stSearchedList*) malloc(sizeof(stSearchedList)); //검색 결과 임의의 리스트의 메모리 할당
                newList->NextNode = NULL; // 초기화
                newList->PrevNode = NULL; // 초기화
                newList->node = NULL; // 초기화
                newList->matchedWith = 0; //초기화
                    
                if(HeadList == NULL){ // Head 값이 없다면
                    HeadList = newList; // 새로운 리스트를 헤드값으로 
                    CurrentList = HeadList; 
                    CurrentList->node = currentNode; // 검색된 stNode의 주소값을 저장
                    CurrentList->matchedWith = searchedFlag; // 어떤 검색 필드와 매칭이 되었는지 저장
                    searchedFlag = 0; // 검색 필드 값 리셋
                }
                else{ // 검색 결과 리스트를 연결
                    if(CurrentList->NextNode != NULL){
                        CurrentList = CurrentList->NextNode;
                    }
                    CurrentList->NextNode = newList;
                    newList->PrevNode = CurrentList;
                    newList->node = currentNode; // 검색된 stNode의 주소값을 저장
                    newList->matchedWith = searchedFlag; // 어떤 검색 필드와 매칭이 되었는지 저장
                    searchedFlag = 0; // 검색 필드 값 리셋
                }
            }
            searchedFlag = 0;
         }
    }
    else if(mode == 3){
        for (currentNode = dataList->pHead; currentNode !=NULL ; currentNode = currentNode->pNext){
            if (stringFind(currentNode->name, searchingValue) >= 0){
                if(searchedFlag == 0){
                    searchedFlag = 3;
                }
            }
            if(searchedFlag > 0){ // 검색 값이 어느 필드의 값과 매칭이 되었다면...
                stSearchedList* newList = (stSearchedList*) malloc(sizeof(stSearchedList)); //검색 결과 임의의 리스트의 메모리 할당
                newList->NextNode = NULL; // 초기화
                newList->PrevNode = NULL; // 초기화
                newList->node = NULL; // 초기화
                newList->matchedWith = 0; //초기화
                    
                if(HeadList == NULL){ // Head 값이 없다면
                    HeadList = newList; // 새로운 리스트를 헤드값으로 
                    CurrentList = HeadList; 
                    CurrentList->node = currentNode; // 검색된 stNode의 주소값을 저장
                    CurrentList->matchedWith = searchedFlag; // 어떤 검색 필드와 매칭이 되었는지 저장
                    searchedFlag = 0; // 검색 필드 값 리셋
                }
                else{ // 검색 결과 리스트를 연결
                    if(CurrentList->NextNode != NULL){
                        CurrentList = CurrentList->NextNode;
                    }
                    CurrentList->NextNode = newList;
                    newList->PrevNode = CurrentList;
                    newList->node = currentNode; // 검색된 stNode의 주소값을 저장
                    newList->matchedWith = searchedFlag; // 어떤 검색 필드와 매칭이 되었는지 저장
                    searchedFlag = 0; // 검색 필드 값 리셋
                }
            }
            searchedFlag = 0;
        }
    }
    else if(mode == 4){
        for (currentNode = dataList->pHead; currentNode !=NULL ; currentNode = currentNode->pNext){
            if (stringFind(currentNode->number, searchingValue) >= 0){
                if(searchedFlag == 0){
                    searchedFlag = 4;
                }
            }
            if(searchedFlag > 0){ // 검색 값이 어느 필드의 값과 매칭이 되었다면...
                stSearchedList* newList = (stSearchedList*) malloc(sizeof(stSearchedList)); //검색 결과 임의의 리스트의 메모리 할당
                newList->NextNode = NULL; // 초기화
                newList->PrevNode = NULL; // 초기화
                newList->node = NULL; // 초기화
                newList->matchedWith = 0; //초기화
                    
                if(HeadList == NULL){ // Head 값이 없다면
                    HeadList = newList; // 새로운 리스트를 헤드값으로 
                    CurrentList = HeadList; 
                    CurrentList->node = currentNode; // 검색된 stNode의 주소값을 저장
                    CurrentList->matchedWith = searchedFlag; // 어떤 검색 필드와 매칭이 되었는지 저장
                    searchedFlag = 0; // 검색 필드 값 리셋
                }
                else{ // 검색 결과 리스트를 연결
                    if(CurrentList->NextNode != NULL){
                        CurrentList = CurrentList->NextNode;
                    }
                    CurrentList->NextNode = newList;
                    newList->PrevNode = CurrentList;
                    newList->node = currentNode; // 검색된 stNode의 주소값을 저장
                    newList->matchedWith = searchedFlag; // 어떤 검색 필드와 매칭이 되었는지 저장
                    searchedFlag = 0; // 검색 필드 값 리셋
                }
            }
            searchedFlag = 0;
        }
    }
    else if(mode == 5){
        for (currentNode = dataList->pHead; currentNode !=NULL ; currentNode = currentNode->pNext){
            if (stringFind(currentNode->group,searchingValue) >= 0){
                if(searchedFlag == 0){
                    searchedFlag = 5;
                }
            }
            if(searchedFlag > 0){ // 검색 값이 어느 필드의 값과 매칭이 되었다면...
                stSearchedList* newList = (stSearchedList*) malloc(sizeof(stSearchedList)); //검색 결과 임의의 리스트의 메모리 할당
                newList->NextNode = NULL; // 초기화
                newList->PrevNode = NULL; // 초기화
                newList->node = NULL; // 초기화
                newList->matchedWith = 0; //초기화
                    
                if(HeadList == NULL){ // Head 값이 없다면
                    HeadList = newList; // 새로운 리스트를 헤드값으로 
                    CurrentList = HeadList; 
                    CurrentList->node = currentNode; // 검색된 stNode의 주소값을 저장
                    CurrentList->matchedWith = searchedFlag; // 어떤 검색 필드와 매칭이 되었는지 저장
                    searchedFlag = 0; // 검색 필드 값 리셋
                }
                else{ // 검색 결과 리스트를 연결
                    if(CurrentList->NextNode != NULL){
                        CurrentList = CurrentList->NextNode;
                    }
                    CurrentList->NextNode = newList;
                    newList->PrevNode = CurrentList;
                    newList->node = currentNode; // 검색된 stNode의 주소값을 저장
                    newList->matchedWith = searchedFlag; // 어떤 검색 필드와 매칭이 되었는지 저장
                    searchedFlag = 0; // 검색 필드 값 리셋
                }
            }
            searchedFlag = 0;
        }
    }
    else{
        for (currentNode = dataList->pHead; currentNode !=NULL ; currentNode = currentNode->pNext){ // datalist 전체를 검색
            if(currentNode->index == atoi(searchingValue)){ // 검색 값이 현재 stNode의 index와 매칭 여부 확인
                if(searchedFlag == 0){
                    searchedFlag = 1; // 검색 값이 어느 필드와 매칭이 되었는지 저장
                }            
            }
            else if (currentNode->id == atoi(searchingValue)){ // 검색 값이 현재 stNode의 id와 매칭 여부 확인
                if(searchedFlag == 0){
                    searchedFlag = 2; // 검색 값이 어느 필드와 매칭이 되었는지 저장
                }
            }
            else if (stringFind(currentNode->name, searchingValue) >= 0){ // 검색 값이 현재 stNode의 name과 매칭 여부 확인
                if(searchedFlag == 0){
                    searchedFlag = 3; // 검색 값이 어느 필드와 매칭이 되었는지 저장
                }
            }
            else if (stringFind(currentNode->number, searchingValue) >= 0){ // 검색 값이 현재 stNode의 number와 매칭 여부 확인
                if(searchedFlag == 0){
                    searchedFlag = 4; // 검색 값이 어느 필드와 매칭이 되었는지 저장
                }
            }
            else if (stringFind(currentNode->group,searchingValue) >= 0){ // 검색 값이 현재 stNode의 group와 매칭 여부 확인
                if(searchedFlag == 0){
                    searchedFlag = 5; // 검색 값이 어느 필드와 매칭이 되었는지 저장
                }
            }
            else{
                searchedFlag = 0;
            }
            if(searchedFlag > 0){ // 검색 값이 어느 필드의 값과 매칭이 되었다면...
                stSearchedList* newList = (stSearchedList*) malloc(sizeof(stSearchedList)); //검색 결과 임의의 리스트의 메모리 할당
                newList->NextNode = NULL; // 초기화
                newList->PrevNode = NULL; // 초기화
                newList->node = NULL; // 초기화
                newList->matchedWith = 0; //초기화
                    
                if(HeadList == NULL){ // Head 값이 없다면
                    HeadList = newList; // 새로운 리스트를 헤드값으로 
                    CurrentList = HeadList; 
                    CurrentList->node = currentNode; // 검색된 stNode의 주소값을 저장
                    CurrentList->matchedWith = searchedFlag; // 어떤 검색 필드와 매칭이 되었는지 저장
                    searchedFlag = 0; // 검색 필드 값 리셋
                }
                else{ // 검색 결과 리스트를 연결
                    if(CurrentList->NextNode != NULL){
                        CurrentList = CurrentList->NextNode;
                    }
                    CurrentList->NextNode = newList;
                    newList->PrevNode = CurrentList;
                    newList->node = currentNode; // 검색된 stNode의 주소값을 저장
                    newList->matchedWith = searchedFlag; // 어떤 검색 필드와 매칭이 되었는지 저장
                    searchedFlag = 0; // 검색 필드 값 리셋
                }
            }
            searchedFlag = 0;
        }
    }
    return HeadList;
}

/* 문자열 2개를 입력받아 각 문자열의 포함 여부 확인, 1이상이면 포함, -1이면 미포함*/
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
