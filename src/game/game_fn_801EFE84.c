extern void* lbl_8064D700;

extern void VISetBlack(void);

void* fn_801EFE84(void* value)
{
    void* previous = lbl_8064D700;

    VISetBlack();
    lbl_8064D700 = value;
    return previous;
}
