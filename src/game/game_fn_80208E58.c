typedef signed int s32;
typedef unsigned int u32;

extern u32 Type_802FCA34[4];
extern volatile u32 __SIStatus : 0xCC006438;

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32 enabled);

u32 SIGetStatus(s32 chan)
{
    register u32 status;
    u32 enabled = OSDisableInterrupts();
    status = __SIStatus;
    status >>= (3 - chan) * 8;

    if ((status & 8) && !(Type_802FCA34[chan] & 0x80)) {
        Type_802FCA34[chan] = 8;
    }

    OSRestoreInterrupts(enabled);
    return status;
}
