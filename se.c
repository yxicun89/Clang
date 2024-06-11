#include	<stdio.h>
#include        <stdlib.h>
#include        <string.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<netdb.h>
#include	<arpa/inet.h>
#include <fcntl.h>
#include	<unistd.h>
#include<linux/soundcard.h>
#define	MAXLINE		8192
#define	SERV_UDP_PORT	44100/* 穴埋め:使用するポート番号を定義する */
#define	Error		fprintf

/∗ TRUE and FALSE ∗/
#ifndef TRUE
#define TRUE (1)
#endif
#ifndef FALSE
#define FALSE (0)
#endif

 unsigned char buf[MAXLINE];
 char *Audio_dev = "/dev/dsp";
 int Audio_fd; /* file descriptor for audio device */
 char *program;

 void initialize(); /∗ i n i t i a l i z e を 定 義 ∗/

 main(argc, argv)
    int			argc;
    char		*argv[];
{
    int			n, sockfd, servlen, dummylen,cnt;
    struct sockaddr_in	serv_addr, cli_addr;
    struct hostent	*host;
    char		*hname;
    char		sendline[MAXLINE], recvline[MAXLINE + 1];
    struct addrinfo	hints, *res;
    struct in_addr	addr;
    
    program = argv[0];

    if (argc != 2) {
	Error(stderr, "Usage: %s servername\n", program);
	exit(1);
    }

    hname = argv[1];

    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;

    /* 穴埋め:引数で指定したサーバ情報を res に代入する */
    if(getaddrinfo(hname,NULL,&hints,&res )!=0){
        Error(stderr, "Usage: %s addrinfo  \n", program);
        exit(1);
    }

    /* serv_addr にサーバアドレスを設定する */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family	= AF_INET;
    addr.s_addr = ((struct sockaddr_in *)(res->ai_addr))->sin_addr.s_addr;
    serv_addr.sin_addr.s_addr	= inet_addr(inet_ntoa(addr));
    serv_addr.sin_port		= htons(SERV_UDP_PORT);
    
    /*socket*/
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd==-1){
        Error(stderr, "Usage: %s servername\n", program);
        exit(1);
    } 

    /* cli_addr にローカルアドレスを設定する */
    memset(&cli_addr, 0, sizeof(cli_addr));
    cli_addr.sin_family	= AF_INET;
    cli_addr.sin_addr.s_addr	= htonl(INADDR_ANY);
    cli_addr.sin_port		= htons(0);
    
    /* 穴埋め:bind() */
    if (bind(sockfd, (struct sockaddr *) &cli_addr, sizeof(cli_addr)) == -1) {
        Error(stderr, "Usage: %s servername\n", program);
        exit(1);
    
    initialize(); /∗ i n i t i a l i z e ( ) 実 行 ∗/

 while ((cnt = read(Audio_fd, (char *)buf, sizeof (buf))) > 0) {

int send = sendto(sockfd,buf,cnt,0,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
        if(send == -1){
            Error(stderr, "Usage: %s servername\n", program);
            exit(1);
        }
 }
 close(sockfd);
 close(Audio_fd);
 exit(0);
 }

 void initialize()

 {
 int fmt = AFMT_S16_LE;
 int freq = 44100;
 int channel = 1;

 int bit;
 int i;
 int fragarg;


 if ( ( Audio_fd = open( Audio_dev, O_RDONLY ) ) == -1 ) {
 Error(stderr, "%s: audio device open error\n", program);
 exit(1);
 }

 for ( i = 0, bit = 1; i <= 65535; bit <<= 1, i ++ ) {
 if ( MAXLINE < bit ) {
 i = ( i == 0 ) ? 0 : i - 1;
 break;
 }
 }

 fragarg = ( 0x7fff << 16 ) | i;

 if ( ioctl( Audio_fd, SNDCTL_DSP_SETFRAGMENT, &fragarg )== -1 ) {
 Error(stderr,
 "%s initialize error: ioctl( SNDCTL_DSP_SETFRAGMENT )\n",program);
 close( Audio_fd );
 exit(1);
 }
 if ( ioctl( Audio_fd, SOUND_PCM_SETFMT, &fmt ) == -1 ) {
 Error(stderr, "
 %s initialize error: ioctl( SOUND_PCM_SETFMT )\n",program);
 close( Audio_fd );
 exit(1);
 }

 if ( ioctl( Audio_fd, SOUND_PCM_WRITE_CHANNELS, &channel ) == -1 ) {
 Error(stderr,
 "%s initialize error: ioctl( SOUND_PCM_WRITE_CHANNELS )\n",program);

 close( Audio_fd );
 exit(1);
 }

 if ( ioctl( Audio_fd, SOUND_PCM_WRITE_RATE, &freq ) == -1 ) {
 Error(stderr,
 "%s initialize error: ioctl( SOUND_PCM_WRITE_RATE )\n",program);
 close( Audio_fd );
 exit(1);
 }
}
