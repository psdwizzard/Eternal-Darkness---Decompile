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

extern CardControl __CARDBlock[];
extern u32 DSPCheckMailToDSP(void);
extern void DSPSendMailToDSP(u32 mail);

void InitCallback(DspTask *task)
{
    CardControl *card;
    u32 packet;
    int channel;

    for (channel = 0; channel < 2; ++channel) {
        card = &__CARDBlock[channel];
        if (&card->task == task) {
            break;
        }
    }

    packet = card->packet;
    DSPSendMailToDSP(0xFF000000);
    while (DSPCheckMailToDSP() != 0) {
    }
    DSPSendMailToDSP(packet);
    while (DSPCheckMailToDSP() != 0) {
    }
}
