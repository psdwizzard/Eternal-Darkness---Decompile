typedef unsigned int u32;
typedef struct Group { u32 count; u32 width; } Group;
typedef struct Slot {
    void* owner;
    u32 capacity;
    void* data;
    int field_C;
    int field_10;
    unsigned short tag;
    unsigned char state;
    unsigned char pad_17;
} Slot;

extern int fn_801358B4(int);
extern void fn_80126084(void);
extern void fn_80134FD8(Slot*, u32, void*);
extern void* memset(void*, int, unsigned long);
extern Slot* lbl_8064CF88;
extern void* lbl_8064CF80;
extern Group* lbl_8064CF90;
extern int lbl_8064CF8C;
extern u32 lbl_8064CF94;
extern int lbl_8064CF9C;
extern int lbl_8064CFA0;
extern unsigned char lbl_8064CFA4;
extern u32 lbl_8064CFAC;

void fn_80134CAC(u32* values, int group_count)
{
    u32 total = 0;
    int i;
    u32 offset;
    u32 record;

    lbl_8064CFA0 = 0;
    lbl_8064CF9C = 0;
    lbl_8064CFA4 = 0;
    fn_801358B4(1);

    for (i = 0; i < group_count; i++) {
        total += values[i * 2];
    }
    lbl_8064CFAC = total;
    memset(lbl_8064CF88, 0, 0x90);
    lbl_8064CF8C = group_count;
    lbl_8064CF90 = (Group*)values;
    fn_80126084();

    offset = 0;
    record = 0;
    lbl_8064CF94 = 0;
    for (i = 0; i < group_count; i++) {
        Group* group = (Group*)((char*)lbl_8064CF90 + i * 8);
        u32 j;
        Slot* slot = &lbl_8064CF88[record];
        if (lbl_8064CF94 < group->width)
            lbl_8064CF94 = group->width;
        for (j = 0; j < group->count; j++) {
            fn_80134FD8(slot, group->width, (char*)lbl_8064CF80 + offset);
            slot++;
            record++;
            offset += group->width;
        }
    }
}
