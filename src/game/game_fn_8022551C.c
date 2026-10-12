/* Set the format of one vertex attribute in a GX VAT, then mark it dirty. */
typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXData {
    u8 reserved0[0x1C];
    u32 vatA[8];
    u32 vatB[8];
    u32 vatC[8];
    u8 reserved7C[0x4F2 - 0x7C];
    u8 dirtyVAT;
    u8 reserved4F3;
    u32 dirtyState;
} GXData;

extern GXData *gx;

#define SET_FIELD(reg, width, shift, value) \
    ((reg) = ((reg) & ~(((1UL << (width)) - 1) << (shift))) | ((u32)(value) << (shift)))

void fn_8022551C(int vtxfmt, int attr, int count, int type, u8 frac)
{
    u32 *vatA = &gx->vatA[vtxfmt];
    u32 *vatB = &gx->vatB[vtxfmt];
    u32 *vatC = &gx->vatC[vtxfmt];

    switch (attr) {
    case 9: /* Position */
        SET_FIELD(*vatA, 1, 0, count);
        SET_FIELD(*vatA, 3, 1, type);
        SET_FIELD(*vatA, 5, 4, frac);
        break;
    case 10: /* Normal */
    case 25: /* Normal, binormal and tangent */
        SET_FIELD(*vatA, 3, 10, type);
        if (count == 2) {
            SET_FIELD(*vatA, 1, 9, 1);
            SET_FIELD(*vatA, 1, 31, 1);
        } else {
            SET_FIELD(*vatA, 1, 9, count);
            SET_FIELD(*vatA, 1, 31, 0);
        }
        break;
    case 11: /* Color 0 */
        SET_FIELD(*vatA, 1, 13, count);
        SET_FIELD(*vatA, 3, 14, type);
        break;
    case 12: /* Color 1 */
        SET_FIELD(*vatA, 1, 17, count);
        SET_FIELD(*vatA, 3, 18, type);
        break;
    case 13: /* Texture coordinate 0 */
        SET_FIELD(*vatA, 1, 21, count);
        SET_FIELD(*vatA, 3, 22, type);
        SET_FIELD(*vatA, 5, 25, frac);
        break;
    case 14: /* Texture coordinate 1 */
        SET_FIELD(*vatB, 1, 0, count);
        SET_FIELD(*vatB, 3, 1, type);
        SET_FIELD(*vatB, 5, 4, frac);
        break;
    case 15: /* Texture coordinate 2 */
        SET_FIELD(*vatB, 1, 9, count);
        SET_FIELD(*vatB, 3, 10, type);
        SET_FIELD(*vatB, 5, 13, frac);
        break;
    case 16: /* Texture coordinate 3 */
        SET_FIELD(*vatB, 1, 18, count);
        SET_FIELD(*vatB, 3, 19, type);
        SET_FIELD(*vatB, 5, 22, frac);
        break;
    case 17: /* Texture coordinate 4 */
        SET_FIELD(*vatB, 1, 27, count);
        SET_FIELD(*vatB, 3, 28, type);
        SET_FIELD(*vatC, 5, 0, frac);
        break;
    case 18: /* Texture coordinate 5 */
        SET_FIELD(*vatC, 1, 5, count);
        SET_FIELD(*vatC, 3, 6, type);
        SET_FIELD(*vatC, 5, 9, frac);
        break;
    case 19: /* Texture coordinate 6 */
        SET_FIELD(*vatC, 1, 14, count);
        SET_FIELD(*vatC, 3, 15, type);
        SET_FIELD(*vatC, 5, 18, frac);
        break;
    case 20: /* Texture coordinate 7 */
        SET_FIELD(*vatC, 1, 23, count);
        SET_FIELD(*vatC, 3, 24, type);
        SET_FIELD(*vatC, 5, 27, frac);
        break;
    }
    gx->dirtyState |= 0x10;
    gx->dirtyVAT |= (u8)(1 << (u8)vtxfmt);
}
