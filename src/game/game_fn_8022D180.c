typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

typedef struct Entry {
    u8 state;
    u8 pad01[0x07];
    u32 resource0;
    u8 pad0C[0x20];
    u32 resource3;
    u8 pad30[0x0C];
    u32 flags;
    u8 pad40[0x70];
} Entry;
typedef struct Bank { Entry *base; u32 unk[3]; } Bank;

typedef struct Request {
    u32 unk0;
    s32 type;
    s32 slot;
    u32 unkC;
} Request;

extern u8 lbl_8064DBD8;
extern s32 lbl_8064DBE4;
extern Request *lbl_8064DBE8;
extern Bank *lbl_8064DBEC;
extern const char lbl_802FF7C0[];
extern s32 OSDisableInterrupts(void);
extern s32 OSRestoreInterrupts(s32);
extern void OSReport(const char *, ...);
extern u32 fn_80209B00(void);
extern u32 fn_80209B18(void);
extern u32 fn_80209B28(void);
extern void fn_802264D4(u32);

#define ENTRIES (lbl_8064DBEC[lbl_8064DBE4].base)

void fn_8022D180(u8 id)
{
    s32 enabled = OSDisableInterrupts();
    s32 slot = lbl_8064DBE8[id].slot;

    if (slot < 0) {
        OSReport(lbl_802FF7C0);
        OSRestoreInterrupts(enabled);
        return;
    }

    switch (lbl_8064DBE8[id].type) {
    case 2:
        fn_802264D4((u16)slot + 0xF000 + ((lbl_8064DBD8 << 8) & 0xFF00));
        break;
    case 1:
        fn_802264D4((u16)slot + 0xF000 + ((lbl_8064DBD8 << 8) & 0xFF00));
    case 0:
        ENTRIES[slot].resource0 = fn_80209B28();
        ENTRIES[slot].resource3 = fn_80209B18();
        ENTRIES[slot].flags = fn_80209B00();
        break;
    }
    lbl_8064DBE8[id].slot = -1;
    OSRestoreInterrupts(enabled);
}
