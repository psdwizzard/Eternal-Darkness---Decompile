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

extern u32 fn_8021B894(void);       /* DSPCheckMailToDSP */
extern u32 fn_8021B8A4(void);       /* DSPCheckMailFromDSP */
extern u32 fn_8021B8B4(void);       /* DSPReadMailFromDSP */
extern void fn_8021B8CC(u32 mail);  /* DSPSendMailToDSP */
extern void fn_8021BAA0(char* fmt, ...); /* __DSP_debug_printf */

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

    while (!fn_8021B8A4()) ;
    mail = fn_8021B8B4();

    fn_8021B8CC(0x80F3A001);
    while (fn_8021B894()) ;
    fn_8021B8CC((u32)(task->iram_mmem_addr));
    while (fn_8021B894()) ;
    fn_8021B8CC(0x80F3C002);
    while (fn_8021B894()) ;
    fn_8021B8CC((u32)(task->iram_addr & 0xFFFF));
    while (fn_8021B894()) ;
    fn_8021B8CC(0x80F3A002);
    while (fn_8021B894()) ;
    fn_8021B8CC(task->iram_length);
    while (fn_8021B894()) ;
    fn_8021B8CC(0x80F3B002);
    while (fn_8021B894()) ;
    fn_8021B8CC(0);
    while (fn_8021B894()) ;
    fn_8021B8CC(0x80F3D001);
    while (fn_8021B894()) ;
    fn_8021B8CC((u32)(0xFFFF & task->dsp_init_vector));
    while (fn_8021B894()) ;

    fn_8021BAA0("DSP is booting task: 0x%08X\n", task);
    fn_8021BAA0("__DSP_boot_task()  : IRAM MMEM ADDR: 0x%08X\n", task->iram_mmem_addr);
    fn_8021BAA0("__DSP_boot_task()  : IRAM DSP ADDR : 0x%08X\n", task->iram_addr);
    fn_8021BAA0("__DSP_boot_task()  : IRAM LENGTH   : 0x%08X\n", task->iram_length);
    fn_8021BAA0("__DSP_boot_task()  : DRAM MMEM ADDR: 0x%08X\n", task->dram_length);
    fn_8021BAA0("__DSP_boot_task()  : Start Vector  : 0x%08X\n", task->dsp_init_vector);
}
