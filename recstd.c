/*
* recstd
* ^^cd^^82 Wo^^cd^^82^^c9^^8fo^^cd^^82
* _CNg > g^^c4^^83t@C^^c9^^95^^db^^91 邱　
* 2010.12
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/soundcard.h>

#define MAXLINE 8192
#define Error (void) fprintf

/* TRUE and FALSE */
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

 void initialize();

 int main(int argc, char** argv)
 {
 int optind;
 int c, i, cnt;
 int ofd;


 program = argv[0]; 
 ofd = fileno(stdout); // fileno(stdout) = 1 

 /* initialize audio device */
 initialize(); // I[fBI^^cc^^8f

 while ((cnt = read(Audio_fd, (char *)buf, sizeof (buf))) > 0) {  /*readでbufに音声データを格納*/


 /* write */
 if (write(ofd, (char *)buf, cnt) < 0) { /*writeでofd(stdout?)にbufの値を格納*/
 Error(stderr, "%s: write error\n", program);
 exit(1);
 }
 }
 close(Audio_fd);

 exit(0);
 }

 /*
 * initialize auidio device
 */
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