/* 差分法プログラム */
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

/* 最大反復回数 */
const int ITERMAX = 10000;

/* 絶対許容誤差 */
/* const double epsa = DBL_MIN; */
const double epsa = FLT_MIN;

/* 相対許容誤差 注) エラーが出る人は，それぞれの関数内に移動させてください．*/
/* const double epsr = pow(2,3)*DBL_EPSILON; */
const double epsr = FLT_EPSILON;

void matpm(int m, int n, double **matA, double **matB, double a, double b, double **matC);
double matnorm(int m, int n, double **matA, int type);

/* 矩形領域用差分法関数
  [入力]
    M,N: 分割数
    h: 分割幅
    f: 2次元配列 ((M+2)x(N+2)次元, 右辺関数f(x_i,y_j)格納)
    U: 2次元配列 ((M+2)x(N+2)次元, 初期行列. 境界値格納済)
  [出力]
    U: 2次元配列 ((M+2)x(N+2)次元, 解行列)
  [返却値]
    終了状態：0->正常終了, 1->異常終了
*/
int fdm(int M, int N, double h, double **f, double **U)
{
  /* [演習（発展）] 差分法プログラムを作成してください．*/
  double **U1;  
  double oldnorm,newnorm,sumnorm,error;
  int i;j;
  oldnorm=matnorm(M,N,U,3);
  for(i=0;i<M+2;i++){
      for(j=0;j<N+2;j++){
          U1[i][j]=U[i][j];
      }
  }
  do
  {
    for(i=1;i<M+1;i++){
        for(j=1;j<N+1;j++){
            U1[i][j]=(U[i+1][j]+U[i][j+1]+U1[i-1][j]+U1[i][j-1]+h*h*)
        }
    }
    newnorm = fabs(xnew);
    sumnorm = oldnorm + newnorm;
    oldnorm = newnorm;
    error =;
  }while (error >= epsa + epsr * sumnorm);
  return(0);
}