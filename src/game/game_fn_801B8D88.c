typedef unsigned char u8;
typedef unsigned int u32;

extern void hwDisableIrq(void);
extern void hwEnableIrq(void);
extern u32 synthFXSetCtrl(u32, u8, u8);

u32 sndFXCtrl(u32 voice_id, u8 control, u8 value)
{
    u32 result;

    hwDisableIrq();
    result = synthFXSetCtrl(voice_id, control, value);
    hwEnableIrq();
    return result;
}
