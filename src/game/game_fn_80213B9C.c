typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;

typedef struct DVDCommandBlock DVDCommandBlock;
struct DVDCommandBlock {
    u8 pad[0x0C];
    s32 state;
    u8 pad10[0x18];
    void (*callback)(s32, DVDCommandBlock *);
};

extern DVDCommandBlock *executing_8064DA00;
extern DVDCommandBlock DummyCommandBlock_806419E0;
extern s32 lbl_8064DA34;
extern void fn_80213CC4(void);
extern void stateReady_80214A10(void);
extern void fn_80213D60(void);

void fn_80213B9C(u32 intType)
{
    DVDCommandBlock *finished;

    if (intType == 0x10) {
        executing_8064DA00->state = -1;
        fn_80213CC4();
    } else if (intType & 1) {
        finished = executing_8064DA00;
        lbl_8064DA34 = 0;
        executing_8064DA00 = &DummyCommandBlock_806419E0;
        finished->state = 0;
        if (finished->callback != 0)
            finished->callback(0, finished);
        stateReady_80214A10();
    } else {
        fn_80213D60();
    }
}
