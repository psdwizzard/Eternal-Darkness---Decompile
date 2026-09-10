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

extern s16 lbl_8064D470;
extern GSTACK lbl_806286B0[];
extern u32 fn_801B2980(void*, void*, SynthMidiSetup*, void*, void*, void*, u16);
extern void fn_801CE2B8(void);
extern void fn_801CE280(void);

u32 fn_801C3F6C(u16 sgid, u16 sid, void* arrfile, void* para, u8 irq_call, void* studio)
{
    int i;
    GROUP_DATA* g;
    void* norm;
    void* drum;
    SynthMidiSetup* midiSetup;
    u32 seqId;
    void* prj;
    GSTACK* gsTab = lbl_806286B0;

    for (i = 0; i < lbl_8064D470; ++i) {
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
                        seqId = fn_801B2980(norm, drum, midiSetup, arrfile, para, studio, sgid);
                    } else {
                        fn_801CE2B8();
                        seqId = fn_801B2980(norm, drum, midiSetup, arrfile, para, studio, sgid);
                        fn_801CE280();
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
