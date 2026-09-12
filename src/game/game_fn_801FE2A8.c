typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Record {
    Vec3 position;
    u8 color[4];
    s32 value;
} Record;

typedef struct CopyData {
    u32 words[6];
} CopyData;

typedef struct Entry {
    u32 id;
    u32 field04;
    u32 field08;
    u32 field0C;
    u8 pad10[4];
    u32 field14;
    u32 mode;
    s16 field1C;
    s16 field1E;
    s16 field20;
    u16 state;
    u16 field24;
    u16 field26;
    u8 pad28;
    u8 flags;
    s16 field2A;
    u8 field2C;
    u8 field2D;
    u8 pad2E[2];
    u32 field30;
    Record record;
    CopyData copy48;
    u8 pad60[0xC];
    u32 callback;
    u16 field70;
    u8 pad72[2];
    u32 field74;
    u32 field78;
} Entry;

typedef struct Input {
    u32 value;
    u32 field04;
    u32 field08;
    u32 field0C;
    u32 field10;
    u32 field14;
    Vec3 position;
    u8 color[4];
    u16 field28;
    u16 options;
    s16 field2C;
    s16 field2E;
    s16 field30;
    u8 field32;
    u8 mode;
    u8 field34;
    u8 pad35[3];
    Vec3 vector;
    u32 callback;
    CopyData copy48;
} Input;

extern Entry* fn_801FD6F4(u32);
extern void fn_801FD6AC(Record*, const Vec3*, const u8*, u32);
extern void fn_801FE838(u32, float, float, float);
extern s32 lbl_8064D18C;

void fn_801FE2A8(Input* input, u32 id)
{
    Entry* entry = fn_801FD6F4(id);
    if (entry != 0) {
        s16 value = input->field30;
        s16 default_value = lbl_8064D18C;
        s32 mode;
        if (value != 0) {
            default_value = value;
        }
        entry->field2A = default_value;
        entry->flags = 0;
        fn_801FD6AC(&entry->record, &input->position, input->color, input->value);
        entry->field24 = input->field28;
        entry->field30 = 0;
        entry->field26 = 0;
        entry->field2C = input->field32;
        entry->field1C = input->field2C;
        entry->field1E = input->field2E;
        entry->field08 = input->field08;
        entry->field0C = input->field0C;
        entry->callback = input->callback;
        entry->state = 1;
        entry->field14 = 1;
        entry->field20 = (s16)(entry->record.value >> 5);
        entry->field74 = input->field10;
        entry->field78 = input->field14;
        entry->field04 = input->field04;
        entry->field2D = input->field34;
        entry->flags = 4;
        mode = (s8)input->mode;
        if ((s32)mode == 1) {
            entry->mode = mode;
            entry->copy48 = input->copy48;
        } else {
            entry->mode = 0;
        }
        if (input->options & 1) {
            fn_801FE838(id, input->vector.x, input->vector.y, input->vector.z);
        }
        if (input->options & 2) {
            entry->flags |= 1;
        }
        if (input->options & 8) {
            entry->flags &= ~4;
        }
        if (input->options & 0x10) {
            entry->flags |= 8;
        }
        if (input->options & 4) {
            entry->flags |= 2;
        }
        if (input->options & 0x40) {
            entry->flags |= 0x10;
        }
    }
}
