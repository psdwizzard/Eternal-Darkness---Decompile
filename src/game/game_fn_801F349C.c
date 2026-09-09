typedef unsigned char u8;

extern int lbl_8064D764;
extern u8 lbl_8064C384[4];
extern float lbl_8063C608[4];
extern float lbl_80651348;

int fn_801F349C(void)
{
    int result = 0;

    if (lbl_8064D764 != 0) {
        result = 1;
    }
    if (lbl_8064C384[0] != 0 || lbl_8064C384[1] != 0 ||
        lbl_8064C384[2] != 0 || lbl_8064C384[3] != 0) {
        result = 1;
    }
    if (lbl_8063C608[0] != lbl_80651348 ||
        lbl_8063C608[1] != lbl_80651348 ||
        lbl_8063C608[2] != lbl_80651348 ||
        lbl_8063C608[3] != lbl_80651348) {
        result = 1;
    }
    return result;
}
