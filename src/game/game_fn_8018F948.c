typedef signed short s16;
typedef unsigned char u8;
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
    u32 state[4];
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
    u8 count;
    signed char effect_type;
    u8 field02;
    u8 field03;
    s16 field04;
    u16 field06;
    u16 field08;
    u8 pad0A[0xA];
    u32 values[2];
} EffectDescriptor;

extern ShortCoord3 lbl_80651D80;
extern const float lbl_80650B00;
extern void* lbl_8064D224;
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];

extern void* memset(void*, int, unsigned int);
extern void* memcpy(void*, const void*, unsigned int);
extern void fn_801804AC(void*, const void*, const void*, const void*);
extern void fn_80180518(u32*, u32, int);
extern void fn_80180554(void*, ShortCoord3*, ShortCoord3*, ShortCoord3*, u16,
                        u16);
extern void fn_801805E0(u8*, int, u8, u32, u32*, float);
extern void fn_801806D4(u8*, u32*, int);
extern void fn_8018C118(u16*, int);
extern void fn_8018FFBC(u8*, const u8*, const u8*, u8);
extern void fn_801F5A04(void*, u32, void*, void*);

void fn_8018F948(EffectObject* object, void* first, void* second,
                 EffectDescriptor* config)
{
    ShortCoord3 fixed;
    u32 first_value;
    u32 second_value;
    u32* values;
    u8 count;
    int i;
    u32 loop_count;
    EffectEntry* entry;

    values = config->values;
    fixed = lbl_80651D80;
    entry = object->entries;
    count = config->count;
    fn_801804AC(object, first, second, &fixed);

    object->flags = 0x80;
    object->count = count;
    object->field0C = config->field06;
    object->field0E = config->field04;
    object->field0A = 0;
    object->field44 = 0;
    object->field02 = config->field02;
    object->field04 = config->field03;
    object->field68 = lbl_8064D224;
    memset(object->state, 0, sizeof(object->state));

    memcpy(&first_value, &values[0], sizeof(first_value));
    memcpy(&second_value, &values[1], sizeof(second_value));

    /* Promote once for the unsigned loop comparison and resource setup. */
    loop_count = count;
    for (i = 0; (u8)i < loop_count; i++) {
        fn_80180554(entry, first, second, &fixed,
                    config->field08, 0);
        fn_801805E0(entry->effect, 2, config->effect_type, (i & 0x7F) * 2,
                    &first_value, lbl_80650B00);
        fn_801806D4(entry->effect, &second_value, 1);
        fn_80180518(object->state, i, 1);
        entry++;
    }

    fn_8018C118(object->resource54, loop_count);
    fn_8018FFBC(object->resource58, (const u8*)&first_value,
                (const u8*)&second_value, count);
    if (config->field04 >= 0) {
        fn_801F5A04(object->field6C, config->field04, lbl_80606328,
                    lbl_80606318);
    }
}
