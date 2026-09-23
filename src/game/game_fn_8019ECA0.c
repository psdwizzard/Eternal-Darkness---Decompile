typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Buffers { u8* vertices; u8* colors; u8* indices; } Buffers;
typedef struct Setup { u32 words[4]; } Setup;
typedef void (*DrawFn)(void*, void*, void*, void*, int);

extern Setup lbl_80607120;
extern u8 lbl_80607140[];
extern int lbl_8064D738;
extern float lbl_80650C68, lbl_80650C74, lbl_80650C78;
extern void fn_8018D788(int, void*, Buffers*, u16);
extern void fn_8018D020(void*, float, float, float, float, float);
extern void fn_80211484(float (*)[3][4], float, float, float);
extern void fn_80211268(float (*)[3][4], float, int);
extern void fn_80210FDC(float (*)[3][4], float (*)[3][4], float (*)[3][4]);
extern int fn_801ED57C(int);
extern void DCFlushRange(void*, u32);
extern void fn_8018D0D0(void*, void*, int);
extern void fn_8019EF50(void*, void*, void*, void*, int);
extern void fn_8019EFAC(void*, void*, void*, void*, int);

void fn_8019ECA0(u8* obj)
{
    Setup setup = lbl_80607120;
    Buffers buffers;
    float first[3][4];
    float second[3][4];
    u8* entry;
    u8* color;
    u8* fields;
    int count;
    int offset;
    int matrix_offset;
    int i;
    int j;
    int saved;
    DrawFn draw;

    fields = obj + 0x8C;
    fn_8018D788(lbl_8064D738, obj, &buffers, *(u16*)((u8*)&setup + 2));
    entry = *(u8**)(obj + 0x4C);
    count = obj[1];
    color = buffers.indices;
    draw = fn_8019EF50;
    if (*(int*)fields == 0)
        draw = fn_8019EFAC;
    for (i = matrix_offset = offset = 0; i < count; i++) {
        int radius = entry[0x21];
        fn_8018D020(buffers.vertices + offset,
                    (float)(*(s16*)(entry + 0x0A) - radius),
                    (float)(*(s16*)(entry + 0x0C) + radius),
                    (float)(*(s16*)(entry + 0x0A) + radius),
                    (float)(*(s16*)(entry + 0x0C) - radius),
                    (float)*(s16*)(obj + 0x14));
        for (j = 0; j < entry[0x20]; j++, color += 4)
            color[3] = entry[0x2B];
        fn_80211484(&first, lbl_80650C74, lbl_80650C74, lbl_80650C68);
        fn_80211268((float (*)[3][4])(lbl_80607140 + lbl_8064D738 * 0x180 + matrix_offset),
                    *(float*)(fields + 0x30 + i * 4), 90);
        fn_80210FDC((float (*)[3][4])(lbl_80607140 + lbl_8064D738 * 0x180 + matrix_offset),
                    &first, &second);
        fn_80211484(&first, lbl_80650C78, lbl_80650C78, lbl_80650C68);
        fn_80210FDC(&first, &second,
                    (float (*)[3][4])(lbl_80607140 + lbl_8064D738 * 0x180 + matrix_offset));
        entry += 0x38;
        offset += 0x18;
        matrix_offset += 0x30;
    }
    saved = fn_801ED57C(0);
    DCFlushRange(lbl_80607140 + lbl_8064D738 * 0x180, 0x180);
    DCFlushRange(buffers.vertices, *(u16*)((u8*)&setup + 0xA));
    DCFlushRange(buffers.colors, *(u16*)((u8*)&setup + 0xE));
    DCFlushRange(buffers.indices, *(u16*)((u8*)&setup + 0xC));
    fn_8018D0D0(obj, obj + 0x5C, *(s16*)(obj + 0x0E));
    draw(buffers.vertices, buffers.colors, buffers.indices,
         lbl_80607140 + lbl_8064D738 * 0x180, count);
    fn_801ED57C(saved);
}
