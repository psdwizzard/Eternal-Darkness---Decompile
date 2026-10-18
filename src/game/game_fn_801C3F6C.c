typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct GROUP_DATA {
    u32 nextOff;
    u16 id;
    u16 type;
    u32 macroOff;
    u32 sampleOff;
    u32 curveOff;
    u32 keymapOff;
    u32 layerOff;
    u32 normpageOff;
    u32 drumpageOff;
    u32 midiSetupOff;
} GROUP_DATA;

typedef struct GSTACK {
    GROUP_DATA* gAddr;
    void* sdirAddr;
    void* prjAddr;
} GSTACK;

typedef struct SynthMidiSetup {
    u16 songId;
    u8 payload[0x52];
} SynthMidiSetup;

extern s16 sp;
extern GSTACK gs[];
extern u32 seqStartPlay(void*, void*, SynthMidiSetup*, void*, void*, void*, u16);
extern void hwDisableIrq(void);
extern void hwEnableIrq(void);

u32 seqPlaySong(u16 sgid, u16 sid, void* arrfile, void* para, u8 irq_call, void* studio)
{
    int i;
    GROUP_DATA* g;
    void* norm;
    void* drum;
    SynthMidiSetup* midiSetup;
    u32 seqId;
    void* prj;
    GSTACK* gsTab = gs;

    for (i = 0; i < sp; ++i) {
        if (gsTab[i].gAddr->id != sgid) {
            continue;
        }

        if (gsTab[i].gAddr->type == 0) {
            g = gsTab[i].gAddr;
            prj = gsTab[i].prjAddr;
            norm = (u8*)prj + g->normpageOff;
            drum = (u8*)prj + g->drumpageOff;
            midiSetup = (SynthMidiSetup*)((u8*)prj + g->midiSetupOff);
            while (midiSetup->songId != 0xFFFF) {
                if (midiSetup->songId == sid) {
                    if (irq_call != 0) {
                        seqId = seqStartPlay(norm, drum, midiSetup, arrfile, para, studio, sgid);
                    } else {
                        hwDisableIrq();
                        seqId = seqStartPlay(norm, drum, midiSetup, arrfile, para, studio, sgid);
                        hwEnableIrq();
                    }
                    return seqId;
                }

                ++midiSetup;
            }

            return 0xffffffff;
        } else {
            return 0xffffffff;
        }
    }

    return 0xffffffff;
}
