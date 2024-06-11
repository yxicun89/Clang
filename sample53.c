#include<stdio.h>

void set_zero(int v[],int n){
    int i;

    for(i=0;i<n;i++){
        v[i]=0;
    }
}

void print_array(const int v[],int n){
    int i;

    printf("{");
    for(i=0;i<n;i++){
        printf("%d",v[i]);
        printf("}");
    }
}

int main(void){
    int arr1[] = {1,2,3,4,5};
    int arr2[] = {3,2,1};

    printf("arr1 = "); print_array(arr1,5); putchar('\n');
    printf("arr2 = "); print_array(arr2,3); putchar('\n');    

    set_zero(arr1,5);
    set_zero(arr2,3);

    printf("両配列の全要素に０を代入しました。\n");
    printf("arr1="); print_array(arr1,5); putchar('\n');
    printf("arr2="); print_array(arr2,3); putchar('\n');

    return 0;
}