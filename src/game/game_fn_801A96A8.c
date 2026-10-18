extern int lbl_8064D294;

extern void OSSetSoundMode(int);
extern unsigned int OSGetSoundMode(void);
extern void sndOutputMode(int);

void fn_801A96A8(int mode, int apply, int notify)
{
    unsigned int state;

    if (apply != 0) {
        if (mode == 0) {
            OSSetSoundMode(0);
        } else {
            OSSetSoundMode(1);
        }
    }

    state = OSGetSoundMode();
    if (state == 0) {
        lbl_8064D294 = 0;
    } else if (state == 1) {
        if (mode == 2) {
            lbl_8064D294 = 2;
        } else {
            lbl_8064D294 = 1;
        }
    } else {
        lbl_8064D294 = 1;
    }

    if (notify != 0) {
        sndOutputMode(lbl_8064D294);
    }
}
