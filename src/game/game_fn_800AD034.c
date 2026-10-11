typedef unsigned char u8;
typedef unsigned short u16;

extern int lbl_8064C958;
extern int lbl_8064D5A8;

extern void fn_801441C0(int kind, int priority, int duration);
extern void fn_801F74C8(int first, int second, int third);
extern int fn_801A9EF4(int low, int high);
extern int fn_801A98F4(int index, void *object);

void fn_800AD034(int variant, int mode, int state, u16 duration, unsigned int volume, int previousState)
{
    int sound;
    int now = lbl_8064D5A8;

    /* Clamp the low-byte volume, with a lower cap for recent events. */
    volume = ((u8)volume > 90U ? 90 : (u8)volume) & 0xFF;
    if (now < lbl_8064C958 + 90) {
        volume = (volume > 70U ? 70 : volume) & 0xFF;
    }
    lbl_8064C958 = now;
    fn_801441C0(1, 1, duration);

    if ((mode == 0 && previousState == 3) || (mode == 2 && state == 3)) {
        fn_801F74C8(15, 1, 5);
        switch (variant) {
        case 1: sound = 0x2A8; break;
        case 2: sound = 0x2A9; break;
        case 3: sound = 0x2AA; break;
        default: sound = 0x2A8; break;
        }
    } else {
        if (mode == 1) {
            fn_801F74C8(15, 1, 5);
        }
        switch (variant) {
        case 1: sound = fn_801A9EF4(0x2B9, 0x2BB) & 0xFFFF; break;
        case 2: sound = fn_801A9EF4(0x2BC, 0x2BE) & 0xFFFF; break;
        case 3: sound = fn_801A9EF4(0x2BF, 0x2C1) & 0xFFFF; break;
        default: sound = fn_801A9EF4(0x2B9, 0x2BB) & 0xFFFF; break;
        }
    }
    if ((u16)sound != 0 && (u8)volume != 0) {
        fn_801A98F4(sound, (void *)volume);
    }
}
