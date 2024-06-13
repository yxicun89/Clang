#include<stdio.h>

void main(void){
    int alen,blen,clen,dlen,elen;
    double a=0.3,b=0.25,c=0.2,d=0.15,e=0.1,averagelen;
    /*  
    printf("a1の生起確率を入力してください\n");
    scanf("%f",&a);
    printf("a2の生起確率を入力してください\n");
    scanf("%f",&b);
    printf("a3の生起確率を入力してください\n");
    scanf("%f",&c);
    printf("a4の生起確率を入力してください\n");
    scanf("%f",&d);
    printf("a5の生起確率を入力してください\n");
    scanf("%f",&e);
    */
    printf("a1の符号長を入力してください\n");
    scanf("%d",&alen);
    printf("a2の符号長を入力してください\n");
    scanf("%d",&blen);
    printf("a3の符号長を入力してください\n");
    scanf("%d",&clen);
    printf("a4の符号長を入力してください\n");
    scanf("%d",&dlen);
    printf("a5の符号長を入力してください\n");
    scanf("%d",&elen);
    averagelen=a*alen+b*blen+c*clen+d*dlen+e*elen;
    printf("平均長の長さ=%.2f",averagelen);
}