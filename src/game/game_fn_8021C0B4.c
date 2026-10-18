/* fn_8021C0B4: __DSP_boot_task (SDK dsp_task.c). Waits for the DSP's boot
 * mail, then sends the task's IRAM/DRAM layout and init vector. */

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct DSPTaskInfo {
    volatile u32 state;            /* 0x00 */
    volatile u32 priority;         /* 0x04 */
    volatile u32 flags;            /* 0x08 */
    u16* iram_mmem_addr;           /* 0x0C */
    u32 iram_length;               /* 0x10 */
    u32 iram_addr;                 /* 0x14 */
    u16* dram_mmem_addr;           /* 0x18 */
    u32 dram_length;               /* 0x1C */
    u32 dram_addr;                 /* 0x20 */
    u16 dsp_init_vector;           /* 0x24 */
    u16 dsp_resume_vector;         /* 0x26 */
} DSPTaskInfo;

extern u32 DSPCheckMailToDSP(void);       /* DSPCheckMailToDSP */
extern u32 DSPCheckMailFromDSP(void);       /* DSPCheckMailFromDSP */
extern u32 DSPReadMailFromDSP(void);       /* DSPReadMailFromDSP */
extern void DSPSendMailToDSP(u32 mail);  /* DSPSendMailToDSP */
extern void __DSP_debug_printf(char* fmt, ...); /* __DSP_debug_printf */

/* __DSP_boot_task debug format strings in .data. */
typedef struct DSPBootStrings {
    char booting[0x20];         /* "DSP is booting task: 0x%08X\n" */
    char iram_mmem_addr[0x30];
    char iram_dsp_addr[0x30];
    char iram_length[0x30];
    char dram_length[0x30];
    char start_vector[0x30];
} DSPBootStrings;

extern DSPBootStrings lbl_802FEA20;

void fn_8021C0B4(DSPTaskInfo* task) {
    volatile u32 mail;

    while (!DSPCheckMailFromDSP()) ;
    mail = DSPReadMailFromDSP();

    DSPSendMailToDSP(0x80F3A001);
    while (DSPCheckMailToDSP()) ;
    DSPSendMailToDSP((u32)(task->iram_mmem_addr));
    while (DSPCheckMailToDSP()) ;
    DSPSendMailToDSP(0x80F3C002);
    while (DSPCheckMailToDSP()) ;
    DSPSendMailToDSP((u32)(task->iram_addr & 0xFFFF));
    while (DSPCheckMailToDSP()) ;
    DSPSendMailToDSP(0x80F3A002);
    while (DSPCheckMailToDSP()) ;
    DSPSendMailToDSP(task->iram_length);
    while (DSPCheckMailToDSP()) ;
    DSPSendMailToDSP(0x80F3B002);
    while (DSPCheckMailToDSP()) ;
    DSPSendMailToDSP(0);
    while (DSPCheckMailToDSP()) ;
    DSPSendMailToDSP(0x80F3D001);
    while (DSPCheckMailToDSP()) ;
    DSPSendMailToDSP((u32)(0xFFFF & task->dsp_init_vector));
    while (DSPCheckMailToDSP()) ;

    __DSP_debug_printf("DSP is booting task: 0x%08X\n", task);
    __DSP_debug_printf("__DSP_boot_task()  : IRAM MMEM ADDR: 0x%08X\n", task->iram_mmem_addr);
    __DSP_debug_printf("__DSP_boot_task()  : IRAM DSP ADDR : 0x%08X\n", task->iram_addr);
    __DSP_debug_printf("__DSP_boot_task()  : IRAM LENGTH   : 0x%08X\n", task->iram_length);
    __DSP_debug_printf("__DSP_boot_task()  : DRAM MMEM ADDR: 0x%08X\n", task->dram_length);
    __DSP_debug_printf("__DSP_boot_task()  : Start Vector  : 0x%08X\n", task->dsp_init_vector);
}
