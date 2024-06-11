#include<stdio.h>

int factorial(int x){
    int i,f;

    i=0;
    f=1;
    while(i<x){
        ++i;
        f*=i;
    }

    printf("factorial called, %3d! = %12ld\n",x,f);

    return f;
}

int main(void){
    int n,r,ncr;
    
    printf("n:"); scanf("%d",&n);
    printf("r:"); scanf("%d",&r);
    ncr=factorial(n)/(factorial(r)*factorial(n-r));
    printf("n=%d, r=%d, nCr=%ld\n",n,r,ncr);
    return 0;
}