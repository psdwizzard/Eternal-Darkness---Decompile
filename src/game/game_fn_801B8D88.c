typedef unsigned char u8;
typedef unsigned int u32;

extern void fn_801CE2B8(void);
extern void fn_801CE280(void);
extern u32 fn_801B7E84(u32, u8, u8);

u32 fn_801B8D88(u32 voice_id, u8 control, u8 value)
{
    u32 result;

    fn_801CE2B8();
    result = fn_801B7E84(voice_id, control, value);
    fn_801CE280();
    return result;
}
