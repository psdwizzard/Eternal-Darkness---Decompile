/* fn_802224EC (0x802224EC, 504 bytes): lays out sub-buffer offsets for a
 * resource descriptor based on its format bits. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

typedef struct Desc {
    u8 pad0[0x7];
    u8 flags;           /* 0x07 */
    u8 pad8[0x2C - 0x8];
    u32 base;           /* 0x2C */
    u16 chanBits;       /* 0x30 */
} Desc;

typedef struct Layout {
    u8 pad0[0x2E];
    u8 unk2E;           /* 0x2E */
    u8 pad2F[0x34 - 0x2F];
    u16 unk34;          /* 0x34 */
    u16 unk36;          /* 0x36 */
    u8 pad38[0x3C - 0x38];
    s32 unk3C;          /* 0x3C */
    s32 unk40;          /* 0x40 */
    s32 chan[8];        /* 0x44 */
    s32 unk64;          /* 0x64 */
    s32 unk68;          /* 0x68 */
} Layout;

void fn_802224EC(Desc* desc, Layout* out) {
    s32 offset;
    s32 found;
    s32 i;

    if ((offset = desc->base) == 0xFFFFFFFF) {
        out->unk2E = 0;
        offset = 0;
        out->unk34 = 0;
        out->unk36 = 0;
    }
    found = 0;
    switch (desc->flags & 3) {
    case 1:
        out->unk3C = offset;
        out->unk40 = offset + 0xC00;
        offset += 0xE00;
        break;
    case 2:
        out->unk3C = offset;
        out->unk40 = -1;
        offset += 0x1800;
        break;
    default:
        out->unk3C = -1;
        out->unk40 = -1;
        break;
    }
    for (i = 0; i < 8; i++) {
        switch ((desc->chanBits >> (i * 2)) & 3) {
        case 1:
            out->chan[i] = offset;
            found = 1;
            offset += 0x400;
            break;
        case 2:
            out->chan[i] = offset;
            offset += 0x800;
            break;
        default:
            out->chan[i] = -1;
            break;
        }
    }
    if (found) {
        out->unk64 = offset;
        offset += 0x200;
    } else {
        out->unk64 = -1;
    }
    out->unk68 = offset;
}
