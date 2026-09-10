typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct PackedRecord {
    u16 position[3];
    u16 flags;
    u32 field08;
    u32 field0C;
    short field10;
    short field12;
    float field14;
    short field18;
    short field1A;
    short field1C;
    short field1E;
    short field20;
    short field22;
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
    short field38;
    u8 field3A;
    u8 field3B;
    short field3C;
    u8 pad3E[2];
} PackedRecord;

typedef struct OutputRecord {
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
} OutputRecord;

extern void* memset(void*, int, unsigned long);
extern void* memcpy(void*, const void*, unsigned long);
extern void fn_80201B3C(void);
extern void* fn_80201BC8(void);
extern void fn_801FB9C8(u16*, float*);
extern void* fn_801FB0B8(int);
extern void* fn_801FB0F8(int);
extern void* fn_801FB1CC(int, int);
extern void* fn_801FB318(void*, int, int);

u16 fn_801FB6A4(PackedRecord* input, OutputRecord* output, int alternate, int copy)
{
    PackedRecord packed;
    OutputRecord result;
    void* context;

    fn_80201B3C();
    context = fn_80201BC8();
    memset(&result, 0, sizeof(result));
    memcpy(&packed, input, sizeof(packed));

    fn_801FB9C8(&packed.position[0], &result.position[0]);
    fn_801FB9C8(&packed.position[1], &result.position[1]);
    fn_801FB9C8(&packed.position[2], &result.position[2]);
    result.field0C = packed.field08;
    result.field14 = packed.field0C;
    result.field30 = packed.field14;
    result.field10 = packed.field3B;
    result.field18 = packed.field37;
    result.field84 = packed.field30;
    result.field78 = packed.field2C;
    result.field64 = packed.field24;
    result.field44 = packed.field34;
    result.field24 = packed.field29;
    result.field20 = packed.field28;
    result.field1C = (signed char)packed.field3A;

    result.field28 = packed.field10 * 0.0625f;
    result.field2C = packed.field12 * 0.0625f;
    result.field38 = packed.field3C * 0.0625f;
    result.field34 = packed.field38 * 0.0625f;
    result.field48 = packed.field18 * 0.001953125f;
    result.field4C = packed.field1A * 0.001953125f;
    result.field50 = packed.field1C * 0.001953125f;
    result.field54 = packed.field1E * 0.001953125f;
    result.field58 = packed.field20 * 0.001953125f;
    result.field5C = packed.field22 * 0.001953125f;

    result.field3C = packed.flags & 1;
    result.field40 = packed.flags & 2;
    if (packed.flags & 4) {
        result.field68 = context;
    } else {
        result.field68 = 0;
    }
    if (packed.flags & 8) {
        result.field60 = context;
    } else {
        result.field60 = 0;
    }
    if (packed.flags & 0x10) {
        result.field6C = fn_801FB0B8(packed.field2A);
    }
    if (packed.flags & 0x20) {
        result.field80 = fn_801FB0F8(packed.field2B);
    }
    if (packed.flags & 0x40) {
        result.field7C = fn_801FB1CC(packed.field36, alternate);
    } else if (packed.flags & 0x80) {
        result.field7C = fn_801FB318(context, packed.field36, alternate);
    } else {
        result.field7C = 0;
    }

    if (copy) {
        *output = result;
    }
    return sizeof(packed);
}
