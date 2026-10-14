typedef unsigned int u32;
typedef int s32;
typedef void (*DVDLowCallback)(u32 intType);

extern s32 fn_80212BE0(DVDLowCallback callback);
extern void fn_80213E3C(u32 error);

void fn_80213D60(void) {
    fn_80212BE0(fn_80213E3C);
}
