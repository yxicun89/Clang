#include<stdio.h>
#include<string.h>

int main(void){
    char s1[4]="AB";
    char s2[4]="AB";

    if(s1==s2){
        printf("真");
    } else {
        printf("偽");
    }
    if(s1=="AB"){
        printf("真");
    }else{
        printf("偽");
    }
    return 0;
}