extern void getData(stList* pList, char*); // CSV파일에서 데이터를 읽어 온다.
extern stNode* getNode(char*); // 데이터의 한줄을 파싱해서 stNode의 값 필드값으로 매핑하고 해당 노드 값을 리턴한다.
extern stNode* searchDisplay(stList*); // 검색 화면으로 넘어가서 검색 값을 입력 받고 최종 선택된 한개의 노드값을 리턴한다.
extern stSearchedList* SearchingValue(int mode, stList*, char*); // 데이터에서 찾고자 하는 값을 입력하면 매칭되는 값들의 리스트를 리턴한다.
int stringFind(char* a, char* b); // 문자열 2개를 비교해서 포함 여부를 확인하고 포함 시 1을 미포함시 0을 리턴한다.