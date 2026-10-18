typedef unsigned char u8;
typedef unsigned int u32;

extern u8 salAuxFrame;
extern u8 salFrame;
extern u32 salMessageCallback;

extern void snd_handle_irq(void);
extern void hwInitIrq(void);
extern u32 salInitAi(void (*callback)(void), u32 flags, void* config);
extern u32 salInitDspCtrl(u8 count, u8 arena_count, int enable);
extern u32 salInitDsp(u32 flags);
extern void hwEnableIrq(void);
extern void salStartAi(void);

int hwInit(void* config, u32 count, u32 arena_count, u32 flags)
{
    hwInitIrq();
    salFrame = 0;
    salAuxFrame = 0;
    salMessageCallback = 0;
    if (salInitAi(snd_handle_irq, flags, config) != 0 &&
        salInitDspCtrl(count, arena_count, (flags & 1) != 0) != 0 &&
        salInitDsp(flags) != 0) {
        hwEnableIrq();
        salStartAi();
        return 0;
    }
    return -1;
}
