#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "double_linked_list.h"
#include "phonebook.h"

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"


static void subMenu(stNode* Node, stList* pList);
static void EditMenu(stNode* Node, stList* pList);
static void EditName(stNode* Node);
static void EditNumber(stNode* Node);
static void EditGroup(stNode* Node);
static void EditFavorate(stNode* Node);
static void StartCalling(stNode* Node);
static int PrintShowNode(stNode* Node);

extern int ShowNode(stNode* Node, stList* pList) {
    
    
    stNode* tmp_stNode;

   system("clear");

    printf("%5d ", Node->id);
    printf("%3d ", Node->index);
    printf("%30s ", Node->name);
    printf("%20s ", Node->number);
    printf("%20s ", Node->group);
    printf("%3d", Node->favorite);
    printf("\n");

   subMenu(Node, pList);

  
    return 0;
}


static void subMenu(stNode* Node, stList* pList) {
    
    int i=0;   
    int index = Node->index;

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
           DeleteNode(pList,Node);          
           system("clear");
           
        }

       else if (i == 2) {
           EditMenu(Node,pList);
           SortList(pList);
       }

       else if (i == 3) {
            StartCalling(Node);
       }      

      else {
            break;
            return;
           
        }
       
    }
    return;
    
}


static void EditMenu(stNode* Node, stList* pList) {
    int num = 0;
    int j = 0;   

    system("clear");

    if (Node->id == 0) {
        printf("There is no Person \n");
        subMenu(Node, pList);
        return;
    } 
    else {

        while (j < 5) {

            printf("%5d ", Node->id);
            printf("%3d ", Node->index);
            printf("%30s ", Node->name);
            printf("%20s ", Node->number);
            printf("%20s ", Node->group);
            printf("%3d", Node->favorite);
            printf("\n");

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
                    EditName(Node);

                    break;
                case 2:
                    EditNumber(Node);

                    break;
                case 3:
                    EditGroup(Node);

                    break;
                case 4:
                    EditFavorate(Node);

                    break;
                default:
                    break;
                }
                break;
            }
            j = num;

        }
        system("clear");
        PrintShowNode(Node);
        subMenu(Node, pList);
        return;
    }

}


static void EditName(stNode *Node) {
    char sName[NAME_LENGTH];
    printf("New name: ");
    //scanf("%s", Node->name); 
    scanf(" %[^\n]s", sName);	
    strcpy(Node->name, sName);

    system("clear");
}


static void EditNumber(stNode* Node) {

    printf("New number: ");
    scanf("%s", Node->number);    

    system("clear");
}


static void EditGroup(stNode* Node) {
    char sGroup[GROUP_LENGTH];
    printf("New Group: ");
    //scanf("%s", Node->group);
    scanf(" %[^\n]s", sGroup);
    strcpy(Node->group, sGroup);

    system("clear");
}

static void EditFavorate(stNode* Node) {
   
    int scalar = 0;
    bool b = false;   
 
    printf("New Favorate: ");
    scanf("%d", &scalar);
    b=(bool)scalar;
    Node->favorite = b;

    system("clear");

}

static void StartCalling(stNode* Node) {
    int num;
    int i; 

    if (Node->id == 0) {
        printf("There is no Person \n");   
        sleep(1);
        system("clear");
        return;
    }

    else {

        while (1)
        {
            system("clear");
            PrintShowNode(Node);

            for (i = 0;i < 5; i++) {
                printf(ANSI_COLOR_RED "*Calling*" ANSI_COLOR_RESET "");
                printf(ANSI_COLOR_GREEN "*Calling*" ANSI_COLOR_RESET "");
                printf(ANSI_COLOR_YELLOW "*Calling*" ANSI_COLOR_RESET "");
                printf(ANSI_COLOR_BLUE "*Calling*" ANSI_COLOR_RESET "");
                printf(ANSI_COLOR_MAGENTA "*Calling*" ANSI_COLOR_RESET "");
                printf(ANSI_COLOR_CYAN "*Calling*" ANSI_COLOR_RESET "\n");

                sleep(1);

            };

            printf("If you want to hang up, press 1:   ");
            scanf("%d", &num);

            if (num == 1) {
                system("clear");
                PrintShowNode(Node);
                break;
            }

        }
    }

    

 }
 

static int PrintShowNode(stNode* Node) {

   
    system("clear");

    printf("%5d ", Node->id);
    printf("%3d ", Node->index);
    printf("%30s ", Node->name);
    printf("%20s ", Node->number);
    printf("%20s ", Node->group);
    printf("%3d", Node->favorite);
    printf("\n");       

    return 0;
}



