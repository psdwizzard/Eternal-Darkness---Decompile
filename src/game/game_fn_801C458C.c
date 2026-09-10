typedef unsigned char u8;
typedef unsigned int u32;

typedef struct DSPstudioinfo {
    void* spb;
    u32 l;
    u32 r;
    u32 s;
    u32 lA;
    u32 rA;
    u32 sA;
    u32 lB;
    u32 rB;
    u32 sB;
    void* main[2];
    void* auxA[3];
    void* auxB[3];
    void* voiceRoot;
    void* alienVoiceRoot;
    u8 state;
    u8 isMaster;
    u8 numInputs;
    u8 pad53;
    u32 type;
    u8 pad58[0x54];
    void* auxAHandler;
    void* auxBHandler;
    u8 padB4[8];
} DSPstudioinfo;

extern DSPstudioinfo lbl_80628CB0[];
#define dspStudio lbl_80628CB0
extern void* memset(void*, int, u32);
extern void DCFlushRangeNoSync(void*, u32);

void fn_801C458C(u8 studio, u32 isMaster, u32 type)
{
    DSPstudioinfo* base = dspStudio;

    memset(base[studio].main[0], 0, 0x3c00);
    DCFlushRangeNoSync(base[studio].main[0], 0x3c00);
    memset(base[studio].spb, 0, 0x36);
    base[studio].l = base[studio].r = base[studio].s = 0;
    base[studio].lA = base[studio].rA = base[studio].sA = 0;
    base[studio].lB = base[studio].rB = base[studio].sB = 0;
    DCFlushRangeNoSync(base[studio].spb, 0x36);
    memset(base[studio].auxA[0], 0, 0x780);
    DCFlushRangeNoSync(base[studio].auxA[0], 0x780);
    memset(base[studio].auxB[0], 0, 0x780);
    DCFlushRangeNoSync(base[studio].auxB[0], 0x780);
    base[studio].voiceRoot = 0;
    base[studio].alienVoiceRoot = 0;
    base[studio].state = 1;
    base[studio].isMaster = isMaster;
    base[studio].numInputs = 0;
    base[studio].type = type;
    base[studio].auxAHandler = base[studio].auxBHandler = 0;
}
