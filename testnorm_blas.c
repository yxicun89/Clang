/*
ライブラリ BLAS・LAPACK を使用したノルム計算プログラムです．
コンパイルしてください．

[UbuntuなどLinuxの場合]
gcc -o testnorm testnorm_blas.c -llapacke -llapack -lblas -lm
注) 演習室WSではコンパイルできません

[OS Xの場合]
gcc -I(BLASインストールディレクトリ)/include -I(LAPACKインストールディレクトリ)/include -L(BLASインストールディレクトリ)/lib -L(LAPACKインストールディレクトリ)/lib -o testnorm  testnorm_blas.c -llapacke -llapack -lblas -lm
注) brewでインストールしている場合は，brew ls openblas でBLASのインストールディレクトリを，brew ls lapack でLAPACKのインストールディレクトリを表示させることができます．

[Windows（MSYS2+MinGW+OpenBLAS+LAPACK）の場合] 注) 追加
gcc -o testnorm testnorm_blas.c -llapacke -llapack -lcblas -lm

コンパイルに成功した場合は，./testnorm で実行できます．計算結果を確認してください．
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cblas.h>
#include <lapacke.h>

/*
 演習問題プログラム（ベクトル・行列ノルム）
 */
int main(void)
{
  int m = 100, n = 100;
  int i,j;
  double *x;
  double *A; // LAPACK, BLAS を使用する場合は1次元配列にした方が便利
  double xnorm1, xnorm2, xnorminf, Anorm1, Anormfro, Anorminf;

  x = (double *)calloc(n,sizeof(double));
  if(x == NULL)
  {
    printf("領域の確保に失敗（ベクトル）\n");
    exit(1);
  }

  A = (double *)calloc(m * n,sizeof(double));
  if(A == NULL)
  {
    printf("領域の確保に失敗（行列）\n");
    exit(1);
  }

  /* ベクトルの定義 */
  for(i = 0; i < n; i++) x[i] = i + 1;

  /* 行列の定義 (行優先方式の格納) */
  for(i = 0; i < m; i++)
  {
    for(j = 0; j < n; j++)
    {
      A[i*n + j] = fmin(i+1,j+1);
    }
  }

  /* ベクトルノルムの計算 */
  xnorm1 = cblas_dasum(n,x,1);
  xnorm2 = cblas_dnrm2(n,x,1);
  xnorminf = fabs(x[cblas_idamax(n,x,1)]);
  printf("vector: 1 norm = %e; 2 norm = %e; max norm = %e\n", xnorm1, xnorm2, xnorminf);

  /* 行列ノルムの計算 */
  Anorm1 = LAPACKE_dlange(LAPACK_ROW_MAJOR,'1',m,n,A,m);
  Anormfro = LAPACKE_dlange(LAPACK_ROW_MAJOR,'F',m,n,A,m);
  Anorminf = LAPACKE_dlange(LAPACK_ROW_MAJOR,'I',m,n,A,m);;
  printf("matrix: 1 norm = %e; Frobenius norm = %e; max norm = %e\n", Anorm1, Anormfro, Anorminf);

  free(x);
  free(A);

  return(0);
}
