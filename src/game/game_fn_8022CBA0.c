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
    u8 pad38[0x78];
} Entry;
typedef struct Bank { Entry *base; u32 unk[3]; } Bank;

extern s32 lbl_8064C4B0;
extern volatile u32 lbl_8064C4B4;
extern u8 lbl_8064DBD8;
extern void (*lbl_8064DBDC)(u32);
extern s32 lbl_8064DBE0;
extern s32 lbl_8064DBE4;
extern Bank *lbl_8064DBEC;
extern u32 fn_80209B00(void);
extern u32 fn_80209B18(void);
extern u32 fn_80209B28(void);
extern void fn_8022CA98(Entry *, s32);
extern void fn_8022D2C4(void);
extern void fn_8022D40C(void);

#define ENTRIES (lbl_8064DBEC[lbl_8064DBE4].base)

void fn_8022CBA0(u32 arg)
{
    u16 code = arg;
    s32 slot;
    u32 res;

    if (code < 0xE000 || ((code >> 8) & 0xF) != lbl_8064DBD8 || lbl_8064DBE0 == 0) {
        if (lbl_8064DBDC != 0)
            lbl_8064DBDC(arg);
    } else {
        if (code >= 0xF000) {
            if (lbl_8064C4B4 == 0xFFFF) {
                fn_8022D40C();
                fn_8022D2C4();
            } else {
                slot = (u8)code;
                if ((u8)lbl_8064C4B4 != slot)
                    slot = (u8)lbl_8064C4B4;
                ENTRIES[slot].resource0 = fn_80209B28();
                ENTRIES[slot].resource3 = fn_80209B18();
                ENTRIES[slot].flags = fn_80209B00();
                fn_8022CA98(&ENTRIES[slot], 1);
                if (lbl_8064C4B0 >= 0)
                    fn_8022D40C();
                lbl_8064C4B4 = 0xFFFF;
                fn_8022D2C4();
            }
        } else {
            if (lbl_8064C4B4 < 0xFFFF) {
                slot = (u8)lbl_8064C4B4;
                ENTRIES[slot].resource0 = fn_80209B28();
                ENTRIES[slot].resource3 = fn_80209B18();
                ENTRIES[slot].flags = fn_80209B00();
                fn_8022CA98(&ENTRIES[slot], 1);
            } else {
                fn_8022D40C();
            }
            slot = (u8)code;
            ENTRIES[slot].resource3b = fn_80209B18();
            ENTRIES[slot].flagsb = fn_80209B00();
            res = fn_80209B28();
            ENTRIES[slot].resource2b = res;
            ENTRIES[slot].resource2 = res;
            fn_8022CA98(&ENTRIES[slot], 0);
            lbl_8064C4B4 = (u16)arg;
        }
    }
}
