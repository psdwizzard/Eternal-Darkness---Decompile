typedef signed int s32;

/* The verification routines use different views of the card control block. */
typedef struct CardControl CardControl;
typedef struct CARDControl CARDControl;
typedef struct SaveCtx SaveCtx;

extern s32 fn_8021F350(CardControl *control);
extern s32 fn_8021F5D4(CARDControl *control, int *outCurrent);
extern s32 fn_8021F814(SaveCtx *control, s32 *outIndex);

s32 fn_8021FA98(CardControl *control)
{
    s32 result;
    s32 errors;

    result = fn_8021F350(control);
    if (result < 0)
        return result;

    errors = fn_8021F5D4((CARDControl *)control, 0);
    errors += fn_8021F814((SaveCtx *)control, 0);
    switch (errors) {
    case 0:
        return 0;
    case 1:
        return -6;
    default:
        return -6;
    }
}
