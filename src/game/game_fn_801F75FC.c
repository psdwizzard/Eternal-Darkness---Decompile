extern int lbl_8064D7B8;
extern int lbl_8064D7B4;
extern float lbl_8064D7AC;
extern unsigned char lbl_8063D400[];

void fn_801F7620(void* state);

void fn_801F75FC(int first, int second, float amount)
{
    lbl_8064D7B8 = first;
    lbl_8064D7B4 = second;
    lbl_8064D7AC = amount;
    *(void (**)(void*))(lbl_8063D400 + 0x6C) = fn_801F7620;
}
