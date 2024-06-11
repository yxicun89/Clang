/*
1~100個の整数をクイックソートします。整数の個数を入力してください。
4
ソート前
1番目 5
2番目 22
3番目 99
4番目 22

ソート後
1番目 5
2番目 22
3番目 22
4番目 99
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>


void q_sort(int p[], int left, int right)
{
    int piv, lside, rside;

    lside = left;
    rside = right;
    piv = p[left];
    while (left < right)
    {
        while ((p[right] >= piv) && (left < right))
            right--;
        if (left != right)
        {
            p[left] = p[right];
            left++;
        }
        while ((p[left] <= piv) && (left < right))
            left++;
        if (left != right)
        {
            p[right] = p[left];
            right--;
        }
    }
    p[left] = piv;
    piv = left;
    left = lside;
    right = rside;
    if (left < piv)
        q_sort(p, left, piv-1);
    if (right > piv)
        q_sort(p, piv+1, right);
}



int main(void){
  int i,n;

  srand((unsigned)time(NULL));

  printf("1~100個の整数をクイックソートします。");
  printf("整数の個数を入力してください。\n");
  scanf("%d",&n);
  while(n>100){
    printf("もう一度Nを入力してください。\n");
    scanf("%d",&n);
  }
  int p[n];
  printf("ソート前\n");
  for(i=0;i<n;i++){
    p[i]=rand()%100+1;
    printf("%d番目 %d\n",i+1,p[i]);
  }
  q_sort(p,0,n-1);
  printf("\n");
  printf("ソート後\n");
  for(i=0;i<n;i++){
    printf("%d番目 %d\n",i+1,p[i]);
  }
  return 0;
}
