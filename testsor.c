/*
このプログラムを使用する場合は，まずlaiter.c内の関数gaussseidelおよびsorを完成させてください．
完成後，コンパイルしてください．

[UbuntuなどLinux, OS X (gccインストール済), Windows (MSYS2+MinGW) の場合]
gcc -o testsor testsor.c laiter.c lacalc.c -lm
注) 演習室WSのCentOSでも同じ

コンパイルに成功した場合は，./testsor で実行できます．
計算結果を確認してください．
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int jacobi(int n, double **a, double *b, double *x);
int gaussseidel(int n, double **a, double *b, double *x);
int sor(int n, double **a, double *b, double w, double *x);
void vecpm(int n, double *veca, double *vecb, double a, double b, double *vecc);
void mulmatvec(int m, int n, double **matA, double *vecb, double *vecc);
double vecnorm(int n, double *veca, int type);

/*
 演習問題確認プログラム（SOR法）
*/
int main(void)
{
  int n = 100;
  int i,j,rval;
  double *b,*exactx,*diffx;
  double **A;
  double *jcx,*gsx,*sorx;
  double abserr,xnorm;
  double w;

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

  /* 初期ベクトルを零ベクトル以外にするには，各要素に値を格納する必要有 */
  jcx = (double *)calloc(n,sizeof(double));
  if(jcx == NULL)
  {
    printf("領域の確保に失敗（近似解ベクトル：ヤコビ法）\n");
    exit(1);
  }

  /* 初期ベクトルを零ベクトル以外にするには，各要素に値を格納する必要有 */
  gsx = (double *)calloc(n,sizeof(double));
  if(gsx == NULL)
  {
    printf("領域の確保に失敗（近似解ベクトル：ガウス・ザイデル法）\n");
    exit(1);
  }

  /* 初期ベクトルを零ベクトル以外にするには，各要素に値を格納する必要有 */
  sorx = (double *)calloc(n,sizeof(double));
  if(sorx == NULL)
  {
    printf("領域の確保に失敗（近似解ベクトル：SOR法）\n");
    exit(1);
  }
  
  /* 真の解ベクトルの定義 */
  for(i = 0; i < n; i++) exactx[i] = 1.1;

  /* 行列1 */
  double h = 1.0 / n;
  A[0][0] = 1.0;
  A[n-1][n-1] = 1.0;
  for(i = 1; i < n-1; i++)
  {
    A[i][i-1] = 1.0 / h;
    A[i][i] = 4.0 / h;
    A[i][i+1] = 1.0 / h;
  }

  /* 行列2: こちらも試してみてください */
  /* for(i = 0; i < n; i++)
  {
    for(j = 0; j < n; j++)
    {
      A[i][j] = fmin(i+1,j+1);
    }
  } */

  /* 右辺ベクトルの計算 */
  mulmatvec(n,n,A,exactx,b);

  /* ヤコビ法 */
  rval = jacobi(n,A,b,jcx);
  
  /* 相対誤差の計算（ヤコビ法） */
  xnorm = vecnorm(n,exactx,2);
  if(rval == 0)
  {
    vecpm(n,jcx,exactx,1.0,-1.0,diffx);
    abserr = vecnorm(n,diffx,2);
    printf("Relative error (Jacobi method) = %e\n\n", abserr/xnorm);
  }

  /* ガウス・ザイデル法 */
  rval = gaussseidel(n,A,b,gsx);
  
  /* 相対誤差の計算（ガウス・ザイデル法） */
  if(rval == 0)
  {
    vecpm(n,gsx,exactx,1.0,-1.0,diffx);
    abserr = vecnorm(n,diffx,2);
    printf("Relative error (Gauss-Seidel method) = %e\n\n", abserr/xnorm);
  }

  /* SOR法: w = 0.9 */
  w = 0.9;
  rval = sor(n,A,b,w,sorx);
  
  /* 相対誤差の計算（SOR法: w = 0.9） */
  if (rval == 0)
  {
    vecpm(n,sorx,exactx,1.0,-1.0,diffx);
    abserr = vecnorm(n,diffx,2);
    printf("Relative error (SOR method: w = %e) = %e\n", w, abserr/xnorm);
  }
  
  free(b);
  free(exactx);
  free(diffx);
  for(i = 0; i < n ; i++)
  {
    free(A[i]);
  }
  free(A);
  free(jcx);
  free(gsx);
  free(sorx);
  
  return(0);
}