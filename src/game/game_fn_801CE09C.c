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
extern unsigned char lbl_80253BC0[];
extern u16 lbl_8064C2F8;
extern volatile u32 lbl_8064D528;
extern void fn_801CDED8(void);
extern void fn_801CDEE8(void);
extern void fn_8021B8E0(void);
extern void fn_8021BA30(AudioState*);
extern void fn_801CE280(void);
extern void fn_801CE2B8(void);

u32 fn_801CE09C(u32 unused)
{
    sDspTask.data = lbl_80253BC0;
    sDspTask.value10 = lbl_8064C2F8;
    sDspTask.value14 = 0;
    sDspTask.buffer = sDspTask.storage;
    sDspTask.buffer_size = 0x2000;
    sDspTask.value20 = 0;
    sDspTask.value24 = 0x10;
    sDspTask.value26 = 0x30;
    sDspTask.callback28 = fn_801CDED8;
    sDspTask.callback2C = fn_801CDEE8;
    sDspTask.value30 = 0;
    sDspTask.value34 = 0;
    sDspTask.unk04 = 0;
    fn_8021B8E0();
    fn_8021BA30(&sDspTask);
    lbl_8064D528 = 0;
    fn_801CE280();
    while (lbl_8064D528 == 0) {
    }
    fn_801CE2B8();
    return 1;
}
