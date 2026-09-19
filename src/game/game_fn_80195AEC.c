typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern const float lbl_80650B70;

void fn_801871F0(u8*, u16*, s16*, int, int, int, int, int, int, int);
void fn_80187320(u8*, u16*, s16*, int, int, int, int, int, float, int);
void fn_80187488(u8*, u16*, s16*, int, int, int, s16*, s16*, int, int);
void fn_801875FC(u8*, u16*, s16*, int, int, int, s16*, s16*, int, int);

void fn_80195AEC(u8* object)
{
    u32 flags = *(u32*)(object + 0x108);
    u8 count = object[0x97] - 4;
    u16* flags0 = (u16*)(object + 0x9c);
    int end = ((*flags0 & 7) + 1);
    u8 kind = object[0x8f];
    u8 mode = object[0x98];
    u8* owner = *(u8**)(object + 0x4c);
    u16* flags1 = (u16*)(object + 0x9e);
    u16* flags2 = (u16*)(object + 0xa0);
    s16* bounds0 = (s16*)(object + 0xb4);
    s16* bounds1 = (s16*)(object + 0xce);
    s16* bounds2 = (s16*)(object + 0xe8);
    s16* starts = (s16*)(object + 0x10);

    if (flags & 0x8000) {
        if (flags & 0x32000) {
            if (flags & 0x10000) {
                fn_801875FC(owner + 0x38, flags0, bounds0, 0, 0, count,
                            starts, (s16*)(object + 0xa2), mode, end);
            } else {
                fn_80187320(owner + 0x38, flags0, bounds0, 0, 0, count,
                            starts[0], kind, *(float*)(object + 0x10c), end);
            }
            if (*(u32*)(object + 0x108) & 0x20000) {
                fn_801875FC(owner + 0x38, flags1, bounds1, 1, 0, count,
                            starts, (s16*)(object + 0xa2), mode, end);
            } else {
                fn_80187320(owner + 0x38, flags1, bounds1, 1, 0, count,
                            starts[1], kind, *(float*)(object + 0x110), end);
            }
            if (*(u32*)(object + 0x108) & 0x2000) {
                fn_801875FC(owner + 0x38, flags2, bounds2, 2, 0, count,
                            starts, (s16*)(object + 0xa2), mode, end);
            } else {
                fn_80187320(owner + 0x38, flags2, bounds2, 2, 0, count,
                            starts[2], kind, *(float*)(object + 0x114), end);
            }
        } else if (flags & 0x100) {
            int half = count >> 1;
            int rest;
            float step;
            int base;

            fn_80187320(owner + 0x38, flags0, bounds0, 0, 0, count,
                        starts[0], kind, *(float*)(object + 0x10c), end);
            fn_80187320(owner + 0x38, flags1, bounds1, 1, 0, count,
                        starts[1], kind, *(float*)(object + 0x110), end);
            step = lbl_80650B70 * *(float*)(object + 0x114);
            fn_80187320(owner + 0x38, flags2, bounds2, 2, 0, half,
                        starts[2], kind, step, end);
            rest = count - half;
            base = (int)((float)half * step + (float)starts[2]);
            fn_80187320(owner + 0x38 + half * 0x38, flags2, bounds2, 2,
                        half, count, base, kind,
                        *(float*)(object + 0x114) / (float)rest, end);
        } else if (flags & 0x400) {
            int half = count >> 1;
            int rest = count - half;
            float step;
            int base;
            u8* entry = owner + 0x38 + half * 0x38;

            step = lbl_80650B70 * *(float*)(object + 0x10c);
            fn_80187320(owner + 0x38, flags0, bounds0, 0, 0, half,
                        starts[0], kind, step, end);
            base = (int)((float)half * step + (float)starts[0]);
            fn_80187320(entry, flags0, bounds0, 0, half, count, base, kind,
                        *(float*)(object + 0x10c) / (float)rest, end);

            step = lbl_80650B70 * *(float*)(object + 0x110);
            fn_80187320(owner + 0x38, flags1, bounds1, 1, 0, half,
                        starts[1], kind, step, end);
            base = (int)((float)half * step + (float)starts[1]);
            fn_80187320(entry, flags1, bounds1, 1, half, count, base, kind,
                        *(float*)(object + 0x110) / (float)rest, end);

            step = lbl_80650B70 * *(float*)(object + 0x114);
            fn_80187320(owner + 0x38, flags2, bounds2, 2, 0, half,
                        starts[2], kind, step, end);
            base = (int)((float)half * step + (float)starts[2]);
            fn_80187320(entry, flags2, bounds2, 2, half, count, base, kind,
                        *(float*)(object + 0x114) / (float)rest, end);
        } else {
            fn_80187320(owner + 0x38, flags0, bounds0, 0, 0, count,
                        starts[0], kind, *(float*)(object + 0x10c), end);
            fn_80187320(owner + 0x38, flags1, bounds1, 1, 0, count,
                        starts[1], kind, *(float*)(object + 0x110), end);
            fn_80187320(owner + 0x38, flags2, bounds2, 2, 0, count,
                        starts[2], kind, *(float*)(object + 0x114), end);
        }
    } else {
        if (flags & 0x32000) {
            if (flags & 0x10000) {
                fn_80187488(owner + 0x38, flags0, bounds0, 0, 0, count,
                            starts, (s16*)(object + 0xa2), mode, end);
            } else {
                fn_801871F0(owner + 0x38, flags0, bounds0, 0, 0, count,
                            starts[0], *(s16*)(object + 0xa8), kind, end);
            }
            if (*(u32*)(object + 0x108) & 0x20000) {
                fn_80187488(owner + 0x38, flags1, bounds1, 1, 0, count,
                            starts, (s16*)(object + 0xa2), mode, end);
            } else {
                fn_801871F0(owner + 0x38, flags1, bounds1, 1, 0, count,
                            starts[1], *(s16*)(object + 0xaa), kind, end);
            }
            if (*(u32*)(object + 0x108) & 0x2000) {
                fn_80187488(owner + 0x38, flags2, bounds2, 2, 0, count,
                            starts, (s16*)(object + 0xa2), mode, end);
            } else {
                fn_801871F0(owner + 0x38, flags2, bounds2, 2, 0, count,
                            starts[2], *(s16*)(object + 0xac), kind, end);
            }
        } else if (flags & 0x100) {
            int half = count >> 1;
            int rest;
            int step;
            int base;

            fn_801871F0(owner + 0x38, flags0, bounds0, 0, 0, count,
                        starts[0], *(s16*)(object + 0xa8), kind, end);
            fn_801871F0(owner + 0x38, flags1, bounds1, 1, 0, count,
                        starts[1], *(s16*)(object + 0xaa), kind, end);
            step = *(s16*)(object + 0xac) * 2;
            fn_801871F0(owner + 0x38, flags2, bounds2, 2, 0, half,
                        starts[2], step, kind, end);
            rest = count - half;
            base = starts[2] + half * step;
            fn_801871F0(owner + 0x38 + half * 0x38, flags2, bounds2, 2,
                        half, count, base, *(s16*)(object + 0xac) / rest,
                        kind, end);
        } else if (flags & 0x400) {
            int half = count >> 1;
            int rest = count - half;
            int step;
            int base;
            u8* entry = owner + 0x38 + half * 0x38;

            step = *(s16*)(object + 0xa8) * 2;
            fn_801871F0(owner + 0x38, flags0, bounds0, 0, 0, half,
                        starts[0], step, kind, end);
            base = starts[0] + half * step;
            fn_801871F0(entry, flags0, bounds0, 0, half, count, base,
                        *(s16*)(object + 0xa8) / rest, kind, end);

            step = *(s16*)(object + 0xaa) * 2;
            fn_801871F0(owner + 0x38, flags1, bounds1, 1, 0, half,
                        starts[1], step, kind, end);
            base = starts[1] + half * step;
            fn_801871F0(entry, flags1, bounds1, 1, half, count, base,
                        *(s16*)(object + 0xaa) / rest, kind, end);

            step = *(s16*)(object + 0xac) * 2;
            fn_801871F0(owner + 0x38, flags2, bounds2, 2, 0, half,
                        starts[2], step, kind, end);
            base = starts[2] + half * step;
            fn_801871F0(entry, flags2, bounds2, 2, half, count, base,
                        *(s16*)(object + 0xac) / rest, kind, end);
        } else {
            fn_801871F0(owner + 0x38, flags0, bounds0, 0, 0, count,
                        starts[0], *(s16*)(object + 0xa8), kind, end);
            fn_801871F0(owner + 0x38, flags1, bounds1, 1, 0, count,
                        starts[1], *(s16*)(object + 0xaa), kind, end);
            fn_801871F0(owner + 0x38, flags2, bounds2, 2, 0, count,
                        starts[2], *(s16*)(object + 0xac), kind, end);
        }
    }
}
