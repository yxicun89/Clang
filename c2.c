/*
何段ですか？
8
       *
      **
     ***
    ****
   *****
  ******
 *******
********

 */

#include <stdio.h>

int main(void)
{
  int i,j,k,x;
   
  puts("何段ですか？");
  scanf("%d",&x);
  
  for(i=1;i<=x;++i) {
    
    for(j=1;j<=x-i;++j) {
       printf(" ");
    }

    for(k=1;k<=i;++k) {
       printf("*");
    }
    
    printf("\n");
  }

  return 0;
}
