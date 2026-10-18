typedef signed int s32;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct DSPTask DSPTask;
struct DSPTask {
    u32 state;
    volatile u32 priority;
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

typedef struct DSPTaskInfo DSPTaskInfo;

extern s32 OSDisableInterrupts(void);
extern s32 OSRestoreInterrupts(s32 enable);
extern void __DSP_insert_task(DSPTask *task);
extern void fn_8021C0B4(DSPTaskInfo *task);
extern DSPTask *__DSP_first_task;

/* Queue a DSP task and boot it if it is the first task. */
DSPTask *DSPAddTask(DSPTask *task)
{
    s32 enabled;

    enabled = OSDisableInterrupts();
    __DSP_insert_task(task);
    task->state = 0;
    task->flags = 1;
    OSRestoreInterrupts(enabled);
    if (task == __DSP_first_task) {
        fn_8021C0B4((DSPTaskInfo *)task);
    }
    return task;
}
