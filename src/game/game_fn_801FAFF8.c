extern void* lbl_802FC6D8[9];

int fn_801FAFF8(void* value)
{
    int i;
    for (i = 0; i < 9; i++) {
        if (lbl_802FC6D8[i] == value) {
            return i;
        }
    }
    return -1;
}
