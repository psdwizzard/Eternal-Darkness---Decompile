typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Buffers {
    u8* vertices;
    u8* indices;
    u8* colors;
} Buffers;

extern Vec3 lbl_8023B094;
extern u8 lbl_80607120[];
extern int lbl_8064D738;
extern void* lbl_8064C4E4;
extern float lbl_80650B84;
extern float lbl_80650B8C;
extern float lbl_80650B90;
extern float lbl_80650B94;

extern void fn_8018D788(int, void*, Buffers*, u16);
extern void fn_8011F114(Vec3*, void*);
extern void PSVECSubtract(Vec3*, Vec3*, Vec3*);
extern float PSVECMag(Vec3*);
extern void DCFlushRange(void*, u32);
extern int fn_801ED57C(int);
extern void fn_801ED5F4(int, int, int, int, void*, float);
extern void GXSetCullMode(int);
extern void fn_8018D0D0(void*, void*, int);
extern void fn_80189B70(void*, void*, void*);
extern void* memcpy(void*, const void*, unsigned long);

void fn_80197910(u8* object)
{
    u8 scratch[0x30];
    Vec3 average = lbl_8023B094;
    Buffers buffers;
    Vec3 direction;
    Vec3 position;
    float alpha_scale = lbl_80650B84;
    int count;
    u8 initial_count;
    u8* entry;
    u8* destination;
    u8* source;
    u8* color;
    u8* alpha;
    int outer;
    int inner;
    int saved;
    float distance;
    u8* config = lbl_80607120;

    entry = *(u8**)(object + 0x4c);
    fn_8018D788(lbl_8064D738, object, &buffers,
                *(u16*)(config + 2));
    color = buffers.colors;
    initial_count = object[1];
    source = buffers.vertices + ((initial_count - 1) << 1) * 6;
    count = initial_count;
    destination = source;

    while (count < 64) {
        memcpy(destination, source, 6);
        average.x += *(s16*)(destination + 0);
        average.y += *(s16*)(destination + 2);
        average.z += *(s16*)(destination + 4);
        memcpy(destination + 6, source + 6, 6);
        average.x += *(s16*)(destination + 6);
        average.y += *(s16*)(destination + 8);
        average.z += *(s16*)(destination + 10);
        destination += 12;
        count++;
    }

    average.x /= (64 - object[1]) * 2;
    average.y /= (64 - object[1]) * 2;
    average.z /= (64 - object[1]) * 2;

    if (*(u16*)(object + 8) != 0) {
        if (lbl_8064C4E4 != 0) {
            fn_8011F114(&position, lbl_8064C4E4);
            direction = position;
            direction.z += lbl_80650B8C;
            PSVECSubtract(&average, &direction, &direction);
            distance = PSVECMag(&direction);
            if (distance > *(u16*)(object + 8)) {
                return;
            }
            alpha_scale = lbl_80650B84 - distance / *(u16*)(object + 8);
        } else {
            return;
        }
    }

colors:
    for (outer = 0; outer < object[1]; outer++) {
        alpha = entry;
        for (inner = 0; inner < entry[0x20]; inner++) {
            color[3] = (u8)(alpha[0x2b] * alpha_scale);
            alpha += 4;
            color += 4;
        }
        entry += 0x38;
    }

    DCFlushRange(buffers.vertices, *(u16*)(config + 0xa));
    DCFlushRange(buffers.indices, *(u16*)(config + 0xe));
    DCFlushRange(buffers.colors, *(u16*)(config + 0xc));
    saved = fn_801ED57C(0);
    if (*(u16*)(object + 0x96) != 0) {
        fn_801ED5F4(1, *(u16*)(object + 0x96) | 0x2000,
                    *(s16*)(object + 0x98), 0, scratch, lbl_80650B90);
        GXSetCullMode(0);
    }
    fn_8018D0D0(object, object + 0x5c, *(s16*)(object + 0xe));
    fn_80189B70(buffers.vertices, buffers.indices, buffers.colors);
    if (*(u16*)(object + 0x96) != 0)
        fn_801ED5F4(0, 0, 0, 0, 0, lbl_80650B94);
    fn_801ED57C(saved);
}
