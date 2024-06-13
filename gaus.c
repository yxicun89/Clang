/*
部分ピポット選択付きガウスの消去法プログラム
テスト：testgselm.cを利用すると便利です（詳しくはtestgselm.cのコメントを参照）
 */
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

/* 
  [入力]
    n: 行列・ベクトルの次元
    a: 2次元配列（係数行列）※n次正方行列である必要あり
    b: 1次元配列（右辺ベクトル）
  [出力]
    b: 1次元配列（近似解ベクトル）
  [返却値]
    なし
  注) 右辺ベクトルをとっておきたい場合は，修正が必要
*/
void gausselm(int n, double **a, double *b)
{
  int i,j,k,ip;
  double amax,atemp,btemp;

  /* 前進消去過程 */
  for (k = 0 ; k < n - 1 ; k++)
  {
    /* 部分ピボット探索 */
    amax = fabs(a[k][k]);
    ip = k;
    for (i = k + 1 ; i < n ; i++)
    {
      if (fabs(a[i][k]) > amax)
      {
	amax = fabs(a[i][k]); ip = i;
      }
    }

    /* DBL_EPSILON: 計算機イプシロン（double）．float.hが必要*/
    if(amax < DBL_EPSILON)
    {
      /* 係数行列は特異 (終了) */
      printf("The coeficient matrix is singular...\n");
      exit(1);
    }
    else if (ip != k)
    {
      /* 行の交換 */
      for (j = k ; j < n ; j++)
      {
	atemp = a[k][j];
	a[k][j] = a[ip][j];
	a[ip][j] = atemp;
      }
      btemp = b[k];
      b[k] = b[ip];
      b[ip] = btemp;
    }

    /* [演習] 前進消去部分を記述してください */
    for(i=k+1;i<n;i++){
        a[i][k]=a[i][k]/a[k][k];
        for(j=k+1;i<n;j++){
          a[i][j]=a[i][j]-a[i][k]*a[k][j];
        }
        b[i]=b[i]-a[i][k]*b[k];
    }
  }

  /* 後退代入 */
  /* [演習] 後退代入部分を記述してください */
  b[n-1]=b[n-1]/a[n-1][n-1];
  for(k=n-2;k<n;k++){
    for(j=k+1;k<n;k++){
      b[k]=b[k]-a[k][j]*b[j];
    }
    b[k]=b[k]/a[k][k];
  }
}
