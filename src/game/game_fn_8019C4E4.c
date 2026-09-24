typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ShortCoord3 {
    s16 x;
    s16 y;
    s16 z;
} ShortCoord3;

typedef struct EffectEntry {
    u8 pad00[0x20];
    u8 effect[0x18];
} EffectEntry;

typedef struct EffectObject {
    u8 flags;
    u8 count;
    u8 field02;
    u8 pad03;
    u8 field04;
    u8 pad05[5];
    u16 field0A;
    u16 field0C;
    s16 field0E;
    u8 pad10[0x14];
    u8 state[0x10];
    u8 pad34[0x10];
    u32 field44;
    u8 pad48[4];
    EffectEntry* entries;
    u8 pad50[4];
    void* resource54;
    void* resource58;
    u8 pad5C[0xC];
    void* field68;
    u8 field6C[1];
} EffectObject;

typedef struct EffectDescriptor {
    signed char count;
    signed char effect_type;
    u8 field02;
    u8 field03;
    s16 field04;
    u16 field06;
    u16 field08;
    u8 pad0A[0xE];
    u8 effect[6];
} EffectDescriptor;

extern ShortCoord3 lbl_80651E00;
extern ShortCoord3 lbl_80651E08;
extern void* lbl_8064D224;
extern const float lbl_80650C10;
extern u8 lbl_80607120[];
extern u8 lbl_80606328[];
extern u8 lbl_80606318[];

extern void fn_801804AC(void*, const void*, const void*, const void*);
extern void* memset(void*, int, unsigned long);
extern void fn_80180554(void*, ShortCoord3*, ShortCoord3*, ShortCoord3*, u16,
                        u16);
extern void fn_801805E0(u8*, int, u8, u32, u32*, float);
extern void fn_8018CEC0(u32*, u8);
extern void fn_8018C540(u8*, const u8*, u8, int, u16);
extern void fn_801F5A04(void*, u32, void*, void*);

void fn_8019C4E4(EffectObject* object, void* first, void* second,
                 EffectDescriptor* config)
{
    ShortCoord3 setup;
    ShortCoord3 value;
    EffectEntry* entry;
    int i;
    u32 count;

    setup = lbl_80651E00;
    value = lbl_80651E08;
    /* Keep the integer promotion explicit before narrowing the descriptor byte. */
    count = (u8)(int)config->count;
    entry = object->entries;
    fn_801804AC(object, first, &setup, &value);

    object->flags = 0x80;
    object->count = config->count;
    object->field02 = config->field02;
    object->field04 = config->field03;
    object->field0C = config->field06;
    object->field0E = config->field04;
    object->field0A = 0;
    object->field44 = 0;
    object->field68 = lbl_8064D224;
    memset(object->state, 0, sizeof(object->state));

    i = 0;
    config->effect[3] = 0;
    for (; (u8)i < count; entry++, i++) {
        fn_80180554(entry, first, &setup, &value, config->field08, 0);
        fn_801805E0(entry->effect, 4, config->effect_type,
                    (u32)((i & 0x3F) * 4), (u32*)config->effect,
                    lbl_80650C10);
    }

    fn_8018CEC0(object->resource54, count);
    fn_8018C540(object->resource58, config->effect, count, 4,
                *(u16*)(lbl_80607120 + 2));
    if (config->field04 >= 0) {
        fn_801F5A04(object->field6C, config->field04,
                    lbl_80606328, lbl_80606318);
    }
}
