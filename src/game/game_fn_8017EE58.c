typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ShortCoord3 {
    s16 x;
    s16 y;
    s16 z;
} ShortCoord3;

typedef struct ResultEntry {
    s16 values[12];
    u32 flags;
    u32 field_1C;
} ResultEntry;

typedef struct ResultTable {
    u32 pad[2];
    ResultEntry* entries;
} ResultTable;

typedef struct EffectObject {
    u8 flags;
    u8 count;
    u8 pad_02[8];
    u16 field_0A;
    u8 pad_0C[2];
    s16 field_0E;
    u8 pad_10[0x14];
    u32 control[4];
    u8 pad_34[0x10];
    u32 field_44;
    u8 pad_48[4];
    u8* entries;
    u8 pad_50[4];
    u32* field_54;
    u8* field_58;
    u8 pad_5C[0xC];
    void* field_68;
    ResultEntry result;
} EffectObject;

extern u32 lbl_80651CC8;
extern u16 lbl_80651CCC;
extern void* lbl_8064D224;
extern float lbl_80650938;
extern u16 lbl_80607120[];
extern u8 lbl_80606318[0x10];
extern ResultTable lbl_80606328;

extern void* memset(void*, int, u32);
extern void* memcpy(void*, const void*, u32);
extern void fn_80179904(ShortCoord3*, s16);
extern void fn_801804AC(void*, const void*, const void*, const void*);
extern void fn_8018EFB0(s16*, u16, int);
extern void fn_80180554(void*, ShortCoord3*, ShortCoord3*, ShortCoord3*, u16,
                        u16);
extern void fn_801805E0(u8*, int, u8, u32, u32*, float);
extern void fn_80180518(u32*, u32, int);
extern void fn_8018CEC0(u32*, u8);
extern void fn_8017FA14(u8*, const u8*, const u8*, u8, int, u32);
extern void fn_801F5A04(ResultEntry*, u32, ResultTable*, int);

void fn_8017EE58(EffectObject* object, ShortCoord3* first, ShortCoord3* second,
                 u8* config) {
    u32 i;
    ShortCoord3 work;
    ShortCoord3 base;
    ShortCoord3 current;
    ShortCoord3 zero;
    u8 index;

    *(u32*)&zero = lbl_80651CC8;
    *(u16*)((u8*)&zero + 4) = lbl_80651CCC;
    object->flags = 0x80;
    object->count = config[0];
    object->field_0E = *(s16*)(config + 4);
    object->field_0A = 0;
    object->field_44 = 0;
    object->field_68 = lbl_8064D224;
    memset(object->control, 0, sizeof(object->control));

    memcpy(&base, second, sizeof(base));
    fn_80179904(&base, *(s16*)(config + 0x14));
    fn_801804AC(object, first, &base, &zero);

    i = 0;
    current.x = first->x + 10;
    current.y = first->y - 10;
    current.z = first->z;

    while ((index = i) < object->count - 1) {
        u8* entry = object->entries + (u8)(unsigned long)i * 0x38;

        memcpy(&work, &base, sizeof(work));
        if (work.x != 0) {
            fn_8018EFB0((s16*)&work, config[0x16], 0);
        }
        if (work.y != 0) {
            fn_8018EFB0((s16*)&work, config[0x16], 1);
        }
        fn_80180554(entry, first, &work, &zero, *(u16*)(config + 8), 1);
        fn_801805E0(entry + 0x20, 4, config[1], 0, (u32*)(config + 0x1C),
                    lbl_80650938);
        fn_80180518(object->control, i, 1);

        fn_80180554(entry + 0x38, &current, &work, &zero,
                    *(u16*)(config + 8), 1);
        fn_801805E0(entry + 0x58, 4, config[1], 0, (u32*)(config + 0x20),
                    lbl_80650938);
        fn_80180518(object->control, (u8)(index + 1), 1);
        i += 2;
    }

    fn_8018CEC0(object->field_54, object->count);
    fn_8017FA14(object->field_58, config + 0x1C, config + 0x20,
                object->count, 4, lbl_80607120[1]);
    if (*(s16*)(config + 4) >= 0) {
        fn_801F5A04(&object->result, *(s16*)(config + 4), &lbl_80606328,
                    (int)lbl_80606318);
    }
}
