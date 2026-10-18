typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

typedef struct Entry {
    u8 state;
    u8 pad01[0x07];
    u32 resource0;
    u8 pad0C[0x20];
    u32 resource3;
    u8 pad30[0x0C];
    u32 flags;
    u8 pad40[0x70];
} Entry;
typedef struct Bank { Entry *base; u32 unk[3]; } Bank;

typedef struct Request {
    u32 unk0;
    s32 type;
    s32 slot;
    u32 unkC;
} Request;

extern u8 magic;
extern s32 PERFCurrFrame;
extern Request *PERFEvents;
extern Bank *PERFFrames;
extern const char lbl_802FF7C0[];
extern s32 OSDisableInterrupts(void);
extern s32 OSRestoreInterrupts(s32);
extern void OSReport(const char *, ...);
extern u32 PPCMfpmc1(void);
extern u32 PPCMfpmc3(void);
extern u32 PPCMfpmc4(void);
extern void GXSetDrawSync(u32);

#define ENTRIES (PERFFrames[PERFCurrFrame].base)

void PERFEventEnd(u8 id)
{
    s32 enabled = OSDisableInterrupts();
    s32 slot = PERFEvents[id].slot;

    if (slot < 0) {
        OSReport(lbl_802FF7C0);
        OSRestoreInterrupts(enabled);
        return;
    }

    switch (PERFEvents[id].type) {
    case 2:
        GXSetDrawSync((u16)slot + 0xF000 + ((magic << 8) & 0xFF00));
        break;
    case 1:
        GXSetDrawSync((u16)slot + 0xF000 + ((magic << 8) & 0xFF00));
    case 0:
        ENTRIES[slot].resource0 = PPCMfpmc4();
        ENTRIES[slot].resource3 = PPCMfpmc3();
        ENTRIES[slot].flags = PPCMfpmc1();
        break;
    }
    PERFEvents[id].slot = -1;
    OSRestoreInterrupts(enabled);
}
