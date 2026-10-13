/* fn_800F44E8: MetroTRK TRKTargetAccessExtended2 (paired-single register
 * access). Reads/writes FPRs firstRegister..lastRegister as paired singles
 * via self-modifying psq_l / psq_st stubs. */

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef int BOOL;
typedef int DSError;

typedef struct TRKExceptionStatus {
    u32 field0;
    u32 field4;
    u8 field8;
    u8 field9;
    u8 fieldA;
    u8 fieldB;
    u8 fieldC;
    u8 exceptionDetected;
    u8 fieldE;
    u8 fieldF;
} TRKExceptionStatus;

typedef void (*asm_access_type)(void *, void *);

typedef struct AccessFunc {
    u32 instr[10];
} AccessFunc;

extern TRKExceptionStatus gTRKExceptionStatus_8024A864;
extern const AccessFunc lbl_80239C10;
extern const AccessFunc lbl_80239C38;
extern u8 lbl_8032A554[];

extern void fn_800F35AC(void *, unsigned int);
extern DSError fn_800EF604(void *buffer, u64 *data);
extern DSError fn_800EF9FC(void *buffer, u64 data);

#define INSTR_BLR 0x4E800020
#define INSTR_MFSPR(reg, spr) \
    (0x7C0002A6 | ((reg) << 21) | (((spr) & 0x1F) << 16) | (((spr) >> 5) << 11))
#define INSTR_MTSPR(spr, reg) \
    (0x7C0003A6 | ((reg) << 21) | (((spr) & 0x1F) << 16) | (((spr) >> 5) << 11))
#define INSTR_STW(rs, off, ra) (0x90000000 | ((rs) << 21) | ((ra) << 16) | (off))
#define INSTR_LWZ(rd, off, ra) (0x80000000 | ((rd) << 21) | ((ra) << 16) | (off))
#define INSTR_PSQ_ST(fs, off, ra, w, i) \
    (0xF0000000 | ((fs) << 21) | ((ra) << 16) | ((w) << 15) | ((i) << 12) | (off))
#define INSTR_PSQ_L(fd, off, ra, w, i) \
    (0xE0000000 | ((fd) << 21) | ((ra) << 16) | ((w) << 15) | ((i) << 12) | (off))

#define SPR_GQR0 912
#define SPR_HID2 920

static DSError TRKPPCAccessSpecialReg(void *value, u32 *access_func, BOOL read)
{
    asm_access_type asm_access;

    asm_access = (asm_access_type)access_func;
    access_func[9] = INSTR_BLR;
    fn_800F35AC((void *)(u32)access_func, sizeof(u32) * 10);
    asm_access(value, lbl_8032A554);
    return 0;
}

static DSError TRKPPCAccessSPR(void *value, u32 spr, BOOL read)
{
    AccessFunc access_func = lbl_80239C10;

    if (read) {
        access_func.instr[0] = INSTR_MFSPR(4, spr);
        access_func.instr[1] = INSTR_STW(4, 0, 3);
    } else {
        access_func.instr[0] = INSTR_LWZ(4, 0, 3);
        access_func.instr[1] = INSTR_MTSPR(spr, 4);
    }
    return TRKPPCAccessSpecialReg(value, access_func.instr, read);
}

static DSError TRKPPCAccessPairedSingleRegister(void *value, u32 psr, BOOL read)
{
    AccessFunc access_func = lbl_80239C38;

    if (read) {
        access_func.instr[0] = INSTR_PSQ_ST(psr, 0, 3, 0, 0);
    } else {
        access_func.instr[0] = INSTR_PSQ_L(psr, 0, 3, 0, 0);
    }
    return TRKPPCAccessSpecialReg(value, access_func.instr, read);
}

DSError fn_800F44E8(u32 firstRegister, u32 lastRegister, void *b,
                    u32 *registerStorageSize, BOOL read)
{
    TRKExceptionStatus savedException;
    u32 value_buf0[1];
    u32 value_buf[2];
    DSError err;
    u32 current;

    if (lastRegister > 31) {
        return 0x701;
    }

    savedException = gTRKExceptionStatus_8024A864;
    gTRKExceptionStatus_8024A864.exceptionDetected = 0;

    TRKPPCAccessSPR(value_buf0, SPR_HID2, 1);
    value_buf0[0] |= 0xA0000000;
    TRKPPCAccessSPR(value_buf0, SPR_HID2, 0);
    value_buf0[0] = 0;
    TRKPPCAccessSPR(value_buf0, SPR_GQR0, 0);

    *registerStorageSize = 0;
    err = 0;

    for (current = firstRegister; current <= lastRegister && err == 0;
         current++, *registerStorageSize += 8) {
        if (read) {
            err = TRKPPCAccessPairedSingleRegister(value_buf, current, read);
            err = fn_800EF9FC(b, *(u64 *)value_buf);
        } else {
            err = fn_800EF604(b, (u64 *)value_buf);
            err = TRKPPCAccessPairedSingleRegister(value_buf, current, read);
        }
    }

    if (gTRKExceptionStatus_8024A864.exceptionDetected) {
        *registerStorageSize = 0;
        err = 0x702;
    }

    gTRKExceptionStatus_8024A864 = savedException;
    return err;
}
