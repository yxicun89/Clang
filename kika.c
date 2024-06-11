#include<stdio.h>
int* Sort(int length,int a[length]){
    int i,j,tmp;
    for (i=0; i<length; ++i) {
        for (j=i+1; j<length; ++j) {
            if (a[i] > a[j]) {
                tmp =  a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
    return a;
}

void kika(int length,int t,int n,int a [length]){
    int j,k,l;
    for(j=0;j<length;j++){    
        a[j]=(a[j]*t)%49; //T*Hをする
    }
    Sort(length,a);
    printf("%dH={",t);
    for(k=0;k<length;k++){
        printf("%d,",a[k]);//要素を書き出す。
    }
    printf("}\n");
}

int main(void){
    int i;
    int n=49;
    int a[7]={1,8,15,22,29,36,43};
    for(i=0;i<n;i++){
        if(i%7!=0){
            kika(7,i,n,a);
        }
    }

    return 0;
}