typedef int s32;
typedef unsigned int u32;
typedef short s16;
typedef unsigned short u16;
typedef signed char s8;
typedef unsigned char u8;
typedef unsigned long long u64;

typedef struct Vec3 { float x, y, z; } Vec3;

extern const char lbl_80244EDC[];
extern unsigned char lbl_8031CD84[];
extern unsigned char lbl_802FC5BC[];
extern s32 lbl_8064C8F0;
extern s32 lbl_8064C4E4;
extern s32 lbl_8064D18C;
extern float lbl_8064EA14;
extern float lbl_8064EA50;
extern float lbl_8064EA54;
extern float lbl_8064EA58;

extern int fn_8016A598(void *);
extern void fn_80163BB4(void *, const char *, ...);
extern void *fn_8015C4A4(u32, int);
extern s16 *fn_80158CC8(void *, int, int);
extern void fn_8011F0E8(s32, Vec3 *);
extern void fn_8011F114(Vec3 *, void *);
extern void *fn_80201B9C(void);
extern void *fn_80201BC0(void *);
extern void *fn_80201BC8(void *);
extern int fn_80201B54(void *);
extern int fn_80201B44(void);
extern int fn_80201EB8(void *);
extern u64 fn_8020123C(int, int, int, int);
extern float fn_801790A4(float, float, float, float);
extern int fn_80036E50(void *);
extern u16 fn_80050730(int, int, u8 *, s8 *, s16 *, int);
extern void fn_801A98F4(u16, u8);
extern void fn_800CEA1C(int, int, Vec3 *, int, int, int, void *, float, float, float);

s32 fn_8007F80C(void *script)
{
    Vec3 center;
    void *object;
    void *runtime;
    int objectId;
    u16 sound;
    s16 *pos;

    if (fn_8016A598(script) != 0) {
        fn_80163BB4(script, lbl_80244EDC, 0, fn_8016A598(script));
        return 0;
    }

    pos = fn_80158CC8(fn_8015C4A4(((u32 *)(lbl_8031CD84 + 0x444))[lbl_8064C8F0 * 2], 2), 2, 0);
    center.x = pos[0];
    center.y = pos[1];
    center.z = pos[2];
    fn_8011F0E8(lbl_8064C4E4, &center);

    for (object = fn_80201B9C(); object != 0; object = fn_80201BC0(object)) {
        runtime = fn_80201BC8(object);
        if (runtime == 0) {
            continue;
        }
        objectId = fn_80201B54(object);
        if ((u32)(fn_8020123C(0x3B, objectId, objectId, 0) & 0xFFFFFFFF) == 0) {
            continue;
        }
        if (objectId == fn_80201B44()) {
            continue;
        }
        if (runtime == 0) {
            continue;
        }
        if (lbl_8064D18C != fn_80201EB8(object)) {
            continue;
        }
        {
            Vec3 objPos;
            Vec3 tmp;
            u8 volume;
            s8 pan;
            s16 pitch;

            fn_8011F114(&tmp, runtime);
            objPos = tmp;
            if (!(fn_801790A4(objPos.x, objPos.y, center.x, center.y) < lbl_8064EA50)) {
                continue;
            }
            volume = 0x7F;
            pan = 0;
            pitch = 0;
            switch (fn_80036E50(object)) {
            case 3:
                sound = 0x3B;
                break;
            case 4:
                sound = 0xB6;
                break;
            case 5:
                sound = 0x15B;
                break;
            default:
                sound = fn_80050730(0x32, 0, &volume, &pan, &pitch, 0);
                break;
            }
            fn_8020123C(0x39, objectId, objectId, 0);
            if (sound != 0) {
                fn_801A98F4(sound, volume);
            }
            fn_800CEA1C(0x17, 3, &center, 0, 5, 10, lbl_802FC5BC + 0x18,
                        lbl_8064EA54, lbl_8064EA14, lbl_8064EA58);
        }
    }
    return 0;
}
