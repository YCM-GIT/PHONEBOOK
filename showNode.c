#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "double_linked_list.h"
#include "phonebook.h"

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"


static void subMenu(stList* pList, int index);
static void EditMenu(stList* pList, int index);
static void EditName(stList* pList, int index);
static void EditNumber(stList* pList, int index);
static void EditGroup(stList* pList, int index);
static void EditFavorate(stList* pList, int index);
static void StartCalling(stList* pList, int index);
static void MainFunction();
static int PrintShowNode(stList* pList, int index);

extern int ShowNode(stList* pList, int index) {

    stNode* cur;
    system("clear");

    if (IsEmpty(pList)) {
        printf("There is no member.\n");
        return -1;
    }
    else {
        cur = pList->pHead;
        while (cur->pNext != NULL) {
            if (index == cur->index) {
                printf("%5d ", cur->id);
                printf("%3d ", cur->index);
                printf("%30s ", cur->name);
                printf("%20s ", cur->number);
                printf("%20s ", cur->group);
                printf("%3d", cur->favorite);
                printf("\n");

                subMenu(pList, index);

                break;
            }
            cur = cur->pNext;
        }
    }
    return 0;
}


static void subMenu(stList* pList, int index) {
    
    int i=0;    

    while (i< 4) {
        
        printf("\n");
        printf("****Sub Menu****\n");
        printf("1: Delete \n");
        printf("2: Edit \n");
        printf("3. Calling \n");
        printf("4. Go to Main Menu \n");
        printf("Press number: ");
        scanf("%d", &i);

        
        if (i == 1) {
           DeleteNode(pList, index);
           printf("Delete Success \n");
           system("clear");
           
        }

       else if (i == 2) {
           EditMenu(pList, index);
           SortList(pList);
       }

       else if (i == 3) {
            StartCalling(pList, index);
       }      

      else {
            MainFunction();
           
        }
       
    }
    
}


static void EditMenu(stList* pList, int index) {
    int num = 0;
    int j = 0;
    stNode* cur;

    system("clear");


    while (j < 5) {

        if (IsEmpty(pList)) {
            printf("There is no member.\n");
           
        }
        else {

            cur = pList->pHead;
            while (cur->pNext != NULL) {
                if (index == cur->index) {
                    printf("%5d ", cur->id);
                    printf("%3d ", cur->index);
                    printf("%30s ", cur->name);
                    printf("%20s ", cur->number);
                    printf("%20s ", cur->group);
                    printf("%3d", cur->favorite);
                    printf("\n");

                    break;
                }
                cur = cur->pNext;
            }
        }

        while (num < 5) {
            printf("\n");
            printf("1: Name \n");
            printf("2: Phone Number \n");
            printf("3. Group \n");
            printf("4. Favorate \n");
            printf("5. sub Menu \n");
            printf("Press number: ");
            scanf("%d", &num);

            switch (num)
            {
            case 1:
                EditName(pList, index);

                break;
            case 2:
                EditNumber(pList, index);

                break;
            case 3:
                EditGroup(pList, index);

                break;
            case 4:
                EditFavorate(pList, index);

                break;
            default:
                break;
            }
            break;
        }
        j = num;

    }
    system("clear");
    PrintShowNode(pList, index);
    subMenu(pList, index);
    return;

}


static void EditName(stList* pList, int index) {
    stNode* cur; 

    if (IsEmpty(pList)) {
        printf("There is no member.\n");
    }
    else {        
        cur = pList->pHead;        
        while (cur->pNext != NULL) { 
            if (index == cur->index) {  
                printf("New name: ");
                scanf("%s", cur->name);                        
                             
                break;
            }
            cur = cur->pNext;
        }
       
    }
    system("clear");
}

static void EditNumber(stList* pList, int index) {
    stNode* cur;

    if (IsEmpty(pList)) {
        printf("There is no member.\n");
    }
    else {
        cur = pList->pHead;
        while (cur->pNext != NULL) {
            if (index == cur->index) {
                printf("New number: ");
                scanf("%s", cur->number);
                printf("%s\n", cur->number);
                break;
            }
            cur = cur->pNext;
        }

    }
    system("clear");
}


static void EditGroup(stList* pList, int index) {
    stNode* cur;

    if (IsEmpty(pList)) {
        printf("There is no member.\n");
    }
    else {
        cur = pList->pHead;
        while (cur->pNext != NULL) {
            if (index == cur->index) {
                printf("New Group: ");
                scanf("%s", cur->group);
                printf("%s\n", cur->group);
                break;
            }
            cur = cur->pNext;
        }
    }
    system("clear");
}

static void EditFavorate(stList* pList, int index) {
    stNode* cur;
    int scalar = 0;
    bool b = false;   

    if (IsEmpty(pList)) {
        printf("There is no member.\n");
    }
    else {
        cur = pList->pHead;
        while (cur->pNext != NULL) {
            if (index == cur->index) {
                printf("New Favorate: ");
                scanf("%d", &scalar);
                b=(bool)scalar;
                cur->favorite = b;
                printf("b: %d \n", b);
                printf("Favorate: %d\n", cur->favorite);
                break;
            }
            cur = cur->pNext;
        }
    }
    system("clear");

}

static void StartCalling(stList* pList, int index) {
    int num;
    int i;
    

    while (1) 
    {
        system("clear");
        PrintShowNode(pList, index);
       
        for (i = 0;i < 10; i++) {
            printf(ANSI_COLOR_RED "*Calling*" ANSI_COLOR_RESET "");
            printf(ANSI_COLOR_GREEN "*Calling*" ANSI_COLOR_RESET "");
            printf(ANSI_COLOR_YELLOW "*Calling*" ANSI_COLOR_RESET "");
            printf(ANSI_COLOR_BLUE "*Calling*" ANSI_COLOR_RESET "");
            printf(ANSI_COLOR_MAGENTA "*Calling*" ANSI_COLOR_RESET "");
            printf(ANSI_COLOR_CYAN "*Calling*" ANSI_COLOR_RESET "\n");

        };

        printf("If you want to hang up, press 1:   ");
        scanf("%d", &num);

        if (num == 1) { 
            system("clear");
            PrintShowNode(pList, index);
            break;
        }

     }
 }
 

static int PrintShowNode(stList* pList, int index) {

    stNode* cur;
    system("clear");

    if (IsEmpty(pList)) {
        printf("There is no member.\n");
        return -1;
    }
    else {
        cur = pList->pHead;
        while (cur->pNext != NULL) {
            if (index == cur->index) {
                printf("%5d ", cur->id);
                printf("%3d ", cur->index);
                printf("%30s ", cur->name);
                printf("%20s ", cur->number);
                printf("%20s ", cur->group);
                printf("%3d", cur->favorite);
                printf("\n");                

                break;
            }
            cur = cur->pNext;
        }
    }
    return 0;
}



static void MainFunction() {
    printf("Main Function \n");
}
