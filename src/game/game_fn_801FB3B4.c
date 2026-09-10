typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SourceRecord {
    float position[3];
    u32 field0C;
    u32 field10;
    u32 field14;
    u32 field18;
    u32 field1C;
    u32 field20;
    u32 field24;
    float field28;
    float field2C;
    float field30;
    float field34;
    float field38;
    int field3C;
    int field40;
    u32 field44;
    float field48;
    float field4C;
    float field50;
    float field54;
    float field58;
    float field5C;
    void* field60;
    float field64;
    void* field68;
    void* field6C;
    u8 pad70[8];
    float field78;
    void* field7C;
    void* field80;
    u32 field84;
} SourceRecord;

typedef struct PackedRecord {
    u16 position[3];
    u16 flags;
    u32 field08;
    u32 field0C;
    u16 field10;
    u16 field12;
    float field14;
    u16 field18;
    u16 field1A;
    u16 field1C;
    u16 field1E;
    u16 field20;
    u16 field22;
    float field24;
    u8 field28;
    u8 field29;
    u8 field2A;
    u8 field2B;
    float field2C;
    u32 field30;
    u16 field34;
    u8 field36;
    u8 field37;
    u16 field38;
    u8 field3A;
    u8 field3B;
    u16 field3C;
    u8 pad3E[2];
} PackedRecord;

extern void* memset(void*, int, unsigned long);
extern void* memcpy(void*, const void*, unsigned long);
extern void fn_80201B3C(void);
extern void* fn_80201BC8(void);
extern void fn_801FB698(float*, u16*);
extern int fn_8017AC20(int, int, float);
extern int fn_801FAFF8(void*);
extern int fn_801FB0DC(void*);
extern int fn_801FB118(void*, int);
extern int fn_801FB270(void*, void*, int);
extern void fn_801F8694(void*, int);

u16 fn_801FB3B4(void* output, SourceRecord* source, int alternate)
{
    PackedRecord packed;
    void* context;
    int index;

    fn_80201B3C();
    context = fn_80201BC8();
    memset(&packed, 0, sizeof(packed));

    fn_801FB698(&source->position[0], &packed.position[0]);
    fn_801FB698(&source->position[1], &packed.position[1]);
    fn_801FB698(&source->position[2], &packed.position[2]);
    packed.field08 = source->field0C;
    packed.field0C = source->field14;
    packed.field14 = source->field30;
    packed.field3B = source->field10;
    packed.field37 = source->field18;
    packed.field30 = source->field84;
    packed.field2C = source->field78;
    packed.field24 = source->field64;
    packed.field34 = source->field44;
    packed.field29 = source->field24;
    packed.field28 = source->field20;
    packed.field3A = source->field1C;

    packed.field10 = fn_8017AC20(4, 16, source->field28);
    packed.field12 = fn_8017AC20(4, 16, source->field2C);
    packed.field3C = fn_8017AC20(4, 16, source->field38);
    packed.field38 = fn_8017AC20(4, 16, source->field34);
    packed.field18 = fn_8017AC20(9, 16, source->field48);
    packed.field1A = fn_8017AC20(9, 16, source->field4C);
    packed.field1C = fn_8017AC20(9, 16, source->field50);
    packed.field1E = fn_8017AC20(9, 16, source->field54);
    packed.field20 = fn_8017AC20(9, 16, source->field58);
    packed.field22 = fn_8017AC20(9, 16, source->field5C);

    packed.flags = 0;
    if (source->field3C != 0) {
        packed.flags |= 1;
    }
    if (source->field40 != 0) {
        packed.flags |= 2;
    }
    if (source->field68 == context) {
        packed.flags |= 4;
    }
    if (source->field60 == context) {
        packed.flags |= 8;
    }
    if (source->field6C != 0) {
        index = fn_801FAFF8(source->field6C);
        if (index != -1) {
            packed.field2A = index;
            packed.flags |= 0x10;
        }
    }
    if (source->field80 != 0) {
        index = fn_801FB0DC(source->field80);
        if (index != -1) {
            packed.field2B = index;
            packed.flags |= 0x20;
        }
    }
    if (source->field7C != 0) {
        index = fn_801FB118(source->field7C, alternate);
        if (index == -1) {
            index = fn_801FB270(context, source->field7C, alternate);
            if (index == -1) {
                fn_801F8694(source, alternate);
            } else {
                packed.field36 = index;
                packed.flags |= 0x80;
            }
        } else {
            packed.field36 = index;
            packed.flags |= 0x40;
        }
    }

    memcpy(output, &packed, sizeof(packed));
    return sizeof(packed);
}
