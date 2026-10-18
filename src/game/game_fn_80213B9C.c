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
extern s32 NumInternalRetry;
extern void stateTimeout(void);
extern void stateReady_80214A10(void);
extern void stateGettingError(void);

void cbForStateReadingFST(u32 intType)
{
    DVDCommandBlock *finished;

    if (intType == 0x10) {
        executing_8064DA00->state = -1;
        stateTimeout();
    } else if (intType & 1) {
        finished = executing_8064DA00;
        NumInternalRetry = 0;
        executing_8064DA00 = &DummyCommandBlock_806419E0;
        finished->state = 0;
        if (finished->callback != 0)
            finished->callback(0, finished);
        stateReady_80214A10();
    } else {
        stateGettingError();
    }
}
