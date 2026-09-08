typedef unsigned char u8;
typedef unsigned int u32;
extern int lbl_8064D650;
extern u32 fn_801EB30C(void);
void fn_801EB8AC(u8* object)
{
    if (lbl_8064D650 != 0)
        *(u32*)(object + 8) = fn_801EB30C();
}
