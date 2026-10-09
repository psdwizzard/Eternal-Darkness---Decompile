typedef signed int s32;
typedef unsigned int u32;

extern unsigned char lbl_80332540[];
extern unsigned char lbl_803A7840[];
extern unsigned char lbl_804E4E80[];
extern u32 lbl_8064CEBC[2];
extern unsigned char* lbl_8064CEC4;
extern s32 lbl_8064CEC8;
extern unsigned char* lbl_8064CECC;
extern s32 lbl_8064CED0;
extern unsigned char* lbl_8064CED4;
extern s32 lbl_8064CED8;
extern u32 lbl_8064CEDC[2];
extern s32 lbl_8064CEE4;
extern s32 lbl_8064CEE8;
extern s32 lbl_8064D738;

void fn_80120688(void)
{
    s32 index = lbl_8064D738;

    lbl_8064CEC4 = lbl_80332540 + index * 0x3A980;
    lbl_8064CECC = lbl_803A7840 + index * 0x9EB20;
    lbl_8064CED4 = lbl_804E4E80 + index * 0x4000;
    lbl_8064CEBC[index] = 0;
    lbl_8064CEC8 = 0x9EB20;
    lbl_8064CED8 = 0x400;
    lbl_8064CEDC[index] = 0;
    lbl_8064CEE4 = 0;
    lbl_8064CED0 = 0;
    lbl_8064CEE8 = 0;
}
