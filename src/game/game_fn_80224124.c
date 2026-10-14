typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct {
    u8 pad0[8];
    u32 cpEnable;
    u32 cpStatus;
} GXData;

extern GXData *gx;
extern volatile u16 *__cpReg;

/* GXGetGPStatus: sample the command processor status flags. */
void fn_80224124(u8 *overhi, u8 *underlow, u8 *readIdle,
                 u8 *cmdIdle, u8 *breakpt)
{
    gx->cpStatus = __cpReg[0];
    *overhi = gx->cpStatus & 1;
    *underlow = (gx->cpStatus >> 1) & 1;
    *readIdle = (gx->cpStatus >> 2) & 1;
    *cmdIdle = (gx->cpStatus >> 3) & 1;
    *breakpt = (gx->cpStatus >> 4) & 1;
}
