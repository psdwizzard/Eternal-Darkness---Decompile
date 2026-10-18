typedef unsigned char u8;
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
extern s32 lbl_8064DBE0;
extern s32 lbl_8064DBE4;
extern Bank *lbl_8064DBEC;
extern s32 lbl_8064DBF0;
extern u32 fn_80209B00(void);
extern u32 fn_80209B18(void);
extern u32 fn_80209B28(void);
extern void fn_8022CA98(Entry *, s32);

#define ENTRY_AT(n) (lbl_8064DBEC[lbl_8064DBE4].base[(n)])

/* The entry count and current index are shared with interrupt callbacks.
 * fn_8022CE20 installs fn_8022CBA0 through fn_80226814; the PE token
 * interrupt handler fn_80226858 dispatches it. fn_8022CBA0 calls this
 * routine and fn_8022D40C. The alarm callback fn_8022D4CC, registered by
 * fn_8022DA54, also allocates entries and changes the current index.
 * Qualify accesses to that shared state while retaining the globals' s32
 * declarations used by the entry start/finish and token callback units. */
#define ENTRY_COUNT (*(volatile s32 *)&lbl_8064DBE0)
#define CURRENT_INDEX (*(volatile s32 *)&lbl_8064C4B0)

static inline s32 AllocateEntry(void)
{
    if ((u32)ENTRY_COUNT >= (u32)(lbl_8064DBF0 - 1)) {
        ENTRY_COUNT = lbl_8064DBF0 - 1;
        return ENTRY_COUNT;
    }
    return ENTRY_COUNT++;
}

void fn_8022D2C4(void)
{
    CURRENT_INDEX = AllocateEntry();
    ENTRY_AT(CURRENT_INDEX).state = 0xFF;
    ENTRY_AT(CURRENT_INDEX).status = 0;
    fn_8022CA98(&ENTRY_AT(CURRENT_INDEX), 0);
    ENTRY_AT(CURRENT_INDEX).resource2 = fn_80209B28();
    ENTRY_AT(CURRENT_INDEX).resource0 = 0;
    ENTRY_AT(CURRENT_INDEX).resource3b = fn_80209B18();
    ENTRY_AT(CURRENT_INDEX).flagsb = fn_80209B00();
}
