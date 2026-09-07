typedef signed short s16;
typedef unsigned int u32;

extern void fn_80144C40(void);

void fn_801E5D38(s16 value, void* object)
{
    u32* flags;

    if (object != 0) {
        flags = (u32*)((char*)object + 0x10);
        *flags &= ~0x1400;
        if (value > 0) {
            *flags |= 0x400;
        } else {
            *flags |= 0x1000;
        }
        fn_80144C40();
    }
}
