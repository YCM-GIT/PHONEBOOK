#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>


#include "double_linked_list.h"
#include "phonebook.h"


void print_screen();
int select_sub();
stList* Import();
void Export(stList* pList);
int CSV_search(char *, char [10][1024]);

int main()
{
	int mode;

	//test code
	stList* import_list;
	stList* export_list;

	print_screen();
	mode = select_sub();

	if (mode == 1)
	{
		import_list = Import();
		PrintList(import_list);
	}	
	else if (mode == 2)
		Export(export_list);
	else
		printf("Select Wrong Number \n");
	
//test
	Export(import_list);

	return 0;
}

void print_screen()
{
	printf("========== SUB  MENU ==========\n");
	printf("========== 1. Import ==========\n");
	printf("========== 2. Export ==========\n");
	printf("===============================\n");
}

int select_sub()
{
	int mode;
	printf("Please select sub menu (1 | 2) :  ");
	scanf("%d", &mode);

	return mode;
}

int CSV_search(char *path, char list[10][1024])
{

	DIR * dir_ptr = NULL;
	struct dirent *file = NULL;
	struct stat buf;
	char *ext;
	char filename[1024];
	int i = 0;

	if((dir_ptr = opendir(path)) == NULL)
	{
		return -1;
	}
	
	while((file = readdir(dir_ptr)) != NULL)
	{
		if(strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0)
		{
			continue;
		}

		sprintf(filename, "%s/%s", path, file->d_name);

		if(stat(filename, &buf) == -1)
		{
			continue;
		}

		if(S_ISDIR(buf.st_mode))
		{
			CSV_search(filename,list);
		}
		else if(S_ISREG(buf.st_mode))
		{
			if((ext = strrchr(filename, '.')) == NULL)
			{
				continue;
			}

			if(strcmp(ext, ".csv") == 0)
			{
				sprintf(list[i],"%s",filename);
				i++;
			}
		}
	}

	closedir(dir_ptr);

	return 0;		
}

char *GetNextString(char* src, char token, char* buf)
{
	while(*src && *src != token)
	{
		*buf++ = *src++;
	}

	if(*(buf-1) == '\n') 
	{
		*(buf-1) = 0;
	}
	else
	{
		*buf = 0;
	}

	if(*src == token)
	{
		src++;
	}

	return src;
}


stList* Import()
{
	stList* list = malloc(sizeof(stList));
	list->pHead = list->pTail = NULL;
	list->sort_needs = 1;
	list->sort_order = 0;
	list->count_node = 0;
/*
	stNode* node = malloc(sizeof(stNode));
	node->pNext = NULL;
	node->pPrev = NULL;
*/
	int i=0;
	int num;
	char path[100];
	char csv[10][1024];

	printf("File Path (default :pwd) : ");
	printf("\n");
	//TODO: Input file Path to User

	getcwd(path,sizeof(path));
	CSV_search(path,csv);

	printf("Select CSV file : \n");

	while(strlen(csv[i]) > 0)
	{
		printf("%d : %s\n",i+1, csv[i]);
		i++;
	}

	scanf("%d",&num);

	FILE* fp;
	if((fp = fopen(csv[num-1],"r")) == NULL)
	{
		printf("Cannot open the file\n");
	}
	
	char *p;
	char temp[100];
	char line[100];
	int j = 0;

	while(fgets(line,sizeof(line),fp) !=NULL)
	{
		stNode* node = malloc(sizeof(stNode));
		node->pNext = NULL;
		node->pPrev = NULL;
		
		p = GetNextString(line, ',', temp);
		node->id = atoi(temp);

		p = GetNextString(p, ',', temp);
		node->index = atoi(temp);
		
		p = GetNextString(p, ',', temp);
		strcpy(node->name,temp);

		p = GetNextString(p, ',', temp);
		strcpy(node->number,temp);
		
		p = GetNextString(p, ',', temp);
		strcpy(node->group,temp);

		p = GetNextString(p, ',', temp);
		node->search_hit = atoi(temp);

		p = GetNextString(p, ',', temp);
		node->favorite = atoi(temp);

		AddtoTailNode(list,node);
	}
	
	return list;
}
	

void Export(stList* pList)
{
	FILE * fp;
	char name[100];
	stNode* cur;

	printf("Please write new filename : "); //Just name not ext
	scanf("%s",name);
	strcat(name,".csv"); // name.csv

	if((fp = fopen(name,"w")) == NULL)
	{
		printf("Cannot create the file\n");
	}
	
	for (cur =pList->pHead; cur !=NULL; cur=cur->pNext)
	{
		fprintf(fp,"%d,%d,%s,%s,%s,%d\n",cur->id, cur->index, cur->name, cur->number, cur->group, cur->favorite);
	}

	fclose(fp);
}
