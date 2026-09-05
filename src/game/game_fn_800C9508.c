typedef struct CallbackEntry {
    void *object;
    void *callback;
} CallbackEntry;

extern int lbl_8064CAB0;
extern CallbackEntry lbl_80325450[];

#pragma opt_dead_assignments off
void fn_800C9508(void *object, void *callback)
{
    int index = lbl_8064CAB0;

    lbl_80325450[index].object = object;
    lbl_80325450[index].callback = callback;
    lbl_8064CAB0 = index + 1;
}
#pragma opt_dead_assignments reset
