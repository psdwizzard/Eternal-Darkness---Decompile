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

/* Interrupt-visible profiler state: fn_8022DA54 installs this function as
 * an OS alarm callback. fn_8022CE20 also installs fn_8022CBA0 via fn_80226814
 * as the PE token callback, dispatched by fn_80226858. That callback checks
 * the bank discriminator (DBD8), changes the token (C4B4), and calls the
 * entry start/finish routines, which update C4B0 and DBE0. The allocation
 * parameters below are not changed by the token callback. */
extern volatile s32 lbl_8064C4B0;
extern volatile u32 lbl_8064C4B4;
extern volatile u8 lbl_8064DBD8;
extern volatile s32 lbl_8064DBE0;
extern s32 lbl_8064DBE4;
extern Bank *lbl_8064DBEC;
extern s32 lbl_8064DBF0;
extern const char lbl_802FF7EC[];
extern u32 fn_80209B00(void);
extern u32 fn_80209B18(void);
extern u32 fn_80209B28(void);
extern void fn_8022CA98(Entry *, s32);
extern void OSReport(const char *, ...);
extern void *memcpy(void *, const void *, u32);

#define ENTRY_AT(n) (lbl_8064DBEC[lbl_8064DBE4].base[(n)])

static inline s32 AllocateEntry(void)
{
    if ((u32)lbl_8064DBE0 >= (u32)(lbl_8064DBF0 - 1)) {
        lbl_8064DBE0 = lbl_8064DBF0 - 1;
        return lbl_8064DBE0;
    }
    return lbl_8064DBE0++;
}

static inline void FinishEntry(void)
{
    if (lbl_8064C4B0 >= 0) {
        ENTRY_AT(lbl_8064C4B0).resource0 = fn_80209B28();
        fn_8022CA98(&ENTRY_AT(lbl_8064C4B0), 1);
        ENTRY_AT(lbl_8064C4B0).resource3 = fn_80209B18();
        ENTRY_AT(lbl_8064C4B0).flags = fn_80209B00();
    }
    lbl_8064C4B0 = -1;
}

static inline void StartEntry(void)
{
    lbl_8064C4B0 = AllocateEntry();
    ENTRY_AT(lbl_8064C4B0).state = 0xFF;
    ENTRY_AT(lbl_8064C4B0).status = 0;
    fn_8022CA98(&ENTRY_AT(lbl_8064C4B0), 0);
    ENTRY_AT(lbl_8064C4B0).resource2 = fn_80209B28();
    ENTRY_AT(lbl_8064C4B0).resource0 = 0;
    ENTRY_AT(lbl_8064C4B0).resource3b = fn_80209B18();
    ENTRY_AT(lbl_8064C4B0).flagsb = fn_80209B00();
}

/* Decode the entry index and return the bank encoded in the token. */
static inline s32 DecodeToken(s32 *source)
{
    *source = lbl_8064C4B4 & 0xFF;
    return (lbl_8064C4B4 >> 8) & 0xF;
}

void fn_8022D4CC(void)
{
    s32 source;
    s32 slot;
    s32 bank;
    if (lbl_8064DBE0 == 0)
        return;
    if (lbl_8064C4B4 < 0xFFFF) {
        bank = DecodeToken(&source);
        if (bank != lbl_8064DBD8) {
            FinishEntry();
            StartEntry();
            return;
        }
        slot = AllocateEntry();
        memcpy(&ENTRY_AT(slot), &ENTRY_AT(source), sizeof(Entry));
        ENTRY_AT(slot).resource0 = fn_80209B28();
        ENTRY_AT(slot).resource3 = fn_80209B18();
        ENTRY_AT(slot).flags = fn_80209B00();
        fn_8022CA98(&ENTRY_AT(slot), 1);
        ENTRY_AT(slot).state = 0xFF;
        ENTRY_AT(source).resource2 = fn_80209B28();
        ENTRY_AT(source).resource3b = fn_80209B18();
        ENTRY_AT(source).flagsb = fn_80209B00();
        fn_8022CA98(&ENTRY_AT(source), 0);
        ENTRY_AT(source).status = 1;
        lbl_8064C4B0 = -1;
        return;
    }
    if (lbl_8064C4B0 < 0) {
        OSReport(lbl_802FF7EC);
        return;
    }
    FinishEntry();
    StartEntry();
}
