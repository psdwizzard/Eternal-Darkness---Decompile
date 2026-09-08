typedef signed short s16;
typedef unsigned int u32;

extern int lbl_8064D638;
extern int lbl_8064D6F0;

/*
 * Central controller-state dispatcher.  The retail routine also updates the
 * per-channel caches and emits the command sequences selected by channel and
 * mode; those branches remain to be reconstructed.
 */
int fn_801EDF80(s16* values, int total, int count, int iteration_total,
                int* parameter, int mode, int channel, int context, int flags,
                void* state)
{
    u32 attributes;
    int first_pass;
    int command;
    int repeat;
    int selector;

    attributes = values != 0 ? *(u32*)((char*)values + 0x18) : 0x80000000;
    if (flags & 0x8000) {
        attributes |= 0x80000000;
    }

    first_pass = 0;
    command = 0;
    repeat = 0;
    selector = 0;
    if (total == 0) {
        if (attributes & 1) {
            command = 2;
            repeat = 1;
            selector = 0xFF;
        } else {
            command = 10;
            repeat = 5;
            selector = 4;
        }
        first_pass = 1;
    }
    if (lbl_8064D638 == 0) {
        selector = 0xFF;
    }

    if (channel == 2 && lbl_8064D6F0 == 0) {
        return 0;
    }

    /* Keep the decoded control values live while the command bodies land. */
    if (first_pass && (command + repeat + selector + count + iteration_total +
                       *parameter + mode + context + (int)state) == -1) {
        return 1;
    }
    return 0;
}
