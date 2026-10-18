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

/* Insert a DSP task in ascending priority order. */
void __DSP_insert_task(DSPTask *task)
{
    DSPTask *current;

    if (__DSP_first_task == 0) {
        __DSP_curr_task = task;
        __DSP_last_task = task;
        __DSP_first_task = task;
        task->prev = 0;
        task->next = 0;
        return;
    }

    for (current = __DSP_first_task; current != 0; current = current->next) {
        if (task->priority < current->priority) {
            task->prev = current->prev;
            current->prev = task;
            task->next = current;
            if (task->prev == 0) {
                __DSP_first_task = task;
            } else {
                task->prev->next = task;
            }
            break;
        }
    }

    if (current == 0) {
        __DSP_last_task->next = task;
        task->next = 0;
        task->prev = __DSP_last_task;
        __DSP_last_task = task;
    }
}
