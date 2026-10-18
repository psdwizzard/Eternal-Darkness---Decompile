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

extern DSPTask *__DSP_last_task; /* Last task. */
extern DSPTask *__DSP_first_task; /* First task. */
extern DSPTask *__DSP_curr_task; /* Current task. */

/* Remove a completed DSP task from the task list. */
void __DSP_remove_task(DSPTask *task)
{
    task->flags = 0;
    task->state = 3;

    if (__DSP_first_task == task) {
        if (task->next != 0) {
            __DSP_first_task = task->next;
            task->next->prev = 0;
        } else {
            __DSP_curr_task = 0;
            __DSP_last_task = 0;
            __DSP_first_task = 0;
        }
    } else if (__DSP_last_task == task) {
        __DSP_last_task = task->prev;
        task->prev->next = 0;
        __DSP_curr_task = __DSP_first_task;
    } else {
        __DSP_curr_task = task->next;
        task->prev->next = task->next;
        task->next->prev = task->prev;
    }
}
