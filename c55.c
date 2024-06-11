/*
生徒は何人ですか？
3
得点を入力してください。(a[][0]が数学、a[][1]が英語)
a[0][0]=12
a[1][0]=24
a[2][0]=36

a[0][1]=12
a[1][1]=24
a[2][1]=36

数学の平均点：24.000000
英語の平均点：24.000000
数学の最高点：36.000000
英語の最高点：36.000000
数学の最低点：12.000000
英語の最低点：12.000000
数学の分散：96.000000
英語の分散：96.000000
*/
#include<stdio.h>

int NiziU(int a){
  int b;
  b=a*a;
  return b;  
}

double ave_math(int m,int n,float a[m][n]){
  int i;
  float ave,waru,mathsum=0;
  waru=m;
  for(i=0;i<m;i++){
    mathsum+=a[i][0];
  }
  ave=mathsum/waru;
  return ave;
}

double ave_eigo(int m,int n,float a[m][n]){
  int i;
  float eigosum=0;
  double ave,waru;
  waru=m;
  for(i=0;i<m;i++){
    eigosum+=a[i][1];
  }
  ave=eigosum/waru;
  return ave;
}

float max_math(int m,int n,float a[m][n]){
  int i;
  float mathmax=0;
  for(i=0;i<m;i++){
    if(mathmax<a[i][0]){
      mathmax=a[i][0];
    }
  }
  return mathmax;
}

float max_eigo(int m,int n,float a[m][n]){
  int i;
  float eigomax=0;
  for(i=0;i<m;i++){
    if(eigomax<a[i][1]){
      eigomax=a[i][1];
    }
  }
  return eigomax;
}

float min_math(int m,int n,float a[m][n]){
  int i;
  float mathmin=100;
  for(i=0;i<m;i++){
    if(mathmin>a[i][0]){
      mathmin=a[i][0];
    }
  }
  return mathmin;
}

float min_eigo(int m,int n,float a[m][n]){
  int i;
  float eigomin = 100;
  for(i=0;i<m;i++){
    if(eigomin>a[i][1]){
      eigomin=a[i][1];
    }
  }
  return eigomin;
}

double bun_math(int m,int n,float a[m][n]){
  int i;
  double waru,hensa2,bun=0;
  waru=m;
  float b[m][2];
  for(i=0;i<m;i++){
    b[i][0]=a[i][0];
  }
  for(i=0;i<m;i++){
    hensa2+=NiziU(a[i][0]-ave_math(m,2,b));
  }
  bun=hensa2/waru;
  return bun;
}

double bun_eigo(int m,int n,float a[m][n]){
  int i;
  double waru,hensa2,bun=0;
  waru=m;
  float b[m][2];
  for(i=0;i<m;i++){
    b[i][1]=a[i][1];
  }
  for(i=0;i<m;i++){
    hensa2+=NiziU(a[i][1]-ave_eigo(m,2,b));
  }
  bun=hensa2/waru;
  return bun;
}

int main(void){
  int n;
  puts("生徒は何人ですか？");
  scanf("%d",&n);
  int i,j;
  float a[n][2];
  puts("得点を入力してください。(a[][0]が数学、a[][1]が英語)");
  for(i=0;i<2;++i){
    for(j=0;j<n;++j){
      printf("a[%d][%d]=",j,i);
      scanf("%f",&a[j][i]);
    }
      puts("");
  }

  printf("数学の平均点：%f\n",ave_math(n,2,a));
  printf("英語の平均点：%f\n",ave_eigo(n,2,a));
  printf("数学の最高点：%f\n",max_math(n,2,a));
  printf("英語の最高点：%f\n",max_eigo(n,2,a));
  printf("数学の最低点：%f\n",min_math(n,2,a));
  printf("英語の最低点：%f\n",min_eigo(n,2,a));
  printf("数学の分散：%f\n",bun_math(n,2,a));
  printf("英語の分散：%f\n",bun_eigo(n,2,a));

  return 0;

}