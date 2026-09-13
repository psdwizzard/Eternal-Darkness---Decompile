extern unsigned short fn_8013B920(void*, void*, int, int, int);

int fn_8013B178(void* object, unsigned char* state, int enable, int mode, int update)
{
    unsigned int mask;
    int zero;
    zero = (mode == 0) & 1;
    mask = zero ? 1 : 2;

    if ((*(unsigned int*)(state + 0x68) & mask) != 0) {
        if (enable == 0) {
            if (mode == 0) {
                if (update != 0)
                    *(unsigned int*)(state + 0x68) &= ~mask;
                return 2;
            }
            if (fn_8013B920(object, state, enable, mode, update) == 0) {
                if (update != 0) {
                    unsigned int current = *(unsigned int*)(state + 0x68);
                    *(unsigned int*)(state + 0x68) = current & ~mask;
                }
                return 2;
            }
        } else {
            return 3;
        }
    } else if (enable != 0) {
        if (update != 0)
            *(unsigned int*)(state + 0x68) |= mask;
        return 1;
    }
    return 0;
}
