typedef unsigned char u8;
typedef unsigned int u32;

typedef struct DSPvoice DSPvoice;
struct DSPvoice {
    unsigned char pad00[0xC];
    DSPvoice* next;
    DSPvoice* prev;
    unsigned char pad14[0x10];
    u32 changed;
    unsigned char pad28[0xC4];
    u8 state;
    u8 postBreak;
    u8 startupBreak;
    u8 studio;
};

typedef struct DSPstudioinfo {
    unsigned char pad00[0x48];
    DSPvoice* voiceRoot;
    unsigned char pad4C[0x70];
} DSPstudioinfo;

extern DSPstudioinfo lbl_80628CB0[];
void fn_801C7624(DSPvoice* voice);

void fn_801C7580(DSPvoice* voice, u8 studio)
{
    if (voice->state != 0) {
        fn_801C7624(voice);
        voice->changed |= 0x20;
    }
    voice->postBreak = 0;
    if ((voice->next = lbl_80628CB0[studio].voiceRoot) != 0) {
        voice->next->prev = voice;
    }
    voice->prev = 0;
    lbl_80628CB0[studio].voiceRoot = voice;
    voice->startupBreak = 0;
    voice->state = 1;
    voice->studio = studio;
}
