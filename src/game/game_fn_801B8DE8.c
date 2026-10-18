typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void hwDisableIrq(void);
extern void hwEnableIrq(void);
extern u32 synthFXSetCtrl14(u32, u8, u16);

u32 sndFXCtrl14(u32 voice_id, u8 control, u16 value)
{
    u32 result;

    hwDisableIrq();
    result = synthFXSetCtrl14(voice_id, control, value);
    hwEnableIrq();
    return result;
}
