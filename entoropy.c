#include<stdio.h>
#include<math.h>
void main(){
    double a1,a2,a3,a4,a5,H;
    printf("生起確率a1を入力してください。");
    scanf("%f",&a1);
    printf("生起確率a2を入力してください。");
    scanf("%f",&a2);
    printf("生起確率a3を入力してください。");
    scanf("%f",&a3);
    printf("生起確率a4を入力してください。");
    scanf("%f",&a4);
    printf("生起確率a5を入力してください。");
    scanf("%f",&a5);
    H=a1*log(a1)+a2*log(a2)+a3*log(a3)+a4*log(a4)+a5*log(a5);
    printf("H=%f",H);
}