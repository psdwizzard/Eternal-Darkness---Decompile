typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 unk0;
    u32 unk4;
    u32 length;
    u32 position;
    u8 data[1];
} TRKBuffer;

extern void *fn_80003130(void *, const void *, u32);

int fn_800EF86C(register TRKBuffer *buffer, register u8 *out)
{
    register int error;
    register u32 amount;

    error = 0;
    amount = 1;
    /* ASM: lwz/mr/lwz/subf/cmplw/ble/li/mr preserve the retail argument
     * evaluation and register comparison; C moves out early and folds 1. */
    asm {
        lwz r5, 0xc(r3)
        mr r3, out
        lwz r0, 0x8(buffer)
        subf r0, r5, r0
        cmplw amount, r0
        ble read_ready
        li error, 0x302
        mr amount, r0
    }
read_ready:
    /* ASM: addi/mr/add/bl consumes the position retained in r5; expressing
     * the call in C makes CodeWarrior reuse r4 and changes argument setup. */
    asm {
        addi r4, r5, 0x10
        mr r5, amount
        add r4, buffer, r4
        bl fn_80003130
    }
    buffer->position += amount;
    return error;
}
