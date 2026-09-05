typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad00[0x24];
    u32 flags24;
    u8 pad28[0x24];
    u16 colors[3][3];
    u8 pad5E[0x72];
    u16 fieldD0;
    u16 fieldD2;
    u8 padD4[0x11];
    u8 color_valid[3];
    u8 padE8[7];
    u8 group;
    u32 flagsF0;
} Entry;

typedef struct Group {
    u8 pad00[0x54];
    u32 alternate_layout;
    u8 pad58[0x64];
} Group;

extern Entry* lbl_8064D4AC;
extern Group lbl_80628CB0[];
extern volatile u16 lbl_8023B458[];
extern volatile float lbl_80651020;
extern volatile float lbl_80651024;

extern void fn_801C79C8(u8 table_kind, float* output, u32 packed_min,
                        u32 packed_max, float x, float y, float z,
                        u32 bias_x, u32 alternate_layout);

void fn_801CCCC4(u32 index, u8 table_kind, u32 packed_min, u32 packed_max,
                 float x, float y, float z)
{
    float output[9];
    Entry* entry;
    int red;
    int green;
    int blue;
    float value;

    entry = &lbl_8064D4AC[index];
    value = lbl_80651020;
    if (x >= value) {
        x = value;
    }
    value = lbl_80651020;
    if (y >= value) {
        y = value;
    }
    value = lbl_80651020;
    if (z >= value) {
        z = value;
    }

    fn_801C79C8(table_kind, output, packed_min, packed_max, x, y, z,
                (entry->flagsF0 & 0x80000000) != 0,
                lbl_80628CB0[entry->group].alternate_layout == 1);

    value = lbl_80651024;
    red = value * output[0];
    green = value * output[1];
    blue = value * output[2];
    if (entry->color_valid[0] == 0xFF ||
        entry->colors[0][0] != (u16)red ||
        entry->colors[0][1] != (u16)green ||
        entry->colors[0][2] != (u16)blue) {
        entry->colors[0][0] = red;
        entry->colors[0][1] = green;
        entry->colors[0][2] = blue;
        entry->flags24 |= 1;
        entry->color_valid[0] = 0;
    }

    value = lbl_80651024;
    red = value * output[3];
    green = value * output[4];
    blue = value * output[5];
    if (entry->color_valid[1] == 0xFF ||
        entry->colors[1][0] != (u16)red ||
        entry->colors[1][1] != (u16)green ||
        entry->colors[1][2] != (u16)blue) {
        entry->colors[1][0] = red;
        entry->colors[1][1] = green;
        entry->colors[1][2] = blue;
        entry->flags24 |= 2;
        entry->color_valid[1] = 0;
    }

    value = lbl_80651024;
    red = value * output[6];
    green = value * output[7];
    blue = value * output[8];
    if (entry->color_valid[2] == 0xFF ||
        entry->colors[2][0] != (u16)red ||
        entry->colors[2][1] != (u16)green ||
        entry->colors[2][2] != (u16)blue) {
        entry->colors[2][0] = red;
        entry->colors[2][1] = green;
        entry->colors[2][2] = blue;
        entry->flags24 |= 4;
        entry->color_valid[2] = 0;
    }

    if ((entry->flagsF0 & 0x80000000) != 0) {
        entry->fieldD0 = lbl_8023B458[(packed_min >> 16) & 0xFF];
        entry->fieldD2 = 0x20 - lbl_8023B458[(packed_min >> 16) & 0xFF];
        entry->flags24 |= 0x200;
    }
}
