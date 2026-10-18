typedef signed int s32;

/* The verification routines use different views of the card control block. */
typedef struct CardControl CardControl;
typedef struct CARDControl CARDControl;
typedef struct SaveCtx SaveCtx;

extern s32 VerifyID(CardControl *control);
extern s32 VerifyDir(CARDControl *control, int *outCurrent);
extern s32 VerifyFAT(SaveCtx *control, s32 *outIndex);

s32 __CARDVerify(CardControl *control)
{
    s32 result;
    s32 errors;

    result = VerifyID(control);
    if (result < 0)
        return result;

    errors = VerifyDir((CARDControl *)control, 0);
    errors += VerifyFAT((SaveCtx *)control, 0);
    switch (errors) {
    case 0:
        return 0;
    case 1:
        return -6;
    default:
        return -6;
    }
}
