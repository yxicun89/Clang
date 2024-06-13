#include<stdio.h>

void main(){
    int i,k,j,l;
    int n[100];
    double x,y;
    double z[1000];
    printf("変数kのアドレスは%p\n",&k);
    printf("変数jのアドレスは%p\n",&j);
    printf("変数lのアドレスは%p\n",&l);
    for(i=0;i<50;i++){
        printf("変数n[%d]のアドレスは%p\n",i,&j);
    }
    printf("変数xのアドレスは%p\n",&x);
    printf("変数yのアドレスは%p\n",&y);
    printf("変数z[1]のアドレスは%p\n",&z[1]);
    printf("変数z[100]のアドレスは%p\n",&z[100]);
    printf("変数z[1000]のアドレスは%p\n",&z[1000]);
}