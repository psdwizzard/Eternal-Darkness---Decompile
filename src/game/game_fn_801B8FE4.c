typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void fn_801CE2B8(void);
extern void fn_801CE280(void);
extern void fn_801B8164(u8, u16, u8, u8, u32);

void fn_801B8FE4(u8 volume, u16 time, u8 music, u8 effects)
{
    fn_801CE2B8();
    if (music) {
        fn_801B8164(volume, time, 0x15, 0, -1);
    }
    if (effects) {
        fn_801B8164(volume, time, 0x16, 0, -1);
    }
    fn_801CE280();
}
