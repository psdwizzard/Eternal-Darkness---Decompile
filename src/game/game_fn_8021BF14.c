/* __DSP_exec_task: __DSP_exec_task (SDK dsp_task.c). Sends the outgoing task's
 * DRAM save info and the incoming task's IRAM/DRAM boot info to the DSP. */

typedef unsigned char u8;
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

extern void DSPSendMailToDSP(u32 mail);  /* DSPSendMailToDSP */
extern u32 DSPCheckMailToDSP(void);       /* DSPCheckMailToDSP */

#define DSP_TASK_STATE_INIT 0

void __DSP_exec_task(DSPTaskInfo* curr, DSPTaskInfo* next) {
    if (curr) {
        DSPSendMailToDSP((u32)(curr->dram_mmem_addr));
        while (DSPCheckMailToDSP()) ;
        DSPSendMailToDSP((u32)(curr->dram_length));
        while (DSPCheckMailToDSP()) ;
        DSPSendMailToDSP((u32)(curr->dram_addr));
        while (DSPCheckMailToDSP()) ;
    } else {
        DSPSendMailToDSP((u32)(0));
        while (DSPCheckMailToDSP()) ;
        DSPSendMailToDSP((u32)(0));
        while (DSPCheckMailToDSP()) ;
        DSPSendMailToDSP((u32)(0));
        while (DSPCheckMailToDSP()) ;
    }

    DSPSendMailToDSP((u32)(next->iram_mmem_addr));
    while (DSPCheckMailToDSP()) ;
    DSPSendMailToDSP((u32)(next->iram_length));
    while (DSPCheckMailToDSP()) ;
    DSPSendMailToDSP((u32)(next->iram_addr));
    while (DSPCheckMailToDSP()) ;

    if (DSP_TASK_STATE_INIT == next->state) {
        DSPSendMailToDSP((u32)(next->dsp_init_vector));
        while (DSPCheckMailToDSP()) ;
        DSPSendMailToDSP((u32)(0));
        while (DSPCheckMailToDSP()) ;
        DSPSendMailToDSP((u32)(0));
        while (DSPCheckMailToDSP()) ;
        DSPSendMailToDSP((u32)(0));
        while (DSPCheckMailToDSP()) ;
    } else {
        DSPSendMailToDSP((u32)(next->dsp_resume_vector));
        while (DSPCheckMailToDSP()) ;
        DSPSendMailToDSP((u32)(next->dram_mmem_addr));
        while (DSPCheckMailToDSP()) ;
        DSPSendMailToDSP((u32)(next->dram_length));
        while (DSPCheckMailToDSP()) ;
        DSPSendMailToDSP((u32)(next->dram_addr));
        while (DSPCheckMailToDSP()) ;
    }
}
