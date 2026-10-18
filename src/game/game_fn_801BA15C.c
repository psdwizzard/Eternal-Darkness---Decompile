typedef unsigned char u8;
typedef unsigned int u32;

typedef struct StreamSlot {
    u32 id;
    u32 flags;
    u8 state;
    u8 pad09[0x3F];
    u32 voice;
    u8 pad4C[9];
    u8 volume;
    u8 left;
    u8 right;
    u8 aux_left;
    u8 aux_right;
    u8 saved_left;
    u8 saved_right;
    u8 pad5C[8];
} StreamSlot;

extern StreamSlot lbl_8061AE48[];
extern u8 synthInfo[];
extern u32 synthFlags;
extern void hwDisableIrq(void);
extern void hwEnableIrq(void);
extern void hwSetVolume(u32, u32, u32, u32, float, float, float);

void streamOutputModeChanged(void)
{
    u32 i;
    float volumeScale;

    hwDisableIrq();
    volumeScale = 1 / 127.0f;
    for (i = 0; i < synthInfo[0x210]; i++) {
        if (lbl_8061AE48[i].state != 0) {
            lbl_8061AE48[i].left = lbl_8061AE48[i].saved_left;
            lbl_8061AE48[i].right = lbl_8061AE48[i].saved_right;
            if ((synthFlags & 1) != 0) {
                lbl_8061AE48[i].left = 0x40;
                lbl_8061AE48[i].right = 0;
            } else if ((synthFlags & 2) == 0) {
                lbl_8061AE48[i].right = 0;
            }
            if (lbl_8061AE48[i].state != 3) {
                hwSetVolume(lbl_8061AE48[i].voice, 0, lbl_8061AE48[i].left << 0x10, lbl_8061AE48[i].right << 0x10,
                            volumeScale * lbl_8061AE48[i].volume, volumeScale * lbl_8061AE48[i].aux_left,
                            volumeScale * lbl_8061AE48[i].aux_right);
            }
        }
    }
    hwEnableIrq();
}
