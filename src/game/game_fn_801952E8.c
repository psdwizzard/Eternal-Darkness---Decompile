typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct VertexRecord {
    u8 pad0[10];
    s16 x;
    s16 y;
    s16 z;
    u8 pad10[40];
} VertexRecord;

extern const double lbl_80650B58;
extern const double lbl_80650B68;

s16 fn_801F6D90(s16 x, s16 y, s16 z);
void fn_80194AC4(const s16* first, const float* scale, u8* state);
void fn_80194E80(const s16* first, const s16* second, const s16* step,
                 u8* state);
void fn_80194F80(const s16* first, const s16* second, const float* scale,
                 u8* state);
void fn_801950D4(const s16* first, const s16* step, u8* state);

void fn_801952E8(u8* object, int populate)
{
    s16* xs;
    s16* ys;
    s16* zs;
    u8* state = object + 0x8C;
    s16* first = (s16*)(object + 0x10);
    s16* second = (s16*)(state + 0x16);
    u8 count = object[0x97] - 4;
    VertexRecord* records;
    int i;

    if (*(u32*)(object + 0x108) & 0x4000) {
        *(s16*)(state + 0x22) = fn_801F6D90(first[0], first[1], first[2]);
        *(s16*)(state + 0x24) =
            (fn_801F6D90(second[0], second[1], second[2]) -
             *(s16*)(state + 0x22)) / count;
    } else {
        *(s16*)(state + 0x22) = 0;
        *(s16*)(state + 0x24) = 0;
    }

    if (*(u32*)(state + 0x7C) & 0x8000) {
        float* scale = (float*)(state + 0x80);
        scale[0] = (float)(second[0] - first[0]) / (float)count;
        scale[1] = (float)(second[1] - first[1]) / (float)count;
        scale[2] = (float)(second[2] - first[2]) / (float)count;
    } else {
        s16* step = (s16*)(state + 0x1C);
        step[0] = (second[0] - first[0]) / count;
        step[1] = (second[1] - first[1]) / count;
        step[2] = (second[2] - first[2]) / count;
    }

    if (*(u32*)(state + 0x7C) & 0x8000) {
        if (*(u32*)(state + 0x7C) & 0x32000) {
            fn_80194F80(first, second, (float*)(state + 0x80), state);
        } else {
            fn_80194AC4(first, (float*)(state + 0x80), state);
        }
    } else {
        if (*(u32*)(state + 0x7C) & 0x32000) {
            fn_80194E80(first, second, (s16*)(state + 0x1C), state);
        } else {
            fn_801950D4(first, (s16*)(state + 0x1C), state);
        }
    }

    records = *(VertexRecord**)(object + 0x4C);
    records[0].x = first[0];
    records[0].y = first[1];
    records[0].z = first[2];
    xs = (s16*)(state + 0x28);
    ys = (s16*)(state + 0x42);
    zs = (s16*)(state + 0x5C);
    if (populate) {
        records = *(VertexRecord**)(object + 0x4C);
        for (i = 0; i < count; i++) {
            records[i + 1].x = xs[i];
            records[i + 1].y = ys[i];
            records[i + 1].z = zs[i];
        }
    }
    records[count + 1].x = second[0];
    records[count + 1].y = second[1];
    records[count + 1].z = second[2];

    if (!(*(u32*)(state + 0x7C) & 0x40)) {
        if (*(u32*)(state + 0x7C) & 0x8000) {
            if (*(u32*)(state + 0x7C) & 0x32000) {
                fn_80194F80(first, second, (float*)(state + 0x80), state);
            } else {
                fn_80194AC4(first, (float*)(state + 0x80), state);
            }
        } else {
            if (*(u32*)(state + 0x7C) & 0x32000) {
                fn_80194E80(first, second, (s16*)(state + 0x1C), state);
            } else {
                fn_801950D4(first, (s16*)(state + 0x1C), state);
            }
        }

        *(u16*)(state + 0x10) &= 7;
        *(u16*)(state + 0x12) &= 7;
        *(u16*)(state + 0x14) &= 7;
        records = *(VertexRecord**)(object + 0x4C);
        records++;
        {
            u32 bit = 8;
            for (i = 0; i < count; i++, records++, xs++, ys++, zs++) {
                if (records->x < *xs)
                    *(u16*)(state + 0x10) |= bit;
                if (records->y < *ys)
                    *(u16*)(state + 0x12) |= bit;
                if (records->z < *zs)
                    *(u16*)(state + 0x14) |= bit;
                bit <<= 1;
            }
        }
    }
}
