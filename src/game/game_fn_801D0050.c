typedef unsigned int u32;
typedef signed int s32;

extern s32 fn_80144C40(void);
extern s32 fn_801A5CE0(void);
extern s32 fn_801A5D04(void);
extern s32 fn_80070A6C(s32);
extern s32 fn_801118E8(void);
extern s32 lbl_8064A80C;
extern s32 lbl_8064ABB8;

/*
 * Begins the event/state dispatch visible in retail.  The remaining switch
 * arms are deliberately left as NonMatching C until their object and entity
 * types are recovered; keeping this body in C makes the current divergence
 * reviewable without disguising compiler-codegen debt as assembly.
 */
s32 fn_801D0050(s32 mode, u32* event)
{
    u32 event_word = *event;

    fn_80144C40();
    if (fn_801A5CE0() == 0 && fn_801A5D04() == 0) {
        return 0;
    }
    if (fn_80070A6C(2) != 0) {
        return 0;
    }
    if (lbl_8064A80C == 83) {
        return 0;
    }
    if (mode != 0 && fn_801118E8() == 0) {
        return 0;
    }
    if (lbl_8064ABB8 != 0) {
        return 0;
    }

    switch (event_word & 0x00001FF0) {
    case 0x300:
    case 0x410:
    case 0x420:
    case 0x440:
    case 0x480:
    case 0x500:
    case 0x810:
    case 0x820:
    case 0x1010:
    case 0x1040:
        break;
    default:
        lbl_8064ABB8 = 0;
        break;
    }
    return 0;
}
