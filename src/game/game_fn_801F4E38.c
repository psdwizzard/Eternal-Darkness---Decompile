typedef unsigned char u8;

extern u8 lbl_802FC678[];
extern float lbl_8064C394;
extern float lbl_8064C398;
extern void* memcpy(void*, const void*, unsigned long);

int fn_801F4E38(u8* destination)
{
    memcpy(destination, lbl_802FC678, 12);
    memcpy(destination + 12, &lbl_8064C394, 4);
    memcpy(destination + 16, &lbl_8064C398, 4);
    return 32;
}
