#include<stdio.h> 
#include<stdlib.h> 
#include<stdint.h>
#include<unistd.h>//sleep関数のため 
#include<sys/types.h> 
#include<pthread.h> 
#include<semaphore.h>
#include<time.h> 

#define N 8 /* 哲学者の人数 */ 
#define E 1 /* 哲学者の必要食事回数 */ 
#define THINKING 0 /* 思索中*/ 
#define HUNGRY 1 /* 箸をとりたい*/ 
#define EATING 2 /* 食事中 */ 

int j;
int left; /*左隣を表す数字*/
int right; /*右隣を表す数字*/
int rnd_think[N]; 
int rnd_eat[N];
int state[N]; /* 哲学者の状態 */ 
int phi_eat[N]; /* 哲学者の食事回数 */ 
sem_t mutex; 
sem_t s[N]; /* 哲学者毎のセマフォ */ 

void philosopher(int i); 
void take_chopsticks(int i); 
void put_chopsticks(int i);
void test(int i);
void think(int i); 
void eat(int i);

/*哲学者のプログラム*/
void philosopher(int i){
  while(phi_eat[i] < E){
    if(state[i]==THINKING){
      think(i); /* 思索中 */ 
    }
    if(state[i] != EATING){
      take_chopsticks(i); /* 2本の箸をとる */ 
    }
    eat(i); /* うまいぞ! */ 
    put_chopsticks(i); /* 箸を戻す */ 
  }
} 

/*2本の箸をとるプログラム*/
void take_chopsticks(int i){ 
  sem_wait(&mutex); /*P命令*/
  printf("%d番目の哲学者は空腹です!\n", i+1);
  state[i] = HUNGRY;
  test(i);
  sem_post(&mutex); /*V命令*/
  sem_wait(&s[i]); /*V命令*/
} 

/*箸を戻すプログラム*/
void put_chopsticks(int i){ 
  sem_wait(&mutex); /*P命令*/ 
  printf("%d番目の哲学者は箸を置きました！\n", i+1); 
  state[i] = THINKING;
  left = (i-1)%N;
  right=(i+1)%N;
  if(left < 0){ 
    left = N - 1; 
  }
  test(left); /*左隣は食事をできるか？*/
  test(right); /*右隣は食事をできるか？*/
  sem_post(&mutex); /*V命令*/
}

/*左右の哲学者が食事中か確認するプログラム*/
void test(int i){ 
  left = (i-1)%N; 
  right=(i+1)%N;
  if(left < 0){ 
    left = N - 1; 
  }
  if(state[i] == HUNGRY && state[left] != EATING && state[right] != EATING){
    state[i] = EATING;
    sem_post(&s[i]); /*V命令*/
  }
  else if(state[i] == HUNGRY && state[left] == EATING && state[right] == EATING){ 
    printf("%d番目の哲学者は，両隣の哲学者が食事中のため，食べられません！\n", i+1);
  } else if(state[i] == HUNGRY && state[left] == EATING && state[right] != EATING){ 
    printf("%d番目の哲学者は，左隣の哲学者が食事中のため，食べられません！\n", i+1); 
  } else if(state[i] == HUNGRY && state[left] != EATING && state[right] == EATING){ 
    printf("%d番目の哲学者は，右隣の人が食事中のため，食べられません！\n", i+1); 
  } else{ 
    ; 
  } 
}

/*思索中のプログラム*/
void think(int i){ 
  printf("%d番目の哲学者は考えています！\n", i+1);
  rnd_think[i]=(int)(3*(rand()/(1.0+RAND_MAX))); /*思索時間は3秒以内とする*/
  sleep(rnd_think[i]);
} 

/*食事中のプログラム*/
void eat(int i){ 
  printf("%d番目の哲学者は，箸をとり，食べました．(%d回目の食事)\n", i+1, phi_eat[i] + 1);
  rnd_eat[i]=(int)(3*(rand()/(1.0+RAND_MAX))); /*食事時間は3秒以内とする*/
  sleep(rnd_eat[i]);
  phi_eat[i]++;
} 

int main(void){ 
  pthread_t pt[N]; 
  printf("哲学者はどのような状態ですか？\n"); 
  printf("0:思索中, 1:空腹, 2:食事中\n"); 
  //哲学者の状態を入力する．
  for(j = 0; j < N; j++){
    printf("%d番目の哲学者:", j+1); 
    scanf("%d", &state[j]);
  }
  srand((unsigned int)time(NULL)); //実行ごとに異なる乱数を発生させる
  sem_init(&mutex, 0, 1); //セマフォmutexを1で初期化し，スレッド間で共有
  for(j = 0; j < N; j++){ 
    sem_init(&s[j], 0, 0); //哲学者ごとのセマフォを初期化
    phi_eat[j] = 0;
  }
  for(j = 0; j < N; j++){
    void *jj = (void*)(uintptr_t)j; 
    pthread_create(&pt[j],NULL,(void*)philosopher,jj); //スレッド生成
  }
  for(j = 0; j < N; j++){ 
    pthread_join(pt[j], NULL); //スレッド終了待ち
  }
  printf("全ての哲学者が食事をとりました．\n");
}
