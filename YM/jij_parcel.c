#include <stdio.h>

//일해야하는 최소값 변수 전역 변수
int min_work = 999999;
int ni[51] = {0,}; //택배 레일에 들어오는 배열
int tmp[51] = {0,};

void swap(int *a, int *b ){ //순열을 만드는 스왑 함수
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

//재귀함수로 구현 순열로 정렬하고 그 무게를 측정하고, 최소 값이 나온 값을 출력한다.
//순열을 하나씩 데이터의 값을 바꾸는 방법으로 대응한다.
void permutation(int q, int n, int m, int k){
    int cur_work = 0;
    int tmp_work = 0;
    int w = 0;//워크를 위함
    int p = 0; //배열 쉬프트를 위함
    //int cur_bas[51] = {0,}; 바구니에 어떻게 담기는 지는 알필요가 없음
    if(q == 0){
        while( w != k){
//printf("tmp[] : %d %d\n",tmp[p%n],m);
            if((tmp[p%n] + cur_work) <= m){
                cur_work = cur_work + tmp[p%n];
                p++;
//                printf("u_cur_work : %d\n",cur_work);
            }else{
                tmp_work += cur_work;
                cur_work = tmp[p%n];
                p++;
                w++;
//               printf("o_cur_work : %d\n",cur_work);
                
            }
        }
//        cur_work = 0;
         if(tmp_work <= min_work){
            min_work = tmp_work;
        }
//            printf("end\n");
    }

/*
    if (q == 0) {
        printf("n==0\n");
		for (int jj = 0; jj < 5; jj++){
			printf("%d ", tmp[jj]);
		}
		printf("\n");
		return;
	}
/*
    for(int i ; i < n ; i++){
        printf("%d ",tmp[i]);
    }
    printf("\n");
*/


	for (int i = q - 1; i >= 0; i--){// 이거를 잘 이해해 보자.
		swap(&ni[i], &ni[q-1]);
		tmp[q-1] = ni[q-1];
		permutation(q-1,n, m, k);
		swap(&ni[i], &ni[q-1]); //
	}
    
}


int main(void)
{
    int n = 0; //레일의 개수
    int m = 0; //바구니의 무게
    int k = 0; //일의 시행 횟수

    //입력값 넣기
    scanf("%d %d %d",&n, &m, &k);
    for(int i = 0 ; i < n ; i++){
        scanf("%d ",&ni[i]);
    }
/*
    for(int i ; i < n ; i++){
        printf("%d ",ni[i]);
    }
    printf("\n");
*/

    permutation(n,n,m,k);

    printf("%d",min_work);


    
   return 0;
}
