typedef void (*ExitHandler)(int);

extern ExitHandler signal_funcs[6];
extern void exit(int);

int raise(int index)
{
    ExitHandler handler;

    if (index < 1 || index > 6) {
        return -1;
    }

    handler = signal_funcs[index - 1];
    if (handler != (ExitHandler)1) {
        signal_funcs[index - 1] = 0;
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
