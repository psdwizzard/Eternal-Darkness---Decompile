typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Object { u8 bytes[0x1000]; } Object;

extern int fn_801CEB2C(u32);
extern float fn_80048C2C(float);
extern float fn_80048C50(float);
extern void* fn_80201890(u32);
extern void fn_801D73D0(void);
extern int fn_80142A70(u8, s16*, int, u32, void*, void*, Object*, void*);
extern void fn_801D7998(s16*, s16*, Object*);

extern const float lbl_806510E4;
extern const float lbl_806510E8;

void fn_801D7C24(u32 id, Object* object, float angle, void* target, int emit)
{
    s16 points[24];
    int count_raw;
    s16* point;
    u8* entry;
    s16* out;
    s16 count;
    u8* base;
    int i;
    float step;
    float a;
    int j;

    base = object->bytes + 0xBC;
    count_raw = fn_801CEB2C(id);
    out = points;
    count = count_raw;
    point = out;
    entry = base;
    i = 0;
    while (i < count) {
        step = lbl_806510E4 * (float)i / (float)count;
        a = angle + step;
        point[0] = (s16)(lbl_806510E8 * fn_80048C2C(a) + *(float*)(object->bytes + 0x38));
        point[1] = (s16)(lbl_806510E8 * fn_80048C50(a) + *(float*)(object->bytes + 0x3C));
        point[2] = (s16)*(float*)(object->bytes + 0x40);
        *(u32*)(entry + 0x54) = *(u32*)point;
        *(u16*)(entry + 0x58) = *(u16*)(point + 2);
        point += 3;
        entry += 6;
        i++;
    }
    *(int*)(base + 0x4C) = fn_80142A70((u8)count_raw, points, 500,
        *(u32*)(object->bytes + 8), fn_80201890(*(u32*)(object->bytes + 0xC)),
        fn_801D73D0, object, target);
    if (emit != 0) {
        j = 0;
        while (j < count - 1) {
            fn_801D7998(out, out + 3, object);
            out += 3;
            j++;
        }
        fn_801D7998(points + j * 3, points, object);
    }
}
