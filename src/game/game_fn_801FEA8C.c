typedef unsigned int u32;

extern void* lbl_8064C3C8;
extern char lbl_802FC848[];
extern char lbl_802FC85C[];

extern void* fn_8020AD80(void*, u32);
extern void fn_8020B344(void*);
extern void fn_801E7DC8(int);
extern void fn_80155BB0(const char*, const char*, ...);

void* fn_801FEA8C(u32 size, int report, const char* source, int line)
{
    void* result = fn_8020AD80(lbl_8064C3C8, size);
    if (result == 0) {
        if (report != 0) {
            fn_8020B344(lbl_8064C3C8);
        }
        fn_801E7DC8(0x28);
        fn_801E7DC8(0x206);
        fn_801E7DC8(0x100);
        if (report != 0) {
            fn_80155BB0(lbl_802FC848, lbl_802FC85C, size);
        }
    }
    return result;
}
