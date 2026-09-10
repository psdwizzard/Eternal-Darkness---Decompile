typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

#pragma pack(4)
typedef struct Voice {
    u8 pad_000[0x114];
    u64 flags_114;
    u8 pad_11C[0x2E8];
} Voice;
#pragma pack()

typedef struct AudioState {
    u8 pad_000[0x210];
    u8 voice_count;
} AudioState;

extern u32 lbl_8064D3CC;
extern Voice *lbl_8064D3D0;
extern AudioState lbl_80619C20;
extern void fn_801CD418(void);
extern void fn_801BA15C(void);

void fn_801B9078(int arg0)
{
    u32 old_flags = lbl_8064D3CC;
    switch (arg0) {
    case 0:
        lbl_8064D3CC |= 1;
        lbl_8064D3CC &= ~2;
        fn_801CD418();
        break;
    case 1:
        lbl_8064D3CC &= ~1;
        lbl_8064D3CC &= ~2;
        fn_801CD418();
        break;
    case 2:
        lbl_8064D3CC &= ~1;
        lbl_8064D3CC |= 2;
        fn_801CD418();
        break;
    }
    if (old_flags != lbl_8064D3CC) {
        int offset;
        u32 i;
        i = 0;
        offset = 0;
        while (i < lbl_80619C20.voice_count) {
            ((Voice *)((u8 *)lbl_8064D3D0 + offset))->flags_114 |= 0x0000200000000000ULL;
            offset += 0x404;
            i++;
        }
        fn_801BA15C();
    }
}
