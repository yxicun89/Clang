#include<stdio.h>
int nizyou(int a){
    return a*a;
}

int threezyou(int a){
    return a*a*a;
}
void main(){
    int i,j;
    for(i=0;i<10000;i++){
        for(j=0;j<50;j++){
            if(nizyou(i)==(threezyou(j)+j+3)){
                printf("x=%d, y=%d",j,i);
            }
        }
    }
}