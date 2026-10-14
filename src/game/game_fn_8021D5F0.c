typedef int BOOL;
typedef signed int s32;

extern s32 fn_80220B4C(s32 channel);

/* Allow reset once both memory cards are no longer busy. */
BOOL fn_8021D5F0(BOOL final)
{
    if (!final && (fn_80220B4C(0) == -1 || fn_80220B4C(1) == -1)) {
        return 0;
    }
    return 1;
}
