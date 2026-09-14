extern unsigned short fn_8013B920(void*, void*, int, int, int);

#pragma opt_propagation off
int fn_8013B178(void* object, unsigned char* state, int enable, int mode, int update)
{
    int mask;
    unsigned int flags;
    int temp;

    temp = -((mode == 0) & 1);
    mask = temp + 2;
    flags = *(unsigned int*)(state + 0x68);

    if ((flags & mask) != 0) {
        if (enable == 0) {
            if (mode == 0) {
                if (update != 0)
                    *(unsigned int*)(state + 0x68) = flags & ~mask;
                return 2;
            }
            if (fn_8013B920(object, state, enable, mode, update) == 0) {
                if (update != 0) {
                    temp = *(unsigned int*)(state + 0x68);
                    *(unsigned int*)(state + 0x68) = temp & ~mask;
                }
                return 2;
            }
        } else {
            return 3;
        }
    } else if (enable != 0) {
        if (update != 0)
            *(unsigned int*)(state + 0x68) = flags | mask;
        return 1;
    }
    return 0;
}
#pragma opt_propagation reset
