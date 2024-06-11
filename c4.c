/*
N次連立方程式をときます。次元を教えてください。
3
aを入力してください。
a[0][0]=5
a[0][1]=-1
a[0][2]=-1

a[1][0]=2
a[1][1]=1
a[1][2]=-3

a[2][0]=1
a[2][1]=1
a[2][2]=1

bを入力してください。
b[0]=0
b[1]=-5
b[2]=6

xは以下の通りです。
x[0]=1.00
x[1]=2.00
x[2]=3.00

 */
#include<stdio.h>

int main(void){
  int N;
  puts("N次連立方程式をときます。次元を教えてください。");
  scanf("%d",&N);
  int i,j,k,l;
  float m[N][N];
  float b[N];

  puts("aを入力してください。");
  for(i=0;i<N;++i){
    for(j=0;j<N;++j){
      printf("a[%d][%d]=",i,j);
      scanf("%f",&m[i][j]);
    }
      puts("");
  }

  puts("bを入力してください。");
  for(i=0; i<N; ++i){
    printf("b[%d]=",i);
    scanf("%f",&b[i]);
  }

  for( i=0; i<N; i++){
    for(j = i+1; j < N; j++){
      float coef = m[j][i]/m[i][i]; //対角要素を1にするための操作 縦（１列分）計算している。
      float del[N];

      for(k = 0; k < N; k++){
	del[k]=m[i][k]*coef;
	}

  for(l =0; l<N; l++){
    m[j][l] -= del[l];
  }
      b[j] -= b[i]*coef;
    }
  }

  for( i =N-1; i>=0; i--){
    float x =1. / m[i][i];
    m[i][i] *= x;
    b[i] *=  x;

    for( j= 0; j<i; j++){
      b[j] -= b[i]*m[j][i];
      m[j][i]=0;
    }
  }

  for( i =0; i<N; i++){
    for(j =0; j<N; j++){
      // printf("%1.f",m[i][j]);
      if(j==N-1){
	//printf("\n");
      }
    }
  }

  puts("");
  puts("xは以下の通りです。");
  for( i=0; i<N; i++){

    printf("x[%d]=%.2f\n",i,b[i]);
  }
  return 0;
}


