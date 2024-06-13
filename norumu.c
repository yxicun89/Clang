#include<stdio.h>
#include<math.h>

void main(void){
    int x;
    double sum;  
    int n,t;
    double n1;
    printf("ノルム数ｔを入力してください");
    scanf("%d",&t);
    if(t==1){
        printf("要素数nを入力してください");
        scanf("%d",&n);
        while(n>0){
            printf("要素の値を入力してください\n");
            scanf("%d",&x);
            sum+=x;
            n--;
        }
        printf("1ノルムは%fです。",sum);     
    } else if(t==2){
        printf("要素数nを入力してください");
        scanf("%d",&n);
        while(n>0){
            printf("値を入力してください\n");
            scanf("%d",&x);
            sum+=pow(x,2.0);
            printf("%f\n",sum);
            n--;
        }
        sum=sqrt(sum);
        printf("2ノルムは%fです。",sum);
    }else{
    printf("要素数nを入力してください");
    scanf("%d",&n);
    n1=n;
    while(n>0){
        printf("値を入力してください\n");
        scanf("%d",&x);
        sum+=pow(x,n1);
        printf("pow=%f\n",sum);
        n--;
    }
    sum=pow(sum,1/n1);
    printf("nノルムは%fです。",sum);
}
}

