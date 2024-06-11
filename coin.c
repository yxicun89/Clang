#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int rand_coin(int num_tosses);
int main (void) {
   int heads = 0;
   int tails = 0;
   srand(time(NULL));
   int num_tosses = 500;
   heads = rand_coin(num_tosses);
   tails = num_tosses - heads;
   printf("表 = %d, 裏 = %d\n", heads, tails);
   return 0;
} /* end main */
/* implement rand_coin() below: */
int rand_coin(int num_tosses) {
   int value;
   int i; //
   int heads = 0;
   for(i=0; i < num_tosses; i++){
      value = rand() % 2;
      if (value == 1) {
         heads++;
      }
   }
   return heads;
}