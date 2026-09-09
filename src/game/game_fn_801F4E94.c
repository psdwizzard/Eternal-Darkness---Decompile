typedef unsigned char u8;

extern u8 lbl_802FC678[];
extern float lbl_8064C394;
extern float lbl_8064C398;
extern void* memcpy(void*, const void*, unsigned long);

int fn_801F4E94(u8* source)
{
    memcpy(lbl_802FC678, source, 12);
    memcpy(&lbl_8064C394, source + 12, 4);
    memcpy(&lbl_8064C398, source + 16, 4);
    return 32;
}
