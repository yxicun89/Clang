#include<stdio.h>
#include<math.h>

void main(){
    double f;
    double c=10000000;
    double r=1000;
    double x;
    double a=1;
    printf("fの値：");
    scanf("%f",&f);
    x=a/sqrt(a+pow(((2*M_PI*f)*(r/c)),2.0));
    printf("x=%f",x);
}