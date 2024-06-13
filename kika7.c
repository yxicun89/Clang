#include<stdio.h>
int fcount;
int Nizyou(int a){
    return a*a;
}
int Gyaku(int s,int x){
    int i,t=0;
    for(i=0;i<s;i++){
        if((x*i)%s==1){
            t=i;
        }
    }
    return t;
}
/*
int samearray(int p[2],int q[2]){
    int i,count=0;
    for(i=0;i<2;i++){
        if(p[i]==q[i]){
            count++;
        }
    }
    if(count == 2){
        return 1;
    }
    return 0;
}
*/
void Plus(int s,int p[2],int q[2]){
    int a=1,b=3,N,G,i,y;
    int lam,nyu;
    N=Nizyou(p[0]);
    //printf("N=%d\n",N);
    G=Gyaku(s,2*p[1]);
    //printf("G=%d\n",G);
    lam=((3*N+a)*G)%s;
    nyu=s+((-N*p[0]+a*p[0]+2*b)*G)%s;
    /*
    printf("lam=%d\n",lam);
    printf("nyu=%d\n",nyu);
    */
    q[0]=(Nizyou(lam)-2*p[0])%s;
    y=(-lam*(Nizyou(lam)-2*p[0])-nyu);
    q[1] = (s+(y%s))%s;
    /*
    for(i=0;i<2;i++){
        printf("q[%d]=%d\n",i,q[i]);
    }
    */
}

void PlusPlus(int s,int p[2],int q[2],int r[2]){
    int i,ram,ny,t;
    int w[2],x[2],y[2],z[2];
    fcount++;
    for(i=0;i<2;i++){
        x[i]=p[i];
        y[i]=q[i];
    }
    
    ram=(s+((q[1]-p[1])*Gyaku(s,(s+q[0]-p[0])%s))%s)%s;
    ny=(s+((p[1]*q[0]-q[1]*p[0])*Gyaku(s,(s+q[0]-p[0])))%s)%s;
    r[0]=(s+(Nizyou(ram)-p[0]-q[0])%s)%s;
    r[1]=(s+(-ram*r[0]-ny)%s)%s;
    //printf("ram=%d, ny=%d\n",ram,ny);
    for(i=0;i<2;i++){
        //printf("r[%d]=%d\n",i,r[i]);
        z[i]=r[i];
    }
    if(r[0]==p[0]&&r[1]==p[1]){
        printf("finish\n");
        printf("%d\n",fcount+2);
    } else {
        PlusPlus(s,x,z,w);
    }
}

void main(void){
    int g,i,s,h;
    int p[2],q[2],r[2];
    fcount=0;
    printf("素数Sを入力してください。");
    scanf("%d",&s);
    printf("Pの要素を入力してください。\n");
    for(i=0;i<2;i++){
        printf("p[%d]=",i);
        scanf("%d",&p[i]);
        //printf("\n");
    }
    Plus(s,p,q);
    /*printf("P+P=[");
    for(i=0;i<2;i++){
        printf("%d,",q[i]);
    }
    printf("]\n");
    */
    PlusPlus(s,p,q,r);
    
    /*
    printf("P+2P=[");
    for(i=0;i<2;i++){
        printf("%d,",r[i]);
    }
    printf("]\n");
    */
}