typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

extern u8 lbl_80607120[];
extern int lbl_8064D738;

void fn_8018D788(int index, void* object, void** output, u16 value);
void fn_8018E504(void* entry, void* channels);
void fn_8018E230(void* entry, void* alpha, int type, int value, int count,
                 int stride);
void fn_8018E8B8(void* channels, int value, int channel);
void fn_80198420(void* values, void* entries, u8 count, void* entry, u8 value);
void fn_80198724(void* state, void* entry, u8 count);

int fn_80196B10(u8* object)
{
    void* output;
    u8 count;
    int tick;
    u8* state;
    int i;
    u8* entry;
    int period;

    state = object + 0xd4;
    entry = *(u8**)(object + 0x4c);
    fn_8018D788(lbl_8064D738, object, &output,
                *(u16*)(lbl_80607120 + 2));

    period = *(u16*)(object + 0xc) + 1;
    tick = *(u16*)(object + 0xa);
    count = object[1];
    tick %= period;
    *(u16*)(object + 0xa) = *(u16*)(object + 0xa) + 1;

    if (object[0xa4] != 0) {
        for (i = 0; i < count; entry += 0x38, i++) {
            if (entry[0] != 0) {
                fn_8018E504(entry, entry + 0x20);
            } else if (tick == *(u16*)(entry + 8)) {
                fn_8018E230(entry, entry + 0x2b, object[0xa4], entry[2],
                             object[4], entry[3]);
                fn_8018E8B8(entry + 0x20, entry[2], 0);
                fn_8018E8B8(entry + 0x20, entry[2], 1);
            }
        }
    }

    if ((tick & object[0x8e]) == 0) {
        int entry_count = object[1];
        fn_80198420(object + 0x10, *(void**)(object + 0x4c), entry_count, output,
                     object[0x8c]);
        if ((tick & 1) == 0) {
            object[0x8c] += object[0xa1];
            if (object[0x8c] > object[0x8d]) {
                object[0x8c] = object[0xa1];
            }
        }
    }

    if (*(u16*)(state + 0xc) & 1) {
        fn_80198724(state, output, (u8)(object[1] >> 1));
        *(u16*)(state + 0xc) &= ~1;
    }

    if (!(object[0xa5] & 0x20) && (object[0xa5] & 1)) {
        object[0xa5] &= ~1;
        *(u16*)(object + 0xa) = 0;
        tick = 0;
        *(u16*)(object + 0xc) = 0xff;
        *(s8*)(object + 4) = -1;
        object[0xa4] = 1;
        entry = *(u8**)(object + 0x4c);
        for (i = 0; i < count; entry += 0x38, i++) {
            entry[0] = 0;
            entry[2] = entry[0x2b];
            entry[3] = 0;
        }
        object[0xa5] |= 0x20;
    }

    if (!(object[0xa5] & 1) && tick >= *(u16*)(object + 0xc)) {
        *(u16*)(object + 0x22) = 8;
    }
    return 0;
}
