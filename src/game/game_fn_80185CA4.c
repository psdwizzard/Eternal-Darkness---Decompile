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
    u8 pad10[6];
    u8 position[6];
    u8 pad1C[8];
    u32 state[4];
    u8 pad34[0x10];
    u32 field44;
    u8 pad48[4];
    EffectEntry *entries;
    u8 pad50[4];
    void *resource54;
    void *resource58;
    u8 pad5C[0xC];
    void *field68;
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
    u8 pad0A[0xF];
    u8 field19;
    u8 pad1A[6];
    s16 field20;
    u8 pad22[0x56];
    u32 effect[1];
} EffectDescriptor;

extern ShortCoord3 lbl_80651D38;
extern void* lbl_8064D224;
extern float lbl_80650A18;
extern u8 lbl_80607120[];
extern u8 lbl_80606318[];
extern u8 lbl_80606328[];

extern void* memset(void*, int, u32);
extern void fn_80179904(void*, s16);
extern void fn_801804AC(void*, const void*, const void*, const void*);
extern void fn_80180518(u32*, u32, int);
extern void fn_80180554(void*, void*, void*, void*, u16, u16);
extern void fn_801805E0(u8*, int, u8, u32, u32*, float);
extern void fn_8018C2D0(void*, u8, u8);
extern void fn_8018C540(void*, void*, u8, int, u16);
extern void fn_801F5A04(void*, u32, void*, void*);

void fn_80185CA4(EffectObject* self, void* arg1, void* arg2,
                 EffectDescriptor* desc)
{
    int i;
    EffectEntry* entry;
    u8 count;
    ShortCoord3 setup;

    setup = lbl_80651D38;
    entry = self->entries;
    count = desc->count;
    fn_801804AC(self, arg1, arg2, &setup);

    self->flags = 0x80;
    self->count = desc->count;
    self->field0C = desc->field06;
    self->field0E = desc->field04;
    self->field0A = 0;
    self->field44 = 0;
    self->field02 = desc->field02;
    self->field04 = desc->field03;
    self->field68 = lbl_8064D224;
    memset(self->state, 0, sizeof(self->state));
    fn_80179904(self->position, desc->field20);

    for (i = 0; (u8)i < count; i++) {
        fn_80180554(entry, arg1, self->position, &setup,
                    desc->field08, 0);
        /* Keep the signed-byte promotion explicit for register allocation. */
        fn_801805E0(entry->effect, 2, (int)desc->effect_type,
                    (i & 0x7F) << 1, desc->effect, lbl_80650A18);
        fn_80180518(self->state, i, 1);
        entry++;
    }

    fn_8018C2D0(self->resource54, count, desc->field19);
    fn_8018C540(self->resource58, desc->effect, count, 2,
                *(u16*)(lbl_80607120 + 2));
    if (desc->field04 >= 0) {
        fn_801F5A04(self->field6C, desc->field04,
                    lbl_80606328, lbl_80606318);
    }
}
