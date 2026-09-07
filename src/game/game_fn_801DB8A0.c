typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Descriptor {
    u32 word;
    u16 half;
} Descriptor;

typedef struct EffectInfo {
    u8 type;
    u8 count;
    u8 pad2;
    s8 flags;
    s16 value;
    u16 variant;
    u8 pad8[0xC];
    u8 mode;
    u8 pad15[3];
    u32 owner;
    u8 pad1C[0x74];
} EffectInfo;

extern u32 lbl_80651EE8;
extern u16 lbl_80651EEC;
extern u32 lbl_80651EF0;
extern u32 lbl_80651190;
extern u32 lbl_80651194;
extern float lbl_80651198;
extern float lbl_8065119C;

extern void* fn_80201814(u32);
extern void fn_802020B4(void*, u32);
extern void* fn_80201BC8(void*);
extern void fn_8012C62C(void*, u32, u32*, u32*, u32*, u32);
extern void fn_8020104C(u32, u32, u32, u32, float);
extern void fn_80181F5C(EffectInfo*);
extern u32 fn_800FBFB0(void);
extern void fn_8011F114(Vec3*, void*);
extern void* fn_80148008(Vec3*, Descriptor*, EffectInfo*, void (*)(void));
extern void fn_80182014(void);

void fn_801DB8A0(u32 object_id, s16 value)
{
    void* object;
    Descriptor descriptor;
    u32 first;
    u32 second;
    u32 third;
    Vec3 position;
    Vec3 submit_position;
    EffectInfo info;

    object = fn_80201814(object_id);
    if (object != 0) {
        descriptor.word = lbl_80651EE8;
        descriptor.half = lbl_80651EEC;
        fn_802020B4(object, 0);
        object = fn_80201BC8(object);
        third = lbl_80651EF0;
        second = lbl_80651194;
        first = lbl_80651190;
        fn_8012C62C(object, 15, &first, &second, &third, 4);
        fn_8020104C(0x39, 0, object_id, 0, lbl_80651198);
        fn_80181F5C(&info);
        info.variant = (fn_800FBFB0() & 3) + 1;
        info.type = 0x10;
        info.count = 4;
        info.value = value;
        info.flags = -10;
        info.owner = 0;
        info.mode = 0x10;
        fn_8011F114(&position, object);
        position.z += lbl_8065119C;
        submit_position = position;
        fn_80148008(&submit_position, &descriptor, &info, fn_80182014);
    }
}
