all: double_linked_list.o searchDiplay.o testSearch.o
	gcc -o testSearch double_linked_list.o searchDiplay.o testSearch.o
	./testSearch