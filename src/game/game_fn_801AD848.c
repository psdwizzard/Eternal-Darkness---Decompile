extern int lbl_8064D300;
extern unsigned int DTKGetState(void);
extern unsigned int DTKGetTrackPosition(void);
extern unsigned int fn_801AD7C0(unsigned int, int);

unsigned int fn_801AD848(void)
{
    if (lbl_8064D300 == 3 || lbl_8064D300 == 2) {
        if (DTKGetState() == 1) {
            return fn_801AD7C0(DTKGetTrackPosition(), 4);
        }
    }
    return 0;
}
