typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;

typedef struct {
    u32 mode;
    u16 x;
    u16 reserved6;
    u16 y, height, width, depth;
    u8 reserved10[4];
    u32 flags;
    u8 data[0xC];
} DisplayInput;

typedef struct {
    u8 pad0[0x32];
    u16 height;
    u16 width;
    u8 pad36[0xBA];
} DisplayState;

typedef struct {
    u8 bytes[0x24];
} DisplayInfo;

extern s32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(s32);
extern void OSReport(const char *, ...);
extern void *fn_80216C24(s32);
extern void fn_80217378(void *, void *, void *, void *, void *);
extern void fn_8021764C(u16, u16, u8, u16, u16, u16, u16, u16, u32);
extern char lbl_802FE710[];
extern volatile DisplayState lbl_80641AC8;
extern volatile u32 lbl_8064DA78, lbl_8064DA80, lbl_8064DA88, lbl_8064DA8C;
extern volatile u32 lbl_8064DAA8, lbl_8064DAAC;
extern volatile s16 lbl_8064DA7C, lbl_8064DA7E;

#define GX_SET_A(mask) do { u32 gxA = lbl_8064DA88; u32 gxB = lbl_8064DA8C; lbl_8064DA8C = gxB; lbl_8064DA88 = gxA | (mask); } while (0)
#define GX_SET_B(mask) do { u32 gxA = lbl_8064DA88; u32 gxB = lbl_8064DA8C; lbl_8064DA8C = gxB | (mask); lbl_8064DA88 = gxA; } while (0)

void fn_802177EC(DisplayInput *in) {
    char *strings = lbl_802FE710;
    volatile DisplayState *s = &lbl_80641AC8;
    register s32 interruptState;
    u32 mode, scan, refreshRate, height, width;
    u32 shouldAdjust, flagsA, flagsB;
    s32 scale;
    s32 left, top, delta, right, bottom;
    DisplayInfo *info;
    u16 tmp;
    s16 infoLines;
    u8 *out = (u8 *)s;
    register volatile u16 *pF2, *pF4, *pF6, *pFA, *pFC;
    register volatile u16 *p102, *p106, *p108, *p10A, *p10C;
    register volatile u32 *p110, *p118, *p134;
    volatile u32 *pMode;

    interruptState = OSDisableInterrupts();
    mode = in->mode & 3;
    pMode = (volatile u32 *)(out + 0x114);
    if (*pMode != mode) {
        lbl_8064DA80 = 1;
        *pMode = mode;
    }
    scan = in->mode >> 2;
    refreshRate = *(volatile u32 *)0x800000CC;
    if (scan == 4 && lbl_8064DAAC == 0) {
        lbl_8064DAAC = 1;
        OSReport(strings + 0x1BC);
        OSReport(strings + 0x1E8);
        OSReport(strings + 0x214);
        OSReport(strings + 0x240);
        OSReport(strings + 0x26C);
        OSReport(strings + 0x298);
        OSReport(strings + 0x1BC);
    }
    if (scan == 0 || scan == 2) *(volatile u32 *)(out + 0x118) = refreshRate;
    else *(volatile u32 *)(out + 0x118) = scan;

    *(volatile u16 *)(out + 0xF0) = in->height;
    *(volatile u16 *)(out + 0xF2) = *pMode == 1 ? (u16)(in->width * 2) & 0xFFFE : in->width;
    pF2 = (volatile u16 *)(out + 0xF2);
    *(volatile u16 *)(out + 0xF4) = in->depth;
    pF4 = (volatile u16 *)(out + 0xF4);
    p102 = (volatile u16 *)(out + 0x102);
    p110 = (volatile u32 *)(out + 0x110);
    p10A = (volatile u16 *)(out + 0x10A);
    p10C = (volatile u16 *)(out + 0x10C);
    p106 = (volatile u16 *)(out + 0x106);
    *(volatile u16 *)(out + 0x102) = in->x;
    p108 = (volatile u16 *)(out + 0x108);
    *(volatile u16 *)(out + 0x104) = in->y;
    *(volatile u32 *)(out + 0x110) = in->flags;
    *(volatile u16 *)(out + 0x10A) = *(volatile u16 *)(out + 0x102);
    *(volatile u16 *)(out + 0x10C) = *(volatile u16 *)(out + 0x104);
    *(volatile u16 *)(out + 0x106) = 0;
    *(volatile u16 *)(out + 0x108) = 0;
    if (*pMode == 2) tmp = *p10C;
    else if (*pMode == 3) tmp = *p10C;
    else if (*p110 == 0) tmp = (u16)(*p10C * 2);
    else tmp = *p10C;
    *(volatile u16 *)(out + 0xF6) = tmp;
    pF6 = (volatile u16 *)(out + 0xF6);
    pFA = (volatile u16 *)(out + 0xFA);
    pFC = (volatile u16 *)(out + 0xFC);
    p118 = (volatile u32 *)(out + 0x118);
    p134 = (volatile u32 *)(out + 0x134);
    *p134 = *pMode == 3;
    info = fn_80216C24(*p118 * 4 + *pMode);
    *(volatile DisplayInfo **)(out + 0x144) = info;

    top = (s16)*(volatile u16 *)(out + 0xF0) + lbl_8064DA7C;
    height = *pF4;
    left = (s16)*pF2;
    width = *pF6;
    right = 0x2D0 - (s16)height;
    if (top > (s32)right) top = right;
    else if (top < 0) top = 0;
    *(volatile u16 *)(out + 0xF8) = top;
    scale = *p110 == 0 ? 2 : 1;
    delta = (s16)left + lbl_8064DA7E;
    bottom = delta > (left & 1) ? delta : (left & 1);
    *pFA = bottom;
    delta = (s16)*(u16 *)(info->bytes + 2) * 2 - (left & 1);
    right = (s16)left + (s16)width + lbl_8064DA7E;
    *pFC = (u16)(width + ((s16)left + lbl_8064DA7E < (left & 1) ? (s16)left + lbl_8064DA7E - (left & 1) : 0) - (right - delta > 0 ? right - delta : 0));
    delta = (s16)left + lbl_8064DA7E - (left & 1);
    *(volatile u16 *)(out + 0xFE) = (s16)*p108 - (delta < 0 ? delta / scale : 0);
    *(volatile u16 *)(out + 0x100) = (u16)((s16)*p10C + ((delta < 0 ? delta : 0) / scale) - ((right - ((s16)*(u16 *)(info->bytes + 2) * 2 - (left & 1)) > 0 ? right - ((s16)*(u16 *)(info->bytes + 2) * 2 - (left & 1)) : 0) / scale));

    if (lbl_8064DA78 == 0) *p118 = 3;
    infoLines = *(u16 *)(info->bytes + 0x18);
    *(volatile u16 *)(out + 0x32) = ((infoLines % 2 != 0) ? *(u16 *)(info->bytes + 0x1A) : 0) + 1;
    tmp = (infoLines / 2) + 1;
    tmp |= 0x1000;
    GX_SET_A(0x40);
    *(volatile u16 *)(out + 0x30) = tmp;
    GX_SET_A(0x80);
    tmp = *(volatile u16 *)(out + 2) & 0xFFF7;
    if (*pMode == 2 || *pMode == 3) tmp = (tmp & ~4) | 4;
    else tmp = (tmp & ~4) | (*pMode << 2);
    tmp = (tmp & ~8) | ((*p134) << 3);
    if (*p118 != 4 && *p118 != 5) tmp |= *p118 << 8;
    *(volatile u16 *)(out + 2) = tmp;
    GX_SET_A(0x40000000);
    tmp = *(volatile u16 *)(out + 0x6C) & 0xFFFE;
    if (in->mode == 2 || in->mode == 3) tmp |= 1;
    *(volatile u16 *)(out + 0x6C) = tmp;
    GX_SET_B(0x200);
    left = *p134 ? *p10A * 2 : *p10A;
    height = *pF4;
    if (left < (s32)height) {
        *(volatile u16 *)(out + 0x4A) = ((height + ((left << 8) - 1)) / height) | 0x1000;
        *(volatile u16 *)(out + 0x70) = left;
        GX_SET_B(0x04000000);
        GX_SET_B(0x80);
    } else {
        *(volatile u16 *)(out + 0x4A) = 0x100;
        GX_SET_B(0x04000000);
    }
    *(volatile u16 *)(out + 6) = *(u16 *)(info->bytes + 0x1A);
    GX_SET_A(0x10000000);
    *(volatile u16 *)(out + 4) = (info->bytes[0x1D] << 8) | info->bytes[0x1E];
    GX_SET_A(0x20000000);
    left = (u16)info->bytes[0x1F] + (u16)*(volatile u16 *)(out + 0xF8) - 0x28;
    *(volatile u16 *)(out + 0xA) = info->bytes[0x1C] | ((left << 7) & 0xFF80);
    GX_SET_A(0x04000000);
    *(volatile u16 *)(out + 8) = (left >> 9) | ((((u16)*(u16 *)(info->bytes + 0x20) + (u16)*(volatile u16 *)(out + 0xF8) + 0x28) - (0x2D0 - height)) * 2);
    GX_SET_A(0x08000000);
    *(volatile u16 *)(out + 0x16) = info->bytes[0x0C] | (*(u16 *)(info->bytes + 0x10) << 5);
    GX_SET_A(0x00100000);
    *(volatile u16 *)(out + 0x14) = info->bytes[0x0E] | (*(u16 *)(info->bytes + 0x14) << 5);
    GX_SET_A(0x00200000);
    *(volatile u16 *)(out + 0x1A) = info->bytes[0x0D] | (*(u16 *)(info->bytes + 0x12) << 5);
    GX_SET_A(0x00040000);
    *(volatile u16 *)(out + 0x18) = info->bytes[0x0F] | (*(u16 *)(info->bytes + 0x16) << 5);
    GX_SET_A(0x00080000);

    out[0x11C] = (*p102 + 15) / 16;
    out[0x11D] = *p110 == 0 ? out[0x11C] : (out[0x11C] * 2) & 0xFE;
    out[0x12C] = *p106 & 15;
    out[0x11E] = (out[0x12C] + *p10A + 15) / 16;
    *(volatile u16 *)(out + 0x48) = out[0x11D] | (out[0x11E] << 8);
    flagsA = lbl_8064DA88;
    shouldAdjust = lbl_8064DAA8;
    flagsB = lbl_8064DA8C;
    lbl_8064DA8C = flagsB | 0x08000000;
    lbl_8064DA88 = flagsA;
    if (shouldAdjust) fn_80217378((void *)(out + 0xF0), (void *)(out + 0x124), (void *)(out + 0x128), (void *)(out + 0x13C), (void *)(out + 0x140));
    fn_8021764C(*pFA, *pFC, info->bytes[0], *(u16 *)(info->bytes + 2), *(u16 *)(info->bytes + 4), *(u16 *)(info->bytes + 6), *(u16 *)(info->bytes + 8), *(u16 *)(info->bytes + 0xA), *(volatile u32 *)(out + 0x130));
    OSRestoreInterrupts(interruptState);
}
