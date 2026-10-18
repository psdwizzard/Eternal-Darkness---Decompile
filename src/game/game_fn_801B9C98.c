typedef unsigned char u8;
typedef unsigned int u32;

typedef void (*StreamCallback)(u32, u32, u32, u32, u32);

typedef struct StreamSlot {
    u8 pad00[8];
    u8 state;
    u8 pad09[3];
    StreamCallback callback;
    u8 pad10[0x38];
    u32 voice;
    u32 callback_arg;
    u8 pad50[0x14];
} StreamSlot;

extern StreamSlot lbl_8061AE48[];
extern void voiceUnblock(u32);

void streamKill(int index)
{
    StreamSlot* slot = &lbl_8061AE48[index];

    switch (slot->state) {
    case 1:
    case 2:
        if (slot->state == 2) {
            voiceUnblock(slot->voice);
        }
        slot->state = 3;
        slot->callback(0, 0, 0, 0, slot->callback_arg);
        break;
    }
}
