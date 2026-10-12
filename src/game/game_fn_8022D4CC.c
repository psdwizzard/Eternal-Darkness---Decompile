typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

typedef struct Entry {
    u8 state;
    u8 pad01[0x0B];
    u32 resource2;
    u32 resource0;
    u32 status;
    u8 pad18[0x0C];
    u32 resource3;
    u8 pad28[0x0C];
    u32 flags;
    u8 pad38[0x78];
} Entry;
typedef struct Bank { Entry *base; u32 unk[3]; } Bank;

extern s32 lbl_8064C4B0;
extern u32 lbl_8064C4B4;
extern u8 lbl_8064DBD8;
extern s32 lbl_8064DBE0;
extern s32 lbl_8064DBE4;
extern Bank *lbl_8064DBEC;
extern s32 lbl_8064DBF0;
extern const char lbl_802FF7EC[];
extern u32 fn_80209B00(void);
extern u32 fn_80209B18(void);
extern u32 fn_80209B28(void);
extern void fn_8022CA98(Entry *, s32);
extern void OSReport(const char *);
extern void *memcpy(void *, const void *, u32);

#define ENTRY_AT(n) ((Entry *)((u8 *)lbl_8064DBEC[lbl_8064DBE4].base + (n) * 0xB0))

void fn_8022D4CC(void)
{
    Entry *e;
    s32 slot;
    s32 old;
    if (lbl_8064DBE0 == 0)
        return;
    if (lbl_8064C4B4 < 0xFFFF) {
        if (((lbl_8064C4B4 >> 8) & 0xF) != lbl_8064DBD8) {
            if (lbl_8064C4B0 >= 0) {
                e = ENTRY_AT(lbl_8064C4B0);
                e->resource0 = fn_80209B28();
                fn_8022CA98(e, 1);
                e->resource3 = fn_80209B18();
                e->flags = fn_80209B00();
            }
            lbl_8064C4B0 = -1;
            slot = lbl_8064DBE0;
            if ((u32)slot >= (u32)(lbl_8064DBF0 - 1))
                slot = lbl_8064DBE0 = lbl_8064DBF0 - 1;
            else
                lbl_8064DBE0 = slot + 1;
            lbl_8064C4B0 = slot;
            e = ENTRY_AT(slot);
            e->state = 0xFF;
            e->flags = 0;
            fn_8022CA98(e, 0);
            e->resource2 = fn_80209B28();
            e->resource0 = 0;
            e->resource3 = fn_80209B18();
            e->flags = fn_80209B00();
            return;
        }
        old = lbl_8064C4B4 & 0xFF;
        slot = lbl_8064DBE0;
        if ((u32)slot >= (u32)(lbl_8064DBF0 - 1))
            slot = lbl_8064DBE0 = lbl_8064DBF0 - 1;
        else
            lbl_8064DBE0 = slot + 1;
        e = ENTRY_AT(slot);
        memcpy(e, ENTRY_AT(old), 0xB0);
        e->resource0 = fn_80209B28();
        e->resource3 = fn_80209B18();
        e->flags = fn_80209B00();
        fn_8022CA98(e, 1);
        e->state = 0xFF;
        e = ENTRY_AT(old);
        e->resource2 = fn_80209B28();
        e->resource3 = fn_80209B18();
        e->flags = fn_80209B00();
        fn_8022CA98(e, 0);
        e->status = 1;
        lbl_8064C4B0 = -1;
        return;
    }
    if (lbl_8064C4B0 < 0) {
        OSReport(lbl_802FF7EC);
        return;
    }
    if (lbl_8064C4B0 >= 0) {
        e = ENTRY_AT(lbl_8064C4B0);
        e->resource0 = fn_80209B28();
        fn_8022CA98(e, 1);
        e->resource3 = fn_80209B18();
        e->flags = fn_80209B00();
    }
    lbl_8064C4B0 = -1;
    slot = lbl_8064DBE0;
    if ((u32)slot >= (u32)(lbl_8064DBF0 - 1))
        slot = lbl_8064DBE0 = lbl_8064DBF0 - 1;
    else
        lbl_8064DBE0 = slot + 1;
    lbl_8064C4B0 = slot;
    e = ENTRY_AT(slot);
    e->state = 0xFF;
    e->flags = 0;
    fn_8022CA98(e, 0);
    e->resource2 = fn_80209B28();
    e->resource0 = 0;
    e->resource3 = fn_80209B18();
    e->flags = fn_80209B00();
}
