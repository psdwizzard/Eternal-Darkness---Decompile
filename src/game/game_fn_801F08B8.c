typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct DrawInput {
    u16 count;
    u16 pad;
    u16* vertices;
    u32 pad8;
    int index;
} DrawInput;

typedef struct Entry {
    u8 pad0[10];
    s16 field_a;
    u8 pad_c[2];
    s16 field_e;
    u8 pad_10[8];
    u32 flags;
    u8 pad_1c[3];
    u8 field_1f;
} Entry;

typedef struct EntryOwner { u8 pad[12]; Entry* entries; } EntryOwner;

extern int lbl_8064D728;
extern u8 lbl_8064D5F8;
extern void fn_801ECEC8(int, int, int);
extern int fn_801ED59C(int, int);
extern void fn_8022A044(int, int, int, int, int);
extern void fn_801ECF50(int);
extern void fn_801EDA7C(Entry*, void*, int, int);
extern void fn_801EB8AC(DrawInput*);
extern void fn_80226AB4(int, int, int);
extern void fn_801F0B18(u16);
extern void fn_801F0B0C(u16);
extern void fn_801F0B00(u16);
extern void fn_801F0AFC(void);

void fn_801F08B8(DrawInput* input, EntryOwner* owner, void* value)
{
    int special;
    int format;
    int i;
    int offset;
    Entry* entries = owner->entries;
    Entry* entry = &entries[input->index];

    lbl_8064D728++;
    special = entry->field_e == -1;
    if (entry->field_a != -1 || entry->field_1f != 0xFF) {
        fn_801ECEC8(1, 3, 0);
        if (fn_801ED59C(1, 0) != 1)
            fn_8022A044(7, 0, 0, 3, 0xFF);
    } else if (entry->flags & 0x20000000) {
        fn_801ECEC8(1, 3, 1);
        if (fn_801ED59C(0, 0) != 0)
            fn_8022A044(4, 0x80, 0, 3, 0xFF);
    } else {
        fn_801ECEC8(1, 3, 1);
        if (fn_801ED59C(1, 0) != 1)
            fn_8022A044(7, 0, 0, 3, 0xFF);
    }

    switch (lbl_8064D5F8) {
    case 0: format = 1; break;
    case 1: format = 2; break;
    case 2: format = 3; break;
    }
    if (special) {
        special = 4;
        fn_801ECF50(0);
    } else {
        special = 0;
        fn_801ECF50(2);
    }
    fn_801EDA7C(entry, value, 0x2B3, 0);
    fn_801EB8AC(input);
    fn_80226AB4(0x98, special, input->count);
    format <<= 1;
    for (i = 0, offset = 0; i < input->count; i++, offset += 12) {
        fn_801F0B18(*(u16*)((u8*)input->vertices + offset));
        fn_801F0B0C(*(u16*)((u8*)input->vertices + offset + 2));
        fn_801F0B00(*(u16*)((u8*)input->vertices + offset + 4));
        fn_801F0B00(*(u16*)((u8*)input->vertices + offset + 4 + format));
    }
    fn_801F0AFC();
}
