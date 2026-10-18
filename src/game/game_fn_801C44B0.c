typedef unsigned char u8;
typedef unsigned int u32;

typedef struct PoolEntry {
    void* object;
    void* aux;
    u8 pad08[0xEC];
} PoolEntry;

typedef struct ArenaEntry {
    void* small;
    u8 pad04[0x24];
    void* arena;
    u8 pad2C[0x90];
} ArenaEntry;

extern u8 salNumVoices;
extern u8 salMaxStudioNum;
extern void* dspCmdList;
extern void* dspHrtfHistoryBuffer;
extern void* dspSurround;
extern void* dspITDBuffer;
extern PoolEntry* dspVoice;
extern ArenaEntry lbl_80628CB0[];

extern void salFree(void*);

int salExitDspCtrl(void)
{
    u8 i;

    salFree(dspHrtfHistoryBuffer);
    for (i = 0; i < salNumVoices; i++) {
        salFree(dspVoice[i].object);
        salFree(dspVoice[i].aux);
    }

    for (i = 0; i < salMaxStudioNum; i++) {
        salFree(lbl_80628CB0[i].small);
        salFree(lbl_80628CB0[i].arena);
    }

    salFree(dspITDBuffer);
    salFree(dspVoice);
    salFree(dspSurround);
    salFree(dspCmdList);
    return 1;
}
