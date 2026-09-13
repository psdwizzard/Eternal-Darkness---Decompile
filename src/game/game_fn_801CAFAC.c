typedef unsigned char u8;
typedef unsigned short u16;

typedef struct InpMidiCtrls {
    u8 pad00[0xC0];
    u8 byKey[8][16][134];
    u8 ctrl[16][134];
} InpMidiCtrls;

extern InpMidiCtrls lbl_8062A230;

#define gInpMidiCtrlByKey s->byKey
#define gInpMidiCtrl s->ctrl

u16 fn_801CAFAC(u8 controller, u8 slot, u8 key)
{
    short mask = 0x1f;
    InpMidiCtrls* s = &lbl_8062A230;

    if (slot != 0xff) {
        if (key != 0xff) {
            if (controller < 0x40) {
                return gInpMidiCtrlByKey[key][slot][controller & 0x1f] << 7 |
                       gInpMidiCtrlByKey[key][slot][(controller & 0x1f) + 0x20];
            }
            if (controller < 0x46) {
                return (gInpMidiCtrlByKey[key][slot][controller] < 0x40) ? 0 : 0x3fff;
            }
            if (controller >= 0x60 && controller < 0x66) {
                return 0;
            }
            if (controller == 0x80 || controller == 0x81) {
                return (gInpMidiCtrlByKey[key][slot][controller & 0xfe] << 7) |
                       gInpMidiCtrlByKey[key][slot][(controller & 0xfe) + 1];
            }
            if (controller == 0x84 || controller == 0x85) {
                return (gInpMidiCtrlByKey[key][slot][controller & 0xfe] << 7) |
                       gInpMidiCtrlByKey[key][slot][(controller & 0xfe) + 1];
            }
            return gInpMidiCtrlByKey[key][slot][controller] << 7;
        }

        if (controller < 0x40) {
            return (gInpMidiCtrl[slot][controller & mask] << 7) |
                   gInpMidiCtrl[slot][(controller & mask) + 0x20];
        }
        if (controller < 0x46) {
            return (gInpMidiCtrl[slot][controller] < 0x40) ? 0 : 0x3fff;
        }
        if (controller >= 0x60 && controller < 0x66) {
            return 0;
        }
        if (controller == 0x80 || controller == 0x81) {
            return (gInpMidiCtrl[slot][controller & 0xfe] << 7) |
                   gInpMidiCtrl[slot][(controller & 0xfe) + 1];
        }
        if (controller == 0x84 || controller == 0x85) {
            return (gInpMidiCtrl[slot][controller & 0xfe] << 7) |
                   gInpMidiCtrl[slot][(controller & 0xfe) + 1];
        }
        return gInpMidiCtrl[slot][controller] << 7;
    }
    return 0;
}
