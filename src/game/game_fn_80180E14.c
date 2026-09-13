typedef unsigned char u8;
typedef unsigned short u16;

extern void* lbl_8064D238;
extern char lbl_80606334[];

typedef struct ConfigBlock {
    u8 bytes[0x14];
} ConfigBlock;

extern void* fn_8018038C(void*, void*);
extern void fn_80180ED8(void*, void*, void*, ConfigBlock*);
extern void fn_801810A0(void*, void*);
extern int fn_801813E4(u8*);
extern void fn_8018D998(void);
extern void fn_8018DC24(void);

void* fn_80180E14(void* arg0, void* arg1, ConfigBlock* config)
{
    void* object = fn_8018038C(lbl_8064D238, lbl_80606334);
    ConfigBlock* block = config;

    if (object != 0) {
        fn_80180ED8(object, arg0, arg1, block++);
        fn_801810A0(object, block);
        *(int (**)(u8*))((u8*)object + 0x14C) = fn_801813E4;
        if (block->bytes[4] & 0x40) {
            *(void (**)(void))((u8*)object + 0x148) = fn_8018D998;
        } else {
            *(void (**)(void))((u8*)object + 0x148) = fn_8018DC24;
        }
        *(u16*)((u8*)object + 0x22) = 4;
    }
    return object;
}
