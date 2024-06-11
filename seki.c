#include<stdio.h>
#define N 2
#define P(y,x) ((y)*N+(x))
int MatDsp(double*Z){
    int i,j;
    for(i=0;i<N;i++) for(j=0;j<N;j++){
        printf("%2g%c",Z[P(i,j)],j<N-1?',':'\n');
    }
    return 0;
}

int MatSet(double*Z,double d,double e){
    int i,j;
    for(i=0;i<N;i++) for(j=0;j<N;j++){
        Z[P(i,j)]=i-j?d:e;
    } 
    return 0;
}

int MatCpy(double*Z,double*X){
    int i;
    for(i=0;i<N*N;i++){
        Z[i]=X[i];
    }
        /*memcpy(Z,X,N*N*sizeof(double));*/
    return 0;
}
int MatMul(double*Z,double*X,double*Y){
    int i,j,k; double L[N*N];
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            for(L[P(i,j)]=k=0;k<N;k++){
                L[P(i,j)]+=X[P(i,k)]*Y[P(k,j)];
            }
        }
    }
  MatCpy(Z,L);
  return 0;
}
int MatPow(double*Z,double*X,int n){
    double R[N*N];
    for(MatCpy(R,X),MatSet(Z,0,1);0<n;n>>=1){
        n&1?MatMul(Z,Z,R):0;
        1<n?MatMul(R,R,R):0;
    }
    return 0;
}

int main(void){
    int i,j,k,n; double A[N*N],B[N*N];
    printf("2行2列の行列のN乗を計算します。\n　Nを入力してください。");
    scanf("%d",&n);
    for(i=0;i<N*N;i++){
        scanf("%lf",A+i);
    }
    MatPow(B,A,n); MatDsp(B);
    return 0;
}
