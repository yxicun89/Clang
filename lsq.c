/*
 最小二乗近似プログラム (gausselm.cを使用)
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void gausselm(int n, double **a, double *b);

/*
  係数計算プログラム
  [入力]
    n: 分点数-1 (スライドp.26参照)
    m: 近似多項式次元
    x: 1次元配列 ((n+1)次元, 関数値が与えられた点)
    f: 1次元配列 ((n+1)次元, 関数値)
  [出力]
    c: 1次元配列 ((m+1)次元, 係数)
  [返却値]
    終了状態：0->正常終了, 1->異常終了 (正規方程式の解が一意でない)
*/
int lsqcoef(int n, int m, double *x, double *f, double *c)
{
  int i,j,k,l;
  double **A,**mat;

  A = (double **)calloc(n+1,sizeof(double *));
  mat = (double **)calloc(m+1,sizeof(double *));
  if(A == NULL || mat == NULL)
  {
    printf("領域の確保に失敗（最小二乗近似）\n");
    exit(1);
  }
  for(i = 0; i <= n; i++)
  {
    A[i] = (double *)calloc(m+1,sizeof(double));
    if(A[i] == NULL)
    {
      printf("領域の確保に失敗（最小二乗近似）\n");
      exit(1);
    }
  }
  for(i = 0; i <= m; i++)
  {
    mat[i] = (double *)calloc(m+1,sizeof(double));
    if(mat[i] == NULL)
    {
      printf("領域の確保に失敗（最小二乗近似）\n");
      exit(1);
    }
  }
  
  /* 行列 A 各要素の格納 */
  for(i = 0 ; i <= n ; i++)
  {
    for (j = 0 ; j <= m ; j++)
    {
	A[i][j] = pow(x[i], j);
    }
  }

  /* 正規方程式の係数行列 */
  for (k = 0 ; k <= m ; k++)
  {
    for (l = 0 ; l <= m ; l++)
    {
      mat[k][l] = 0.0;
      for (i = 0 ; i <= n ; i++)
      {
	mat[k][l] += A[i][k] * A[i][l];
      }
    }
  }

  /* 正規方程式の右辺ベクトル */
  for (k = 0 ; k <= m ; k++)
  {
    c[k] = 0.0;
    for (i = 0 ; i <= n ; i++)
    {
      c[k] += A[i][k] * f[i];
    }
  }
  
  /* 部分ピポット選択付きガウスの消去法による求解 */
  gausselm(m+1,mat,c);
  
  for(i = 0; i <= n ; i++) free(A[i]);
  free(A);
  for(i = 0; i <= m ; i++) free(mat[i]);
  free(mat);
  
  return(0);
}

/*
  最小二乗近似計算プログラム
  [入力]
    m: 近似多項式次元
    c: 1次元配列 ((m+1)次元, 係数)
    xp: 近似値を計算する点
  [返却値]
    xpにおける近似値
  注) 事前にlsqcoef関数を実行し，係数を求めておく必要がある
*/
double lsqcalc(int m, double *c, double xp)
{
  int i;
  double rval;

  /* ホーナーの算法による関数値計算 */
  rval = c[m];
  for(i = m-1; i >= 0; i--)
  {
    rval = rval*xp + c[i];
  }

  return(rval);
}