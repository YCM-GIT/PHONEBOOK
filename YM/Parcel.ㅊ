#include <stdio.h>
#include <stdlib.h>

int N,M,K;
int *data; //배열 선언
int Count;//일하는 횟수
int ThisSum;//현재까지 무게
int TotalSum;  
int minWeight=2500; //최소 중량

void swap(int *a, int *b);
void print_arr(int c);
int Permutation(int n, int r, int depth);



int main()
{
    int i;
    scanf("%d %d %d", &N, &M, &K); //N:레일 수, M: 택배 바구니 무게, K:일하는 목표 횟수

    data = (int*)malloc(N*sizeof(int)); //N개의 배열 할당

    for(i=0; i<N; i++){
        scanf("%d", &data[i]);
    }

    int r = N;
    
    Permutation(N,r,0); //서로다른 n개에서 중복 없이 r개를 택하여 나열하는것을 순열이라 한다. nPr (Permutation)
    printf("%d \n", minWeight);    
    free(data);
    return 0;
}

void swap(int *a, int *b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void print_arr(int c){
    int i=0;

    for (i=0;i<c;i++){
        printf("%d", data[i]); 
    }
    printf("\n");
}

int Permutation(int N, int r, int depth)
{
    if(r==depth){
        //print_arr(depth);
        

    int j=0;
    TotalSum = 0;

    while(Count<K)
    { //K:일하는 목표 횟수
        ThisSum+=data[j];  
        //printf("j:%d Data[j]:%d ThisSumCur:%d \n",j, data[j], ThisSum);        
        
        if(ThisSum>M){ //M: 택배 바구니 무게
            ThisSum=ThisSum-data[j];
            Count++;
            TotalSum+=ThisSum;
            //printf("ThisSum:%d Count:%d \n", ThisSum,Count);
            ThisSum=0;
            j=j-1; //이전 레일로 가기           
        }

        j++;    //다음 레일로 이동

        if(j>=N){ //이동한 곳이 레일밖이면 첫 레일로 이동
                j=0;
            }
    }  

    Count = 0; //Count 초기화  
    //printf("TotalSum:%d \n", TotalSum);   

    if(TotalSum <= minWeight){
        minWeight = TotalSum;
    }

    //printf(" %d \n", minWeight);                
    
    return 0; 
    } 
   
    int i=0;
    for(i=depth; i<N;i++){
        swap(&data[i],&data[depth]);
        Permutation(N,r,depth+1);
        swap(&data[i],&data[depth]);
    }
}

