typedef unsigned char u8;
typedef unsigned int u32;

typedef struct DspTask {
    u8 data[0x50];
} DspTask;

typedef struct CardControl {
    u8 pad00[0x30];
    DspTask task;
    u32 packet;
    u8 pad84[0x8C];
} CardControl;

extern CardControl lbl_80641C60[];
extern u32 fn_8021B894(void);
extern void fn_8021B8CC(u32 mail);

void fn_8021E50C(DspTask *task)
{
    CardControl *card;
    u32 packet;
    int channel;

    for (channel = 0; channel < 2; ++channel) {
        card = &lbl_80641C60[channel];
        if (&card->task == task) {
            break;
        }
    }

    packet = card->packet;
    fn_8021B8CC(0xFF000000);
    while (fn_8021B894() != 0) {
    }
    fn_8021B8CC(packet);
    while (fn_8021B894() != 0) {
    }
}
