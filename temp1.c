/* ʳشü¸
   ¸7 (2-4) ̿ü¸
   temp1.c
   2020 */

#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>
#include        <sys/types.h>
#include        <sys/socket.h>
#include        <netinet/in.h>
#include        <netdb.h>
#include        <arpa/inet.h>
#include        <unistd.h>

#define MAXLINE         512
#define SERV_UDP_PORT   44910/* :Ѥݡֹ�� */
#define Error           fprintf

main(argc, argv)
    int                 argc;
    char                *argv[];
{
    int                 n, sockfd, servlen, dummylen;
    struct sockaddr_in  serv_addr, cli_addr;
    struct hostent      *host;
    char                *hname;
    char                *program;
    char                sendline[MAXLINE], recvline[MAXLINE + 1];
    struct addrinfo     hints, *res;
    struct in_addr      addr;

    program = argv[0];

    if (argc != 2) {
        Error(stderr, "Usage: %s servername\n", program);
        exit(1);
    }

    hname = argv[1];

    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;

    /* :ǻꤷо res  */
    int getinfo = getaddrinfo(hname,NULL,*hints,*res);
    if(getinfo!=0){
        Error(stderr, "Usage: %s servername\n", program);
        exit(1);
    }

    /* serv_addr ˥Хɥ쥹ꤹ */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family        = AF_INET;
    addr.s_addr = ((struct sockaddr_in *)(res->ai_addr))->sin_addr.s_addr;
    serv_addr.sin_addr.s_addr   = inet_addr(inet_ntoa(addr));
    serv_addr.sin_port          = htons(SERV_UDP_PORT);

    /* :socket() */
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd==-1){
        Error(stderr, "Usage: %s servername\n", program);
        exit(1);
    }

    /* cli_addr ˥��륢ɥ쥹ꤹ */
    memset(&cli_addr, 0, sizeof(cli_addr));
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_addr.s_addr    = htonl(INADDR_ANY);
    cli_addr.sin_port           = htons(0);

    /* :bind() */
    if (bind(sockfd, (struct sockaddr *) &cli_addr, sizeof(cli_addr)) == -1) {
        Error(stderr, "Usage: %s servername\n", program);
        exit(1);
    }


    /* main loop */
    while(fgets(sendline, MAXLINE, stdin) != NULL) {
        n = strlen(sendline);

        /* :롼ν */
        int send = sendto(sockfd,sendline,n,0,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
        if(send == -1){
            Error(stderr, "Usage: %s servername\n", program);
            exit(1);
        }

        int recv = recvfrom(sockfd,recvline,MAXLINE + 1,(struct sockaddr *) &cli_addr,dummylen);
        if(recv == -1){
            Error(stderr, "Usage: %s servername\n", program);
            exit(1);
        }
        recvline[n] = 0;
        fputs(recvline, stdout);
    }
    close(sockfd);
    exit(0);

}