typedef int BOOL;
typedef signed int s32;

extern s32 CARDUnmount(s32 channel);

/* Allow reset once both memory cards are no longer busy. */
BOOL fn_8021D5F0(BOOL final)
{
    if (!final && (CARDUnmount(0) == -1 || CARDUnmount(1) == -1)) {
        return 0;
    }
    return 1;
}
