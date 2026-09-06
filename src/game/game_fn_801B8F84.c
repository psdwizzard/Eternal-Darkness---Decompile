typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void fn_801CE2B8(void);
extern void fn_801CE280(void);
extern void fn_801B8164(u8, u16, u8, u8, u32);

void fn_801B8F84(u8 volume, u16 time, u8 volume_group)
{
    fn_801CE2B8();
    fn_801B8164(volume, time, volume_group, 0, -1);
    fn_801CE280();
}
