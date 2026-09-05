typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

extern s16 lbl_80606360[];
extern const double lbl_80650A10;
extern void* memcpy(void*, const void*, unsigned long);

void fn_8018680C(u8* state, u8* entry, Vec3s* dst, int index, Vec3s* origin, u8 count)
{
    int phase;
    s16 offset;
    u16 center;
    s16* sine = lbl_80606360;
    s16* cosine = lbl_80606360 + 64;
    u16 distance;
    Vec3s temp;
    if (index < count - 1) {
        phase = (int)(index * *(float*)(state + 0x30)) & 0x3F;
    } else {
        phase = 0;
    }
    offset = entry[0x21];
    if (state[5] & 2) {
        offset = (s16)-offset;
    }
    center = *(u16*)(state + 0xE);
    distance = center - offset;
    temp.x = origin->x + ((distance * sine[phase]) >> 7);
    temp.y = origin->y + ((distance * cosine[phase]) >> 7);
    temp.z = origin->z;
    memcpy(dst, &temp, 6);
    distance = center + offset;
    temp.x = origin->x + ((distance * sine[phase]) >> 7);
    temp.y = origin->y + ((distance * cosine[phase]) >> 7);
    temp.z = origin->z;
    memcpy((u8*)dst + 6, &temp, 6);
}
