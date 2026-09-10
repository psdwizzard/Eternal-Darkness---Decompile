typedef unsigned char u8;
typedef short s16;
typedef int s32;

typedef struct FirstEntry {
    u8 pad_00[0x19];
    u8 kind;
    u8 pad_1A[2];
    s16 id;
    u8 pad_1E[0xA];
} FirstEntry;

typedef struct SecondEntry {
    u8 pad_00[8];
    s16 kind;
    u8 pad_0A[4];
    s16 id;
    u8 pad_10[8];
} SecondEntry;

extern const char lbl_8023BEF8[];
extern FirstEntry lbl_80241DE8[];
extern SecondEntry lbl_802417D0[];
extern void* lbl_8024E388[];
extern int fn_8016A598(void*);
extern void fn_80163BB4(void*, const char*, ...);
extern void fn_801E7974(void*, int);

s32 fn_800169FC(void* script)
{
    if (fn_8016A598(script) != 0) {
        fn_80163BB4(script, lbl_8023BEF8, 0, fn_8016A598(script));
        return 0;
    }

    {
        s32 i;
        for (i = 0; i < 173; i++) {
            FirstEntry* first = &lbl_80241DE8[i];
            if (first->id != -1) {
                u8 kind = first->kind;
                if (kind == 0) {
                    fn_801E7974(lbl_8024E388[0], first->id);
                } else {
                    fn_801E7974(lbl_8024E388[kind - 1], first->id);
                }
            }
        }
    }

    {
        s32 i;
        for (i = 0; i < 51; i++) {
            SecondEntry* second = &lbl_802417D0[i];
            if (second->id != -1) {
                s32 kind = (u8)second->kind;
                if (kind == 0xFF) {
                    fn_801E7974(lbl_8024E388[0], second->id);
                } else {
                    fn_801E7974(lbl_8024E388[kind - 1], second->id);
                }
            }
        }
    }

    return 0;
}
