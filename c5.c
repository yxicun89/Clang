#include<stdio.h>



double Save(int size1, int size2, float arr[size1][size2] ){

  double dbl,ave;
  dbl = size1;
  int i, j, result = 0;
  for (i = 0; i < size1;++i) {
      result += arr[i][0];
    
  }

  ave = result/dbl;
  return ave;
}

double Eave(int size1, int size2, float arr[size1][size2] ){

  double dbl,ave;
  dbl = size1;
  int i, j, result = 0;
  for (i = 0; i < size1;++i) {
      result += arr[i][1];
  }

  ave = result/dbl;
  return ave;
}

int Smax(int size1, int size2, float arr[size1][size2]){

  int i, j= 0;
  float max = arr[0][0];
    for (i = 0; i < size1;++i) {
      if(max < arr[i][0]){
       max = arr[i][0];
    }
    }
    
  return max;
}

int Emax(int size1, int size2, float arr[size1][size2]){

  int i, j= 0;
  float max = arr[0][1];
    for (i = 0; i < size1;++i) {
      if(max < arr[i][1]){
       max = arr[i][1];
    }
    }
    
  return max;
}

int Smin(int size1, int size2, float arr[size1][size2]){

  int i, j= 0;
  float min = arr[0][0];
    for (i = 0; i < size1;++i) {
      if(min > arr[i][0]){
       min = arr[i][0];
    }
    }
    
  return min;
}

int Emin(int size1, int size2, float arr[size1][size2]){

  int i, j= 0;
  float min =arr[0][1] ;
    for (i = 0; i < size1;++i) {
      if(min > arr[i][1]){
       min = arr[i][1];
    }
    }
    
  return min;
}

double Sbun(double ave, int size1, int size2, float arr[size1][size2]){
 
double dbl,bun,bunn;
dbl = size1;


 int i, j, result = 0;
  for (i = 0; i < size1;++i) {
    result += (arr[i][0])*(arr[i][0]);
    
  }

bun = result/dbl;
bunn = bun - ave*ave;
  return bunn;

}

double Ebun(double ave,int size1, int size2, float arr[size1][size2]){

 double dbl,bun,bunn;
 dbl = size1;

 
 int i, j, result = 0;
  for (i = 0; i < size1;++i) {
    result += (arr[i][1])*(arr[i][1]);
    
  }

  bun = result/dbl;
  bunn = bun - (ave)*(ave);
  return bunn;

}



void main(void){

  int n;
  int i;
  int j;
  double dbl;

  puts("生徒数を入力してください");
  scanf("%d",&n);

  float arr[n][2];
  dbl = n;



  puts("点数の入力");
  for(i=0;i<n;++i){

      printf("%d人目の数学の点数: ",i+1);
      scanf("%f",&arr[i][0]);
      printf("%d人の目英語の点数: ",i+1);
      scanf("%f",&arr[i][1]);

      puts("");
  }

  double save = Save(n,2,arr);
  double eave = Eave(n,2,arr);



  printf("数学平均%1.1f点\n",Save(n,2,arr));
  printf("英語平均%1.1f点\n",Eave(n,2,arr));
  printf("数学の分散%1.2f\n",Sbun(save,n,2,arr));
  printf("英語の分散%1.2f\n",Ebun(eave,n,2,arr));
  printf("数学の最高点%d点\n",Smax(n,2,arr));
  printf("英語の最高点%d点\n",Emax(n,2,arr));
  printf("数学の最低点%d点\n",Smin(n,2,arr));
  printf("英語の最低点%d点\n",Emin(n,2,arr));




}