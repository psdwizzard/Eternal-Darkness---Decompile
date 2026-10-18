typedef unsigned char u8;
typedef unsigned int u32;

extern u32 synthAuxACallback[];
extern u32 synthAuxBCallback[];
extern u8 synthITDDefault[];
extern u8 synthAuxAMIDI;
extern u8 synthAuxBMIDI;
extern void hwDisableIrq(void);
extern void hwEnableIrq(void);
extern void hwActivateStudio(int, int, int);

void synthActivateStudio(int arg0, int arg1, int arg2)
{
    hwDisableIrq();
    {
        int zero;
        u8 index;
        index = (u8)arg0;
        zero = 0;
        synthAuxACallback[index] = zero;
        synthAuxBCallback[index] = zero;
        (&synthAuxAMIDI)[index] = 0xFF;
        (&synthAuxBMIDI)[index] = 0xFF;
        synthITDDefault[index * 2 + 1] = zero;
        synthITDDefault[index * 2] = zero;
    }
    hwActivateStudio(arg0, arg1, arg2);
    hwEnableIrq();
}
