typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

extern s32 lbl_8064C890;
extern const u32 lbl_8064E5F4;
extern const u16 lbl_8064E5F8;

extern void *fn_801A717C(void);
extern void fn_801A7470(void *, s32);
extern void fn_801A74A0(void *, void *);
extern void fn_801A74A8(void *, void *);
extern unsigned long long fn_8020123C();
#define FN_80128E30_RETURN void*
#define FN_80128E30_PARAMETERS void*
extern FN_80128E30_RETURN fn_80128E30(FN_80128E30_PARAMETERS);
extern s32 fn_80128EAC(void *);
extern void fn_80128B10(void *, u16);
extern void fn_801A7228(void *);

void fn_80060C28(void *owner, void *resource, void *target)
{
    void *event = fn_801A717C();

    fn_801A7470(event, 0x10);
    fn_801A74A0(event, owner);
    fn_801A74A8(event, owner);
    fn_8020123C(0x35, owner, owner, event);

    if (fn_80128E30(resource) != 0 && fn_80128EAC(resource) == 0x10) {
        u16 values[3];

        *(u32 *)values = lbl_8064E5F4;
        values[2] = lbl_8064E5F8;

        if (lbl_8064C890 < 0 || lbl_8064C890 >= 3) {
            lbl_8064C890 = 0;
        }
        fn_80128B10(resource, values[lbl_8064C890]);
        lbl_8064C890 = (lbl_8064C890 >= 2) ? 0 : lbl_8064C890 + 1;
    }

    ((u8 *)*(void **)((u8 *)target + 8))[0x89] |= 2;
    fn_801A7228(event);
}
