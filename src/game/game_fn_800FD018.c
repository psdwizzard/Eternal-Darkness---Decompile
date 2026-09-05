typedef void (*ExitHandler)(int);

extern ExitHandler lbl_8032CBF0[6];
extern void exit(int);

int fn_800FD018(int index)
{
    ExitHandler handler;

    if (index < 1 || index > 6) {
        return -1;
    }

    handler = lbl_8032CBF0[index - 1];
    if (handler != (ExitHandler)1) {
        lbl_8032CBF0[index - 1] = 0;
    }

    if (handler == (ExitHandler)1 || (handler == 0 && index == 1)) {
        return 0;
    }
    if (handler == 0) {
        exit(0);
    }
    handler(index);
    return 0;
}
