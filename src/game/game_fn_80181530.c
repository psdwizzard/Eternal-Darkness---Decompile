typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern unsigned int rand(void);
extern void fn_8018E230(void*, void*, int, u8, u8, int);
extern void fn_8018E260(void*, u8, int);
extern void fn_801806D4(void*, u32*, int);
extern void fn_80180518(void*, u8, int);
extern u32 lbl_80650978;

void fn_80181530(u8* objectArg, u8* stateArg, int tick)
{
    u8* state = stateArg;
    u8* object = objectArg;
    u8 count = state[3];

    if (state[0] <= object[1] - count) {
        if (!(tick & *(u16*)(state + 0xA))) {
            int i;
            u8* entry = *(u8**)(object + 0x4C) + state[0] * 0x38;

            for (i = 0; i < count; entry += 0x38, i++) {
                if (state[4] == 4) {
                    u8 value = (rand() & 7) * 20;
                    fn_8018E230(entry, entry + 0x2B, 4, value, 10, 0xF0);
                    fn_8018E260(entry, 0xF0, 0x78);
                } else {
                    u32 value = lbl_80650978;
                    fn_801806D4(entry + 0x20, &value, 0);
                }
                fn_80180518(object + 0x24, state[0], 1);
                state[0]++;
            }
        }
        state[5] &= ~0x40;
    } else {
        state[5] |= 0x40;
    }
}
