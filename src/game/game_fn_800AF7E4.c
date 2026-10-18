extern int CARDProbeEx(int, int*, int*);

int fn_800AF7E4(int index, int* status)
{
    int value;
    int flags;

    *status = CARDProbeEx(index, &value, &flags);
    if (*status == 0) {
        if (flags == 0x2000) {
            return 1;
        }
        return -2;
    }
    return -1;
}
