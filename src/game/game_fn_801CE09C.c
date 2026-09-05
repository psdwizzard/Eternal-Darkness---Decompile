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

extern AudioState lbl_80631340;
extern unsigned char lbl_80253BC0[];
extern u16 lbl_8064D4F8;
extern u32 lbl_8064D528;
extern void fn_801CDED8(void);
extern void fn_801CDEE8(void);
extern void fn_8021B8E0(void);
extern void fn_8021BA30(AudioState*);
extern void fn_801CE280(void);
extern void fn_801CE2B8(void);

u32 fn_801CE09C(u32 unused)
{
    lbl_80631340.data = lbl_80253BC0;
    lbl_80631340.value10 = lbl_8064D4F8;
    lbl_80631340.value14 = 0;
    lbl_80631340.buffer = lbl_80631340.storage;
    lbl_80631340.buffer_size = 0x2000;
    lbl_80631340.value20 = 0;
    lbl_80631340.value24 = 0x10;
    lbl_80631340.value26 = 0x30;
    lbl_80631340.callback28 = fn_801CDED8;
    lbl_80631340.callback2C = fn_801CDEE8;
    lbl_80631340.value30 = 0;
    lbl_80631340.value34 = 0;
    lbl_80631340.unk04 = 0;
    fn_8021B8E0();
    fn_8021BA30(&lbl_80631340);
    lbl_8064D528 = 0;
    fn_801CE280();
    while (lbl_8064D528 == 0) {
    }
    fn_801CE2B8();
    return 1;
}
