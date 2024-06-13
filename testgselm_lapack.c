/*
���C�u���� BLAS�ELAPACK ���g�p���������s�{�b�g�I��t���K�E�X�̏����@�v���O�����ł��D
�R���p�C�����Ă��������D

[Ubuntu�Ȃ�Linux�̏ꍇ]
gcc -o testgselm testgselm_lapack.c -llapacke -llapack -lblas -lm
��) ���K��WS�ł̓R���p�C���ł��܂���

[OS X�̏ꍇ]
gcc -o testgselm -I(BLAS�C���X�g�[���f�B���N�g��)/include -I(LAPACK�C���X�g�[���f�B���N�g��)/include -L(BLAS�C���X�g�[���f�B���N�g��)/lib -L(LAPACK�C���X�g�[���f�B���N�g��)/lib testgselm_lapack.c -llapacke -llapack -lblas -lm

[Windows�iMSYS2+MinGW+OpenBLAS+LAPACK�j�̏ꍇ] ��) �ǉ�
gcc -o testnorm testnorm_blas.c -llapacke -llapack -lcblas -lm

�R���p�C���ɐ��������ꍇ�́C./testgselm �Ŏ��s�ł��܂��D
�v�Z���ʂ��m�F���Ă��������D
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cblas.h>
#include <lapacke.h>

/*
 ���K���v���O�����i�����s�|�b�g�I��t���K�E�X�̏����@�j
 */
int main(void)
{
  int n = 100;
  int i,j;
  double *exactx,*b;
  double *A; // LAPACK, BLAS ���g�p����ꍇ��1�����z��ɂ��������֗�
  double relerr,xnorm;
  int *ipiv;

  exactx = (double *)calloc(n,sizeof(double));
  if(exactx == NULL)
  {
    printf("�領域の確保に失敗（係数行列）\n");
    exit(1);
  }
  
  b = (double *)calloc(n,sizeof(double));
  if(b == NULL)
  {
    printf("領域の確保に失敗（係数行列）\n");
    exit(1);
  }

  A = (double *)calloc(n * n,sizeof(double));
  if(A == NULL)
  {
    printf("領域の確保に失敗（係数行列）\n");
    exit(1);
  }

  ipiv = (int *)calloc(n, sizeof(int));
  if(ipiv == NULL)
  {
    printf("領域の確保に失敗（係数行列）\n");
    exit(1);
  }
  
  /* �^�̉��x�N�g���̒�` */
  for(i = 0; i < n; i++) exactx[i] = 1.1;

  /* �s��̒�` (�s�D������̊i�[) */
  for(i = 0; i < n; i++)
  {
    for(j = 0; j < n; j++)
    {
      A[i*n + j] = fmin(i+1,j+1);
    }
  }

  /* �s��x�N�g���� A*exactx �̌v�Z */
  cblas_dgemv(CblasRowMajor,CblasNoTrans,n,n,1.0,A,n,exactx,1,0.0,b,1);

  /* �^�̉��x�N�g���̃m�����v�Z */
  xnorm = cblas_dnrm2(n,exactx,1);

  /* �����s�|�b�g�I��t���K�E�X�̏����@�ɂ�鋁�� */
  LAPACKE_dgesv(LAPACK_ROW_MAJOR,n,1,A,n,ipiv,b,1);

  /* �덷�x�N�g���̌v�Z�iexactx�֏㏑���j*/
  cblas_daxpy(n,-1.0,b,1,exactx,1);

  /* ���Ό덷�̌v�Z */
  relerr = cblas_dnrm2(n,exactx,1) / xnorm;
  printf("Relative error = %e\n", relerr);

  free(exactx);
  free(b);
  free(A);
  free(ipiv);

  return(0);
}
