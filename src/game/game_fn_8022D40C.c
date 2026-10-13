typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

typedef struct Entry {
    u8 state;
    u8 pad01[0x0B];
    u32 resource2;
    u32 resource0;
    u32 status;
    u8 pad18[0x04];
    u32 resource2b;
    u32 resource3b;
    u32 resource3;
    u8 pad28[0x08];
    u32 flagsb;
    u32 flags;
    u8 pad38[0x08];
    u32 memoryCounters[10][2];
    u32 graphicsCounters[4][2];
} Entry;

typedef struct Bank {
    Entry *base;
    u32 unk[3];
} Bank;

extern s32 lbl_8064C4B0;
extern s32 lbl_8064DBE4;
extern Bank *lbl_8064DBEC;
extern u32 fn_80209B00(void);
extern u32 fn_80209B18(void);
extern u32 fn_80209B28(void);
extern void fn_8022CA98(Entry *entry, s32 sample);

#define CURRENT_ENTRY (lbl_8064DBEC[lbl_8064DBE4].base[lbl_8064C4B0])

void fn_8022D40C(void)
{
    if (lbl_8064C4B0 >= 0) {
        CURRENT_ENTRY.resource0 = fn_80209B28();
        fn_8022CA98(&CURRENT_ENTRY, 1);
        CURRENT_ENTRY.resource3 = fn_80209B18();
        CURRENT_ENTRY.flags = fn_80209B00();
    }
    lbl_8064C4B0 = -1;
}
