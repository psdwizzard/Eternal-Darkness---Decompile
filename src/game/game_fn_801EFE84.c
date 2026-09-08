extern void* lbl_8064D700;

extern void fn_80218110(void);

void* fn_801EFE84(void* value)
{
    void* previous = lbl_8064D700;

    fn_80218110();
    lbl_8064D700 = value;
    return previous;
}
