#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "double_linked_list.h"
#include "phonebook.h"

// 내 파일의 function을 test 하기 위한 main 함수 나중에는 test파일로 이동
int main(void) {

    

    stList list = { 0 };
    stNode member1 = { 10001, (int)1, "KIM CheolMin", "010-5324-2342", "TEAM", 0, 0 };
    stNode member2 = { 10002, (int)2, "NAM HyeMin", "010-3333-2222", "SECURITY", 0, 1 };
    stNode member3 = { 10003, (int)3, "YANG ChangMin", "010-5879-8156", "VEHICLE", 0 ,1 };
    stNode member4 = { 10004, (int)4, "YU Mi", "010-8488-9323", "VEHICLE", 0, 0 };
    stNode member5 = { 10005, (int)5, "YI TaeYeob", "032-4251-0548", "DOMAIN", 0, 0 };
    stNode member6 = { 10006, (int)6, "JEONG SeungYeon", "02-257-2254", "SECURITY", 0, 1 };
    stNode member7 = { 10007, (int)7, "JEONG InJae", "010-0587-3525", "DOMAIN", 0 ,1 };
    stNode member8 = { 10008, (int)8, "CHOI EunBeom", "010-8759-7452", "VEHICLE", 0, 0 };

    InitializeList(&list);

    printf("****** START *****\n");

    // 노드 추가
    printf("****** Added 8 nodes *****\n");
    AddtoTailNode(&list, &member1);
    AddtoTailNode(&list, &member2);
    AddtoTailNode(&list, &member3);
    AddtoTailNode(&list, &member4);
    AddtoTailNode(&list, &member5);
    AddtoTailNode(&list, &member6);
    AddtoTailNode(&list, &member7);
    AddtoTailNode(&list, &member8);

    printf("****** show Node *****\n");

    //ShowList(&list);     
    stNode* Node = ShowList(&list);
    printf("\nstNode is %s\n", Node->name);
    
    ShowNode(Node, &list);
   

    

    //ShowNode(&list);
    printf("main \n");

    //ShowList(&list);

    return 0;
}


