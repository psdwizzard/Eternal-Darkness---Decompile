typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

extern int lbl_8064D18C;
extern int fn_80180430(void*, u8);
extern void fn_80180518(void*, u8, int);
extern void fn_8017E1E4(void*, void*, u8, int);
extern void fn_8018E230();
extern u8 fn_8018E26C(void*, void*);
extern int fn_8019DCF4(void*);
extern int fn_8019DD64(void*);
extern void fn_8019DEFC(void*);
extern s16* fn_8017FDE4(void*);
extern s16* fn_8017FDEC(void*);
extern void fn_8017FE14(void*, void*);
extern void fn_8019DDBC(void);
extern void* fn_8015E780(void);

int fn_8019DA3C(u8* object)
{
    s16* timer;
    int offset;
    u8* state = object + 0x8C;
    u8* entry = *(u8**)(object + 0x4C);
    int count = object[1];
    int i;

    if (object[0x102] == 0) {
        timer = (s16*)state;
        i = 0;
        offset = 0;
        for (; i < count; entry += 0x38, offset += 0x38, i++, timer++) {
            if (entry[0] == 1 && !fn_8018E26C(entry, entry + 0x2B) &&
                entry[0x2B] == 0 && entry[1] == 0) {
                timer[6] = 0;
            }
            if (fn_80180430(object + 0x24, (u8)i)) {
                fn_8017E1E4(entry + 0xA, entry + 0x10, state[0x73], *(s8*)(state + 0x74));
                if (entry[0] == 0 && timer[6] >= *(u16*)(entry + 8))
                    fn_8018E230(entry, entry + 0x2B, 1, entry[0x2B], object[4], 0);
            }
            if (fn_8019DCF4(object)) {
                *(u16*)(state + 8) = 1;
                if (timer[6] == 0)
                    timer[6]--;
            } else if (*(u16*)(state + 8) == 1) {
                fn_8019DEFC(object);
                *(u16*)(state + 8) = 0;
            }
            if (timer[6] == 0) {
                if ((s8)state[i + 0x4F] != 0) {
                    timer[6] = fn_8019DD64(object) - state[0x71] - 1;
                    state[i + 0x4F] = 0;
                } else {
                    s16* first;
                    s16* second;
                    u8* current = *(u8**)(object + 0x4C) + offset;
                    first = fn_8017FDE4(object);
                    second = fn_8017FDEC(object);
                    *(s16*)(current + 0xA) = first[0];
                    *(s16*)(current + 0xC) = first[1];
                    *(s16*)(current + 0xE) = first[2];
                    *(s16*)(current + 0x10) = second[0];
                    *(s16*)(current + 0x12) = second[1];
                    *(s16*)(current + 0x14) = second[2];
                    fn_80180518(object + 0x24, (u8)i, 1);
                    fn_8018E230(entry, entry + 0x2B, 1, 0, (s8)state[0x6F], object[2]);
                }
            }
            timer[6]++;
        }
    }
    (*(u16*)(object + 0xA))++;
    if (*(u16*)(object + 0xA) == 0x7FFF) {
        *(u16*)(object + 0xA) = 0;
        *(u32*)(object + 0x44) = 0;
    }
    if (state[0x75] && lbl_8064D18C != *(int*)(object + 0x38))
        *(u16*)(object + 0x22) = 8;
    if (*(u16*)(object + 0xA) >= *(u16*)(object + 0xC) && *(u16*)(object + 0xC))
        fn_8017FE14(object, fn_8019DDBC);
    if (state[0x4E] && *(void**)state != fn_8015E780())
        *(u16*)(object + 0x22) = 8;
    return 0;
}
