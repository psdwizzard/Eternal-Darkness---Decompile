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

extern DSPTask *lbl_8064DB74; /* Last task. */
extern DSPTask *lbl_8064DB78; /* First task. */
extern DSPTask *lbl_8064DB7C; /* Current task. */

/* Remove a completed DSP task from the task list. */
void fn_8021C2E0(DSPTask *task)
{
    task->flags = 0;
    task->state = 3;

    if (lbl_8064DB78 == task) {
        if (task->next != 0) {
            lbl_8064DB78 = task->next;
            task->next->prev = 0;
        } else {
            lbl_8064DB7C = 0;
            lbl_8064DB74 = 0;
            lbl_8064DB78 = 0;
        }
    } else if (lbl_8064DB74 == task) {
        lbl_8064DB74 = task->prev;
        task->prev->next = 0;
        lbl_8064DB7C = lbl_8064DB78;
    } else {
        lbl_8064DB7C = task->next;
        task->prev->next = task->next;
        task->next->prev = task->prev;
    }
}
