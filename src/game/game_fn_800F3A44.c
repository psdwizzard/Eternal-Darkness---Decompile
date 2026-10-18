/* TRKPPCAccessFPRegister: MetroTRK TRKPPCAccessFPRegister. Reads/writes an FPR (or the
 * FPSCR) through a self-modifying ten-instruction stub copied from a
 * nop-filled template. */

typedef unsigned int u32;
typedef unsigned long long u64;
typedef int BOOL;
typedef int DSError;

typedef void (*asm_access_type)(void *, void *);

typedef struct AccessFunc {
    u32 instr[10];
} AccessFunc;

extern const volatile unsigned int lbl_80239C10[10];
extern const volatile unsigned int lbl_80239C60[10];
extern unsigned char TRKvalue128_temp[];

extern void TRK_flush_cache(void *, unsigned int);

#define INSTR_BLR 0x4E800020
#define INSTR_LFD(fd, off, ra) (0xC8000000 | ((fd) << 21) | ((ra) << 16) | (off))
#define INSTR_STFD(fs, off, ra) (0xD8000000 | ((fs) << 21) | ((ra) << 16) | (off))

/* FPSCR access stubs: move through r4 and the word at 0(r3). */
#define INSTR_READ_FPSCR0  0x7C9EFAA6
#define INSTR_READ_FPSCR1  0x90830000 /* stw r4, 0(r3) */
#define INSTR_WRITE_FPSCR0 0x80830000 /* lwz r4, 0(r3) */
#define INSTR_WRITE_FPSCR1 0x7C9EFBA6

static DSError TRKPPCAccessSpecialReg(void *value, u32 *access_func, BOOL read)
{
    asm_access_type asm_access;

    asm_access = (asm_access_type)access_func;
    access_func[9] = INSTR_BLR;
    TRK_flush_cache((void *)(u32)access_func, sizeof(u32) * 10);
    asm_access(value, TRKvalue128_temp);
    return 0;
}

static DSError TRKPPCAccessFPSCR(void *value, BOOL read)
{
    AccessFunc access_func = *(const AccessFunc *)lbl_80239C10;

    if (read) {
        access_func.instr[0] = INSTR_READ_FPSCR0;
        access_func.instr[1] = INSTR_READ_FPSCR1;
    } else {
        access_func.instr[0] = INSTR_WRITE_FPSCR0;
        access_func.instr[1] = INSTR_WRITE_FPSCR1;
    }
    return TRKPPCAccessSpecialReg(value, access_func.instr, read);
}

DSError TRKPPCAccessFPRegister(void *value, u32 fpr, BOOL read)
{
    DSError error = 0;
    AccessFunc access_func = *(const AccessFunc *)lbl_80239C60;

    if (fpr < 0x20) {
        if (read) {
            access_func.instr[0] = INSTR_STFD(fpr, 0, 3);
        } else {
            access_func.instr[0] = INSTR_LFD(fpr, 0, 3);
        }
        error = TRKPPCAccessSpecialReg(value, access_func.instr, read);
    } else if (fpr == 0x20) {
        *(u64 *)value &= 0xFFFFFFFF;
    } else if (fpr == 0x21) {
        if (!read) {
            *(u32 *)value = *((u32 *)value + 1);
        }
        error = TRKPPCAccessFPSCR(value, read);
        if (read) {
            *(u64 *)value = *(u32 *)value & 0xFFFFFFFFULL;
        }
    }
    return error;
}
