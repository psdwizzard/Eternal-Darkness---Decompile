typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ShortCoord3 {
    s16 x;
    s16 y;
    s16 z;
} ShortCoord3;

typedef struct Object80180ED8 {
    u8 type;
    u8 count;
    u8 config2;
    u8 pad03;
    u8 config3;
    u8 pad05[5];
    u16 field0A;
    u16 field0C;
    s16 field0E;
    u8 pad10[6];
    ShortCoord3 base;
    ShortCoord3 zero;
    u8 pad22[2];
    u8 flags[0x10];
    u8 pad34[8];
    float initial_a;
    float initial_b;
    u32 field44;
    u8 pad48[4];
    u8* entry;
    u8 pad50[4];
    void* field54;
    void* field58;
    u8 pad5C[0xC];
    void* field68;
} Object80180ED8;

extern u32 lbl_80650958;
extern const float lbl_8065095C;
extern const float lbl_80650960;
extern const float lbl_80650964;
extern void* lbl_8064D224;
extern u8 lbl_80607120[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];

extern void* memset(void*, int, unsigned int);
extern void* memcpy(void*, const void*, unsigned int);
extern unsigned int rand(void);
extern void fn_80179904(ShortCoord3*, s16);
extern void fn_801804AC(void*, ShortCoord3*, ShortCoord3*, ShortCoord3*);
extern void fn_80180554(void*, ShortCoord3*, ShortCoord3*, ShortCoord3*, u16,
                        int);
extern void fn_801805E0(void*, int, u8, u32, u8*, float);
extern void fn_8018CEC0(void*, u8);
extern void fn_8018CB70(void*, u8, u16);
extern void fn_8018C540(void*, u8*, u8, int, u16);
extern void fn_801F5A04(void*, s16, void*, void*);

void fn_80180ED8(Object80180ED8* object, ShortCoord3* first, ShortCoord3* second,
                 u8* config)
{
    u32 effect;
    ShortCoord3 work;
    u32 i;
    u8 count;
    u8* entry;
    float initial_b = lbl_80650960;
    float initial_a = lbl_8065095C;

    effect = lbl_80650958;
    entry = object->entry;
    count = config[0];

    object->type = 0x80;
    object->count = config[0];
    object->field0C = *(u16*)(config + 6);
    object->field0E = *(s16*)(config + 4);
    object->field0A = 0;
    object->field44 = 0;
    object->config2 = config[2];
    object->config3 = config[3];
    object->initial_a = initial_a;
    object->initial_b = initial_b;
    object->field68 = lbl_8064D224;
    memset(object->flags, 0, 0x10);

    fn_801804AC(object, first, second, (ShortCoord3*)(config + 0x24));
    fn_80179904(&object->base, *(s16*)(config + 0x20));

    for (i = 0; (u8)i < count; i++) {
        memcpy(&work, &object->base, sizeof(work));
        if (config[0x18] & 0x20) {
            work.z = object->base.z * ((rand() & 3) + 1);
        }
        fn_80180554(entry, first, &work, &object->zero,
                    *(u16*)(config + 8), 0);
        fn_801805E0(entry + 0x20, 4, config[1], (i & 0x3F) * 4,
                    (u8*)&effect, lbl_80650964);
        entry += 0x38;
    }

    if (config[0x18] & 0x40) {
        fn_8018CEC0(object->field54, count);
    } else {
        fn_8018CB70(object->field54, count,
                    *(u16*)(lbl_80607120 + 2));
    }
    fn_8018C540(object->field58, config + 0x10, count, 4,
                *(u16*)(lbl_80607120 + 2));
    if (*(s16*)(config + 4) >= 0) {
        fn_801F5A04((u8*)object + 0x6C, *(s16*)(config + 4), lbl_80606328,
                    lbl_80606318);
    }
}
