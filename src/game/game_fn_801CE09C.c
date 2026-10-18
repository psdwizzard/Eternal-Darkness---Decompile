typedef unsigned short u16;
typedef unsigned int u32;

typedef struct AudioState {
    u32 unk00;
    u32 unk04;
    u32 unk08;
    void* data;
    u32 value10;
    u32 value14;
    void* buffer;
    u32 buffer_size;
    u32 value20;
    u16 value24;
    u16 value26;
    void* callback28;
    void* callback2C;
    u32 value30;
    u32 value34;
    unsigned char padding38[0x28];
    unsigned char storage[1];
} AudioState;

static AudioState sDspTask;
extern unsigned char dspSlave[];
extern u16 dspSlaveLength;
extern volatile u32 salDspInitIsDone;
extern void dspInitCallback(void);
extern void dspResumeCallback(void);
extern void DSPInit(void);
extern void DSPAddTask(AudioState*);
extern void hwEnableIrq(void);
extern void hwDisableIrq(void);

u32 salInitDsp(u32 unused)
{
    sDspTask.data = dspSlave;
    sDspTask.value10 = dspSlaveLength;
    sDspTask.value14 = 0;
    sDspTask.buffer = sDspTask.storage;
    sDspTask.buffer_size = 0x2000;
    sDspTask.value20 = 0;
    sDspTask.value24 = 0x10;
    sDspTask.value26 = 0x30;
    sDspTask.callback28 = dspInitCallback;
    sDspTask.callback2C = dspResumeCallback;
    sDspTask.value30 = 0;
    sDspTask.value34 = 0;
    sDspTask.unk04 = 0;
    DSPInit();
    DSPAddTask(&sDspTask);
    salDspInitIsDone = 0;
    hwEnableIrq();
    while (salDspInitIsDone == 0) {
    }
    hwDisableIrq();
    return 1;
}
