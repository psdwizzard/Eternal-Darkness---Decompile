typedef signed short s16;
typedef signed int s32;
typedef unsigned char u8;

extern u8 lbl_80639260[];
extern s32 lbl_8064D634;
extern s32 lbl_8064D63C;
extern s32 lbl_8064D680;
extern s32 lbl_8064D684;
extern s32 lbl_8064D6B0;

typedef struct Record16 { s32 value[4]; } Record16;
typedef struct Record24 { s32 pad0; s32 a; s32 b; s32 c; u8 flag; u8 pad11[3]; s32 d; } Record24;
typedef struct Record8 { s32 a; s32 b; } Record8;

void fn_801ED118(void)
{
    s16* half = (s16*)(lbl_80639260 + 0x21D8);
    s32* word = (s32*)(lbl_80639260 + 0x21F8);
    s32* a = (s32*)(lbl_80639260 + 0x2238);
    s32* z = (s32*)(lbl_80639260 + 0x2278);
    s32* b = (s32*)(lbl_80639260 + 0x22B8);
    s32* c = (s32*)(lbl_80639260 + 0x22F8);
    s32* d = (s32*)(lbl_80639260 + 0x2338);
    s32* e = (s32*)(lbl_80639260 + 0x2378);
    Record16* r16a = (Record16*)(lbl_80639260 + 0x23B8);
    Record16* r16b = (Record16*)(lbl_80639260 + 0x24B8);
    Record24* r24a = (Record24*)(lbl_80639260 + 0x25B8);
    Record24* r24b = (Record24*)(lbl_80639260 + 0x2738);
    Record8* r8 = (Record8*)(lbl_80639260 + 0x28B8);
    s32* f = (s32*)(lbl_80639260 + 0x2938);
    s32* g = (s32*)(lbl_80639260 + 0x2978);
    s32* h = (s32*)(lbl_80639260 + 0x29B8);
    s32* tail = (s32*)(lbl_80639260 + 0x29F8);
    s32 i;

    for (i = 0; i < 11; i++) {
        half[i] = -1;
        word[i] = -1;
    }
    lbl_8064D634 = -1;
    *(s32*)(lbl_80639260 + 0x21F0) = 0;
    lbl_8064D63C = 0;

    for (i = 0; i < 16; i++) {
        a[i] = b[i] = c[i] = d[i] = e[i] = f[i] = g[i] = h[i] = -1;
        z[i] = 0;
        r16a[i].value[0] = r16a[i].value[1] = r16a[i].value[2] = r16a[i].value[3] = -1;
        r16b[i].value[0] = r16b[i].value[1] = r16b[i].value[2] = r16b[i].value[3] = -1;
        r24a[i].a = r24a[i].b = r24a[i].c = r24a[i].d = -1;
        r24a[i].flag = 255;
        r24b[i].a = r24b[i].b = r24b[i].c = r24b[i].d = -1;
        r24b[i].flag = 255;
        r8[i].a = r8[i].b = -1;
    }
    for (i = 0; i < 16; i++) {
        tail[i] = -1;
    }
    lbl_8064D6B0 = -1;
    lbl_8064D684 = 0;
    lbl_8064D680 = 0;
}
