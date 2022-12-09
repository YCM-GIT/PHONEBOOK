#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "double_linked_list.h"

int main(void) {

    stList list = {0};
    stMember member1 = {10001, (int)1, "KIM CheolMin", "010-5324-2342", "TEAM", 0, 0};
    stMember member2 = {10002, (int)2, "NAM HyeMin", "010-3333-2222", "SECURITY", 0, 1};
    stMember member3 = {10003, (int)3, "YANG ChangMin", "010-5879-8156", "VEHICLE", 0 ,1};
    stMember member4 = {10004, (int)4, "YU Mi", "010-8488-9323", "VEHICLE", 0, 0};
    stMember member5 = {10005, (int)5, "YI TaeYeob", "032-4251-0548", "DOMAIN", 0, 0};
    stMember member6 = {10006, (int)6, "JEONG SeungYeon", "02-257-2254", "SECURITY", 0, 1};
    stMember member7 = {10007, (int)7, "JEONG InJae", "010-0587-3525", "DOMAIN", 0 ,1};
    stMember member8 = {10008, (int)8, "CHOI EunBeom", "010-8759-7452", "VEHICLE", 0, 0};

    InitializeList(&list);
    
    printf("****** START *****\n");
    if(IsEmpty(&list)==1) {
        printf("This list is empty\n");
    }

// 노드 추가
    printf("****** Added 8 nodes *****\n");
    AddtoTailNode(&list, member1);
    AddtoTailNode(&list, member2);
    AddtoTailNode(&list, member3);
    AddtoTailNode(&list, member4);
    AddtoTailNode(&list, member5);
    AddtoTailNode(&list, member6);
    AddtoTailNode(&list, member7);
    AddtoTailNode(&list, member8);

// 전체 노드 보여주기
    PrintList(&list);

// 1개 노드 삭제 (id 3번)
    printf("****** Deleteed a node with no.3 *****\n");
    DeleteNode(&list, 3);

// index 다시 매기기
    Renumbering(&list);

// 전체 노드 보여주기
    PrintList(&list);


    return 0;
}