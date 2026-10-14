typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;

typedef struct DVDCommandBlock {
    u8 pad[0x0C];
    s32 state;
} DVDCommandBlock;

typedef void (*DVDLowCallback)(u32);

extern DVDCommandBlock *executing_8064DA00;
extern void __DVDStoreErrorCode(u32);
extern void DVDReset(void);
extern void cbForStateError_80213C1C(s32);
extern void fn_802141D0(void);
extern void fn_80214138(u32);
extern s32 fn_80212BE0(DVDLowCallback);

void fn_802140D0(u32 intType)
{
    if (intType == 0x10) {
        executing_8064DA00->state = -1;
        __DVDStoreErrorCode(0x01234568);
        DVDReset();
        cbForStateError_80213C1C(0);
    } else if (intType & 1) {
        fn_802141D0();
    } else {
        fn_80212BE0(fn_80214138);
    }
}
