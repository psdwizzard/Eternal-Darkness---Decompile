typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

#pragma pack(4)
typedef struct Voice {
    u8 pad_000[0x114];
    u64 flags_114;
    u8 pad_11C[0x2E8];
} Voice;
#pragma pack()

typedef struct AudioState {
    u8 pad_000[0x210];
    u8 voice_count;
} AudioState;

extern u32 synthFlags;
extern Voice *synthVoice;
extern AudioState synthInfo;
extern void hwDisableHRTF(void);
extern void streamOutputModeChanged(void);

void sndOutputMode(int arg0)
{
    u32 old_flags = synthFlags;
    switch (arg0) {
    case 0:
        synthFlags |= 1;
        synthFlags &= ~2;
        hwDisableHRTF();
        break;
    case 1:
        synthFlags &= ~1;
        synthFlags &= ~2;
        hwDisableHRTF();
        break;
    case 2:
        synthFlags &= ~1;
        synthFlags |= 2;
        hwDisableHRTF();
        break;
    }
    if (old_flags != synthFlags) {
        int offset;
        u32 i;
        i = 0;
        offset = 0;
        while (i < synthInfo.voice_count) {
            ((Voice *)((u8 *)synthVoice + offset))->flags_114 |= 0x0000200000000000ULL;
            offset += 0x404;
            i++;
        }
        streamOutputModeChanged();
    }
}
