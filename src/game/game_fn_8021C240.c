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

/* Insert a DSP task in ascending priority order. */
void fn_8021C240(DSPTask *task)
{
    DSPTask *current;

    if (lbl_8064DB78 == 0) {
        lbl_8064DB7C = task;
        lbl_8064DB74 = task;
        lbl_8064DB78 = task;
        task->prev = 0;
        task->next = 0;
        return;
    }

    for (current = lbl_8064DB78; current != 0; current = current->next) {
        if (task->priority < current->priority) {
            task->prev = current->prev;
            current->prev = task;
            task->next = current;
            if (task->prev == 0) {
                lbl_8064DB78 = task;
            } else {
                task->prev->next = task;
            }
            break;
        }
    }

    if (current == 0) {
        lbl_8064DB74->next = task;
        task->next = 0;
        task->prev = lbl_8064DB74;
        lbl_8064DB74 = task;
    }
}
