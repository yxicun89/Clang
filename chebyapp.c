/*
 チェビシェフ近似プログラム
*/
#include <stdio.h>
#include <math.h>

/*
  チェビシェフ近似分点計算関数
  [入力]
    n: 分点数-1 (スライドに合わせている)
  [出力]
    x: 1次元配列 (n次元, 分点)
*/
void chebypoint(int n, double *x)
{
  int k;

  for(k = 0; k <= n; k++) x[k] = cos(M_PI*(k+0.5)/(n+1));

  return;
}

/*
  チェビシェフ多項式T_n(x)計算関数
  [入力]
    n:  分点数-1 (スライドに合わせている)
    xp: 多項式の値を求める点
  [返却値]
    xpにおける関数値T_n(xp)
*/
double chebypoly(int n, double xp)
{
  /* [演習] チェビシェフ多項式計算関数を完成させてください (p.24の漸化式＋再帰関数で定義すると簡単) */
  if (n == 1)
        return xp;
    else if(n == 0){
      return 1;
    }else{
      return 2*xp*chebypoly(n-1,xp)-chebypoly(n-2,xp);
    }
}

/*
  チェビシェフ近似係数計算関数
  [入力]
    n: 分点数-1 (スライドに合わせている)
    x: 1次元配列 (分点)
    f: 1次元関数 (分点における関数値)
  [出力]
    c: 1次元配列 (チェビシェフ近似の係数)
  注) 事前にchebypointを実行してください
*/
void chebycoef(int n, double *x, double *f, double *c)
{
  /* [演習] チェビシェフ近似の係数 c_i (p.28) を計算するプログラムを作成してください */
  int i;
  double sum;
  for(i=0;i<n+1;i++){
    sum=f[i];
  }
  c[0]=sum/(n+1);
  for(i=0;i<n+1;i++){
    sum=f[i]*chebypoly(i,x[i]);
  }
  for(i=1;i<n+1;i++){
    c[i]=(2/(n+1)*sum);
  }
  return;
}

/*
  チェビシェフ近似計算関数
  [入力]
    n:  分点数-1 (スライドに合わせている)
    c:  1次元配列 (チェビシェフ近似の係数)
    xp: 補間値を計算する点
  [返却地]
    xpにおける補間値
  注) 事前にchebycoefを実行してください
*/
double chebyapp(int n, double *c, double xp)
{
  int i;
  double rval = 0.0;

  for (i = 0; i <= n ;i++)
  {
    rval += c[i] * chebypoly(i,xp);
  }

  return(rval);
}