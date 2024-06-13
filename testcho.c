/*
このプログラムを使用する場合は，まずcholesky.cを完成させてください．
完成後，コンパイルしてください．

[UbuntuなどLinux, OS X (gccインストール済), Windows (MSYS2+MinGW) の場合]
gcc -o testcho testcho.c cholesky.c lacalc.c -lm
注) 演習室WSのCentOSでも同じ
注) 第2回講義演習プログラムlacalc.cが必要

コンパイルに成功した場合は，./testlu で実行できます．
計算結果を確認してください．
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cholesky(int n, double **a, double *b);
void vecpm(int n, double *veca, double *vecb, double a, double b, double *vecc);
void mulmatvec(int m, int n, double **matA, double *vecb, double *vecc);
double vecnorm(int n, double *veca, int type);

/*
 演習問題確認プログラム（コレスキー法）
*/
int main(void)
{
  int n = 100;
  int i,j,rval;
  double *b,*exactx,*diffx;
  double **A;
  double abserr,xnorm;

  b = (double *)calloc(n,sizeof(double));
  if(b == NULL)
  {
    printf("領域の確保に失敗（右辺ベクトル）\n");
    exit(1);
  }

  exactx = (double *)calloc(n,sizeof(double));
  if(exactx == NULL)
  {
    printf("領域の確保に失敗（真の解ベクトル）\n");
    exit(1);
  }

  diffx = (double *)calloc(n,sizeof(double));
  if(diffx == NULL)
  {
    printf("領域の確保に失敗（誤差ベクトル）\n");
    exit(1);
  }

  /* 対称行列限定の方法なのに，無駄なメモリを確保している... */
  A = (double **)calloc(n,sizeof(double *));
  if(A == NULL)
  {
    printf("領域の確保に失敗（係数行列）\n");
    exit(1);
  }
  for(i = 0; i < n; i++)
  {
    A[i] = (double *)calloc(n,sizeof(double));
    if(A[i] == NULL)
    {
      printf("領域の確保に失敗（係数行列）\n");
      exit(1);
    }
  }

  /* 真の解ベクトルの定義 */
  for(i = 0; i < n; i++) exactx[i] = 1.1;

  /* 行列の定義 */
  for(i = 0; i < n; i++)
  {
    for(j = 0; j < n; j++)
    {
      A[i][j] = fmin(i+1,j+1);
    }
  }

  /* 右辺ベクトルの計算 */
  mulmatvec(n,n,A,exactx,b);

  /* コレスキー法 */
  rval = cholesky(n,A,b);
  if (rval != 0) exit(1);
  
  /* 相対誤差の計算 */
  xnorm = vecnorm(n,exactx,2);
  vecpm(n,b,exactx,1.0,-1.0,diffx);
  abserr = vecnorm(n,diffx,2);
  printf("Relative error (Cholesky method) = %e\n", abserr/xnorm);

  free(b);
  free(exactx);
  free(diffx);
  for(i = 0; i < n ; i++)
  {
    free(A[i]);
  }
  free(A);

  return(0);
}
