typedef signed int s32;

s32 Si_802FCA20[5] = { -1 };

s32 SIBusy(void)
{
    if (Si_802FCA20[0] != -1) {
        return 1;
    }
    return 0;
}
