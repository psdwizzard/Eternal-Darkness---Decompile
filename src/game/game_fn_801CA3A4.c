typedef unsigned char u8;

extern u8 sndActive;

extern void hwExit(void);
extern void dataExit(void);
extern void s3dExit(void);
extern void synthExit(void);

void sndQuit(void)
{
    hwExit();
    dataExit();
    s3dExit();
    synthExit();
    sndActive = 0;
}
