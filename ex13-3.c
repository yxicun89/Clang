#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
  FILE *fp;
  int m,n;
  int **score;
  int i,j,k;
  int *sum;
  int max;
  

  fp = fopen(argv[1],"r");
  if((fp = fopen(argv[1], "r")) == NULL){
      printf("エラー！！");
      exit(1);
  }
 while(1){
   max=0;
   fscanf(fp,"%d %d",&n,&m);
   if(m==0||n==0){
     break;
   }
   score = malloc(sizeof(int*) *m);
   if(score == NULL){
       printf("エラー！！");
       exit(1);
   }
  for(i=0; i<m; i++){ 
    /* 手順3 */
    score[i] = malloc(sizeof(int) *n);
    if(score[i] == NULL){
        printf("エラー！！");
        exit(1);
    }
  }
  sum = malloc(n* sizeof(int));
  if(sum == NULL){
    printf("エラー！！");
    exit(1);
  }
  for(i=0;i<m;i++){
       for(j=0;j<n;j++){
           fscanf(fp,"%d",&score[i][j]);
        }
    }
   for(i=0;i<m;i++){
       for(j=0;j<n;j++){
           sum[j]+= score[i][j];
        }
   }
   for(i=0;i<n;i++){
      if(sum[i]>max){
        max=sum[i];
      }
    }
   printf("%d\n",max);
 }
 fclose(fp);
 free(sum);
 free(score);
 return 0;
}
