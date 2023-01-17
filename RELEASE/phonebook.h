#ifndef __Phone_Book__
#define __Phone_Book__

extern stNode* ShowList(stList* pList);  // 정렬된 전체 리스트를 보여주는 함수
extern int SortList(stList* pList);  // 리스트를 정렬하는 함수 (현재는 이름 오름차순)

extern int ShowNode(stNode* Node, stList* pList);


#endif 