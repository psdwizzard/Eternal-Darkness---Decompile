typedef unsigned int u32;
typedef int s32;

typedef struct Entry Entry;
typedef struct Bank {
    Entry *base;
    u32 active;
    u32 unk[2];
} Bank;

typedef void (*Callback)(u32);

extern volatile s32 lbl_8064DBE0;
extern volatile u32 lbl_8064C4B4;
extern s32 lbl_8064DBE4;
extern Bank *lbl_8064DBEC;

extern s32 OSDisableInterrupts(void);
extern s32 OSRestoreInterrupts(s32);
extern Callback fn_80226814(Callback);
extern void fn_8022CBA0(u32);
extern void fn_8022C9F0(void);
extern void fn_8022C3A8(void);
extern void fn_80209B08(u32);
extern void fn_80209B10(u32);
extern void fn_80209B20(u32);
extern void fn_80209B30(u32);
extern void fn_80209AF0(int);
extern void fn_80209AF8(int);
extern void fn_8022D2C4(void);

void fn_8022CE20(void)
{
    s32 enabled = OSDisableInterrupts();

    lbl_8064DBE0 = 0;
    lbl_8064C4B4 = 0xFFFF;
    fn_80226814(fn_8022CBA0);
    lbl_8064DBEC[lbl_8064DBE4].active = 0;
    fn_8022C9F0();
    fn_8022C3A8();
    fn_80209B08(0);
    fn_80209B10(0);
    fn_80209B20(0);
    fn_80209B30(0);
    fn_80209AF0(0x8B);
    fn_80209AF8(0x78400000);
    fn_8022D2C4();
    OSRestoreInterrupts(enabled);
}
