/*
���C�u���� BLAS�ELAPACK ���g�p�����m�����v�Z�v���O�����ł��D
�R���p�C�����Ă��������D

[Ubuntu�Ȃ�Linux�̏ꍇ]
gcc -o testnorm testnorm_blas.c -llapacke -llapack -lblas -lm
��) ���K��WS�ł̓R���p�C���ł��܂���

[OS X�̏ꍇ]
gcc -I(BLAS�C���X�g�[���f�B���N�g��)/include -I(LAPACK�C���X�g�[���f�B���N�g��)/include -L(BLAS�C���X�g�[���f�B���N�g��)/lib -L(LAPACK�C���X�g�[���f�B���N�g��)/lib -o testnorm  testnorm_blas.c -llapacke -llapack -lblas -lm
��) brew�ŃC���X�g�[�����Ă���ꍇ�́Cbrew ls openblas ��BLAS�̃C���X�g�[���f�B���N�g�����Cbrew ls lapack ��LAPACK�̃C���X�g�[���f�B���N�g����\�������邱�Ƃ��ł��܂��D

[Windows�iMSYS2+MinGW+OpenBLAS+LAPACK�j�̏ꍇ] ��) �ǉ�
gcc -o testnorm testnorm_blas.c -llapacke -llapack -lcblas -lm

�R���p�C���ɐ��������ꍇ�́C./testnorm �Ŏ��s�ł��܂��D�v�Z���ʂ��m�F���Ă��������D
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cblas.h>
#include <lapacke.h>

/*
 ���K���v���O�����i�x�N�g���E�s��m�����j
 */
int main(void)
{
  int m = 100, n = 100;
  int i,j;
  double *x;
  double *A; // LAPACK, BLAS ���g�p����ꍇ��1�����z��ɂ��������֗�
  double xnorm1, xnorm2, xnorminf, Anorm1, Anormfro, Anorminf;

  x = (double *)calloc(n,sizeof(double));
  if(x == NULL)
  {
    printf("�̈�̊m�ۂɎ��s�i�x�N�g���j\n");
    exit(1);
  }

  A = (double *)calloc(m * n,sizeof(double));
  if(A == NULL)
  {
    printf("�̈�̊m�ۂɎ��s�i�s��j\n");
    exit(1);
  }

  /* �x�N�g���̒�` */
  for(i = 0; i < n; i++) x[i] = i + 1;

  /* �s��̒�` (�s�D������̊i�[) */
  for(i = 0; i < m; i++)
  {
    for(j = 0; j < n; j++)
    {
      A[i*n + j] = fmin(i+1,j+1);
    }
  }

  /* �x�N�g���m�����̌v�Z */
  xnorm1 = cblas_dasum(n,x,1);
  xnorm2 = cblas_dnrm2(n,x,1);
  xnorminf = fabs(x[cblas_idamax(n,x,1)]);
  printf("vector: 1 norm = %e; 2 norm = %e; max norm = %e\n", xnorm1, xnorm2, xnorminf);

  /* �s��m�����̌v�Z */
  Anorm1 = LAPACKE_dlange(LAPACK_ROW_MAJOR,'1',m,n,A,m);
  Anormfro = LAPACKE_dlange(LAPACK_ROW_MAJOR,'F',m,n,A,m);
  Anorminf = LAPACKE_dlange(LAPACK_ROW_MAJOR,'I',m,n,A,m);;
  printf("matrix: 1 norm = %e; Frobenius norm = %e; max norm = %e\n", Anorm1, Anormfro, Anorminf);

  free(x);
  free(A);

  return(0);
}
