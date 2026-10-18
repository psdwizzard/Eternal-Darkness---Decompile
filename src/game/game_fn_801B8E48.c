extern void hwDisableIrq(void);
extern void hwEnableIrq(void);
extern int synthSendKeyOff(int);

int sndFXKeyOff(int arg0)
{
    int result;

    hwDisableIrq();
    result = synthSendKeyOff(arg0);
    hwEnableIrq();
    return result;
}
