/*
コレスキー法プログラム (完成後，testcho.c のコメントどおりにコンパイル)
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 
  [入力]
    n: 行列・ベクトルの次元
    a: 2次元配列（係数行列）※n次正方行列である必要あり
    b: 1次元配列（右辺ベクトル）
  [出力]
    b: 1次元配列（近似解ベクトル）
  [返却値]
    終了状態：0->正常終了, 1->異常終了
  注) 右辺ベクトルをとっておきたい場合は，修正が必要
*/
int cholesky(int n, double **a, double *b)
{
  int i,j,k;
  double **s;

  s = (double **)calloc(n,sizeof(double *));
  if(s == NULL)
  {
    printf("領域の確保に失敗（コレスキー法）\n");
    return(1);
  }
  for(i = 0; i < n; i++)
  {
    s[i] = (double *)calloc(n,sizeof(double));
    if(s[i] == NULL)
    {
      printf("領域の確保に失敗（コレスキー法）\n");
      return(1);
    }
  }

  /* [演習] スライド24ページを参考にして，コレスキー法プログラムを作成してください．*/
  for(j=0;j<n;j++){
    for(i=0;i<=j;i++){
      s[j][i]=0;
    }
    }
    s[0][0]=sqrt(a[0][0]);
    for(j=1;j<n;j++){
      for(i=0;i<j;i++){
        for(k=0;k<i;k++){
          s[j][i]=s[j][i]+s[j][k]*s[i][k];
        }
        s[j][i]=(a[j][i]-s[j][i])/s[i][i];
      }
      for(k=0;k<j;k++){
        s[j][j]=s[j][j]+pow(s[j][k],2);
      }
      s[j][j]=sqrt(a[j][j]-s[j][j]);
    }
    b[0]=b[0]/s[0][0];
    for(i=1;i<n;i++){
      for(k=0;k<i;k++){
        b[i]=b[i]-s[i][k]*b[k];
      }
      b[i]=b[i]/s[i][i];
    }
    b[n-1]=b[n-1]/s[n-1][n-1];
    for(i=n-2;i>=0;i--){
      for(k=i+1;k<n;k++){
        b[i]=b[i]-s[k][i]*b[k];
      }
      b[i]=b[i]/s[i][i];
    }
  return(0);
}
