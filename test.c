#include <stdio.h>
#include <stdlib.h>

typedef struct test {
    int number;
    struct test* prevNode;
    struct test* nextNode;
} Node;

Node* Head = NULL;
Node* Tail = NULL;
Node* Current = NULL;
Node* newNode = NULL;

int main()
{
    printf("Make 5 Node\n");
    int i;
    for(i=0;i<5;i++){
        Node* temp = (Node*)malloc(sizeof(Node));
        temp->number = i;
        temp->prevNode = NULL;
        temp->nextNode = NULL;
                
        if(i==0){
            Head = temp;
        }
    
        else{
            Node* T = Head;
            while(T->nextNode != NULL){
                T = T->nextNode;
            }
            T->nextNode = temp;
            temp->prevNode = T;
            Tail = temp;
        }
    }

    for (i = 0; i < 5; i++) {
        if(i==0) {
            Current = Head;
        }
		printf(" List[%d] : %d \n", i, Current->number);
        Current = Current->nextNode;
	}    
    printf("Insert new node between 2nd and 3rd\n");
    
    Node* newNode2 = (Node*)malloc(sizeof(Node));
    newNode2->number = 6;
    newNode2->prevNode = NULL;
    newNode2->nextNode = NULL;
    //printf(" List[%d] : %d \n", 6, newNode2->number);
    Current = Head;
    //printf(" List[%d] : %d \n", 10, Head->number);
    for(i=0;i<5;i++)
    {
        if(i==1){
            newNode2->nextNode = Current->nextNode;            
            newNode2->prevNode = Current;            
            if(Current->nextNode != NULL){
                //Current->prevNode->nextNode = newNode2;
                Current->nextNode->prevNode = newNode2;
            }
            //printf("Add[%d] : %d \n", i, Current->number);
            //break;           
            Current->nextNode = newNode2;
            
        }
        //printf(" List[%d] : %d \n", i, Current->number);
        Current = Current->nextNode;        
    }
    
    Current = Head;
    for (i = 0; i < 6; i++) {
    	printf(" List[%d] : %d \n", i, Current->number);
        if(Current->nextNode != NULL) Current = Current->nextNode;
	} 

   printf("Delete 4th node (List[3] : 2)\n");
   Current = Head;
   for(i=0;i<5;i++){
        if(i==3){
            Current->prevNode->nextNode = Current->nextNode;
            Current->nextNode->prevNode = Current->prevNode;
            //Current->prevNode = NULL;
            //Current->nextNode = NULL;
        }
        //printf(" List[%d] : %d \n", i, Current->number);
        Current = Current->nextNode;
        //printf(" List[%d] : %d \n", i, Current->number);
        if(Current->nextNode == NULL) break;
   }
   Current = Head;
   for (i = 0; i < 6; i++) {
    	printf(" List[%d] : %d \n", i, Current->number);
        if(Current->nextNode != NULL) Current = Current->nextNode;
        else break;
	} 
}