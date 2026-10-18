extern void* memset(void*, int, unsigned int);

typedef struct PadStatus {
    unsigned short button;
    signed char stickX;
    signed char stickY;
    signed char substickX;
    signed char substickY;
    unsigned char triggerL;
    unsigned char triggerR;
    unsigned char analogA;
    unsigned char analogB;
    signed char err;
} PadStatus;

typedef struct PadState {
    unsigned int held;
    unsigned int pressed;
    short stickX;
    short stickY;
    short substickX;
    short substickY;
    unsigned short triggerL;
    unsigned short triggerR;
    unsigned short analogA;
    unsigned short analogB;
    short prevStickX;
    short prevStickY;
    short prevSubstickX;
    short prevSubstickY;
} PadState;

typedef struct Entry {
    int field0;
    int field4;
    int field8;
    int fieldC;
    int state;
    int owner;
    int field18;
    unsigned int flags;
} Entry;

extern PadStatus lbl_805B40C0[4];
extern PadState lbl_805B40F0[4];
extern Entry lbl_805B4170[20];
extern int lbl_8064CA64;
extern int lbl_8064D04C;
extern unsigned int lbl_8064D050;
extern void (*lbl_8064D054)(void);
extern void (*lbl_8064D058)(void);
extern int lbl_8064D05C;
extern int lbl_8064D060;
extern int lbl_8064D064;
extern int lbl_8064D068;
extern int lbl_8064D074;
extern int lbl_8064D078;

extern void PADRead(PadStatus* status);
extern void PADClamp(PadStatus* status);
extern void fn_80145408(unsigned int ticks);
extern void fn_80144F8C(void);

void fn_80145004(void)
{
    PadState* pad;
    PadStatus* status;
    Entry* entry;
    Entry* end;
    int buttons;
    int i;

    PADRead(lbl_805B40C0);
    while (lbl_805B40C0[0].err < -1) {
        fn_80145408(0xFB90);
        PADRead(lbl_805B40C0);
    }
    lbl_8064D04C = lbl_805B40C0[0].err;
    PADClamp(lbl_805B40C0);

    pad = lbl_805B40F0;
    status = lbl_805B40C0;
    for (i = 0; i < 4; i++) {
        pad->prevStickX = pad->stickX;
        buttons = status->button;
        pad->prevStickY = pad->stickY;
        pad->prevSubstickX = pad->substickX;
        pad->prevSubstickY = pad->substickY;
        if (status->stickX > 0) {
            buttons |= 0x20000;
        } else if (status->stickX < 0) {
            buttons |= 0x10000;
        }
        if (status->stickY > 0) {
            buttons |= 0x80000;
        } else if (status->stickY < 0) {
            buttons |= 0x40000;
        }
        if (status->substickX > 0) {
            buttons |= 0x200000;
        } else if (status->substickX < 0) {
            buttons |= 0x100000;
        }
        if (status->substickY > 0) {
            buttons |= 0x800000;
        } else if (status->substickY < 0) {
            buttons |= 0x400000;
        }
        if (status->triggerL != 0) {
            buttons |= 0x1000000;
            if (status->triggerL == 150) {
                buttons |= 0x4000000;
            }
        }
        if (status->triggerR != 0) {
            buttons |= 0x2000000;
            if (status->triggerR == 150) {
                buttons |= 0x8000000;
            }
        }
        if (buttons & 3) {
            buttons |= 0x10000000;
        }
        if (buttons & 0xC) {
            buttons |= 0x20000000;
        }
        pad->pressed = buttons & ~pad->held;
        pad->held = buttons;
        pad->stickX = (status->stickX * 0x7FFF) / 72;
        pad->stickY = (status->stickY * 0x7FFF) / 72;
        pad->substickX = (status->substickX * 0x7FFF) / 72;
        pad->substickY = (status->substickY * 0x7FFF) / 72;
        pad->triggerL = (status->triggerL * 0x7FFF) / 150;
        pad->triggerR = (status->triggerR * 0x7FFF) / 150;
        pad->analogA = (status->analogA * 0x7FFF) / 15;
        pad->analogB = (status->analogB * 0x7FFF) / 15;
        pad++;
        status++;
    }

    fn_80144F8C();

    entry = lbl_805B4170;
    end = entry + 20;
    for (; entry < end; entry++) {
        if (entry->flags & 1) {
            memset(entry, 0, sizeof(*entry));
            entry->state = -2;
        }
        if (entry->state > 0) {
            entry->state--;
        }
    }

    lbl_8064D078 = lbl_8064D074;
    if (lbl_8064D050 != 0) {
        lbl_8064D050--;
    }

    if (lbl_8064D054 != 0) {
        if (lbl_805B40F0[0].held == 0) {
            if (lbl_8064D068 < lbl_8064D064) {
                lbl_8064D068++;
            } else {
                lbl_8064D054();
            }
        } else {
            lbl_8064D068 = 0;
        }
    }

    if ((lbl_805B40F0[0].held & 0x1600) == 0x1600) {
        lbl_8064D060++;
        if (lbl_8064D060 >= 30 && lbl_8064D058 != 0) {
            if (lbl_8064CA64 == 0) {
                lbl_8064D058();
            } else {
                lbl_8064D05C = 1;
            }
        }
    } else {
        if (lbl_8064D05C != 0 && lbl_8064D058 != 0 && lbl_8064CA64 == 0) {
            lbl_8064D058();
        }
        lbl_8064D060 = 0;
    }
}
