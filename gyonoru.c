#include<stdio.h>
#include<math.h>

void main(void){
    int m,n,i,j;
    printf("行数と列数を入力してください");
    scanf("%d%d",&m,&n);
    int x[m][n];
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            x[i][j]=0;
        }
    }
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            printf("x[%d][%d]=",i,j);
            scanf("%d",&x[i][j]);
            //printf("x[%d][%d]=%d\n",i,j,x[i][j]);
        }
    }
    int intmax;
    int sum=0,max=0;  
    //printf("%d,%d\n",m,n);
    if(m>n){
        intmax=m;
    }else{
        intmax=n;
    }
    //printf("%d",intmax);
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            sum+=x[i][j];
        }
        if(sum>max){
                max=sum;
        }
        sum=0;
    }
    printf("行列ノルムは%dです。",max);
}
