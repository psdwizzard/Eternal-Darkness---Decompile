typedef signed short s16;
typedef signed int s32;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct OSContext {
    char data[0x2C8];
} OSContext;

typedef struct DSPTask DSPTask;
struct DSPTask {
    u32 state;
    u32 priority;
    u32 flags;
    u16 *iram;
    u32 iramLength;
    u32 iramAddress;
    u16 *dram;
    u32 dramLength;
    u32 dramAddress;
    u16 initVector;
    u16 resumeVector;
    void (*initCallback)(DSPTask *);
    void (*resumeCallback)(DSPTask *);
    void (*doneCallback)(DSPTask *);
    void (*requestCallback)(DSPTask *);
    DSPTask *next;
    DSPTask *prev;
};

extern void OSClearContext(OSContext *context);
extern void OSSetCurrentContext(OSContext *context);
extern u32 DSPCheckMailToDSP(void);
extern u32 DSPCheckMailFromDSP(void);
extern u32 DSPReadMailFromDSP(void);
extern void DSPSendMailToDSP(u32 mail);
extern void __DSP_exec_task(DSPTask *outgoing, DSPTask *incoming);
extern void __DSP_remove_task(DSPTask *task);

extern s32 __DSP_rude_task_pending;
extern DSPTask *__DSP_rude_task;
extern DSPTask *__DSP_last_task;
extern DSPTask *__DSP_first_task;
extern DSPTask *__DSP_curr_task;

volatile u16 DSPRegisters[] : 0xCC005000;

void __DSPHandler(s16 interrupt, OSContext *context)
{
    /* Preserve the interrupt handler's eight-byte stack scratch slot. */
    double contextPadding;
    OSContext exceptionContext;
    s32 mail;
    u16 status;

    status = DSPRegisters[5];
    DSPRegisters[5] = (status & ~0x28) | 0x80;
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);

    while (DSPCheckMailFromDSP() == 0) {
    }
    mail = DSPReadMailFromDSP();
    if ((__DSP_curr_task->flags & 2) && (mail == 0xDCD10002)) {
        mail = 0xDCD10003;
    }

    switch (mail) {
    case (s32)0xDCD10000:
        __DSP_curr_task->state = 1;
        if (__DSP_curr_task->initCallback != 0) {
            __DSP_curr_task->initCallback(__DSP_curr_task);
        }
        break;
    case (s32)0xDCD10001:
        __DSP_curr_task->state = 1;
        if (__DSP_curr_task->resumeCallback != 0) {
            __DSP_curr_task->resumeCallback(__DSP_curr_task);
        }
        break;
    case (s32)0xDCD10002:
        if (__DSP_rude_task_pending != 0) {
            if (__DSP_curr_task == __DSP_rude_task) {
                DSPSendMailToDSP(0xCDD10003);
                while (DSPCheckMailToDSP() != 0) {
                }
                __DSP_rude_task = 0;
                __DSP_rude_task_pending = 0;
                if (__DSP_curr_task->resumeCallback != 0) {
                    __DSP_curr_task->resumeCallback(__DSP_curr_task);
                }
            } else {
                DSPSendMailToDSP(0xCDD10001);
                while (DSPCheckMailToDSP() != 0) {
                }
                __DSP_exec_task(__DSP_curr_task, __DSP_rude_task);
                __DSP_curr_task->state = 2;
                __DSP_curr_task = __DSP_rude_task;
                __DSP_rude_task_pending = 0;
                __DSP_rude_task = 0;
            }
        } else if (__DSP_curr_task->next == 0) {
            if (__DSP_curr_task == __DSP_first_task) {
                DSPSendMailToDSP(0xCDD10003);
                while (DSPCheckMailToDSP() != 0) {
                }
                if (__DSP_curr_task->resumeCallback != 0) {
                    __DSP_curr_task->resumeCallback(__DSP_curr_task);
                }
            } else {
                DSPSendMailToDSP(0xCDD10001);
                while (DSPCheckMailToDSP() != 0) {
                }
                __DSP_exec_task(__DSP_curr_task, __DSP_first_task);
                __DSP_curr_task->state = 2;
                __DSP_curr_task = __DSP_first_task;
            }
        } else {
            DSPSendMailToDSP(0xCDD10001);
            while (DSPCheckMailToDSP() != 0) {
            }
            __DSP_exec_task(__DSP_curr_task, __DSP_curr_task->next);
            __DSP_curr_task->state = 2;
            __DSP_curr_task = __DSP_curr_task->next;
        }
        break;
    case (s32)0xDCD10003:
        if (__DSP_rude_task_pending != 0) {
            if (__DSP_curr_task->doneCallback != 0) {
                __DSP_curr_task->doneCallback(__DSP_curr_task);
            }
            DSPSendMailToDSP(0xCDD10001);
            while (DSPCheckMailToDSP() != 0) {
            }
            __DSP_exec_task(0, __DSP_rude_task);
            __DSP_remove_task(__DSP_curr_task);
            __DSP_curr_task = __DSP_rude_task;
            __DSP_rude_task_pending = 0;
            __DSP_rude_task = 0;
        } else if (__DSP_curr_task->next == 0) {
            if (__DSP_curr_task == __DSP_first_task) {
                if (__DSP_curr_task->doneCallback != 0) {
                    __DSP_curr_task->doneCallback(__DSP_curr_task);
                }
                DSPSendMailToDSP(0xCDD10002);
                while (DSPCheckMailToDSP() != 0) {
                }
                __DSP_curr_task->state = 3;
                __DSP_remove_task(__DSP_curr_task);
            } else {
                if (__DSP_curr_task->doneCallback != 0) {
                    __DSP_curr_task->doneCallback(__DSP_curr_task);
                }
                DSPSendMailToDSP(0xCDD10001);
                while (DSPCheckMailToDSP() != 0) {
                }
                __DSP_curr_task->state = 3;
                __DSP_exec_task(0, __DSP_first_task);
                __DSP_curr_task = __DSP_first_task;
                __DSP_remove_task(__DSP_last_task);
            }
        } else {
            if (__DSP_curr_task->doneCallback != 0) {
                __DSP_curr_task->doneCallback(__DSP_curr_task);
            }
            DSPSendMailToDSP(0xCDD10001);
            while (DSPCheckMailToDSP() != 0) {
            }
            __DSP_curr_task->state = 3;
            __DSP_exec_task(0, __DSP_curr_task->next);
            __DSP_curr_task = __DSP_curr_task->next;
            __DSP_remove_task(__DSP_curr_task->prev);
        }
        break;
    case (s32)0xDCD10004:
        if (__DSP_curr_task->requestCallback != 0) {
            __DSP_curr_task->requestCallback(__DSP_curr_task);
        }
        break;
    }

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}
