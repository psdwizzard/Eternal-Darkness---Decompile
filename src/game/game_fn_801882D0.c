typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

extern void* lbl_80606460[];
extern s32 lbl_8064D244;
extern s32 lbl_8064D248;

extern void qsort(void*, s32, s32, s32 (*)(const void*, const void*));
extern s32 fn_80188288(const void*, const void*);
extern void GXSetCullMode(s32);
extern void fn_8018812C(void*);

void fn_801882D0(void)
{
    int i;
    u8* object;
    s32 total = 0;
    u32 weight;

    qsort(lbl_80606460, lbl_8064D248, 4, fn_80188288);
    i = 0;
    while (lbl_8064D248 > 0) {
        object = lbl_80606460[i];
        weight = object[6];
        total += weight;
        if (total < lbl_8064D244 || weight >= 200) {
            GXSetCullMode(0);
            fn_8018812C(object);
        }
        ++i;
        --lbl_8064D248;
    }
    GXSetCullMode(1);
}
