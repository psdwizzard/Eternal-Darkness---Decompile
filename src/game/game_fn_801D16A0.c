typedef unsigned char u8;

int fn_801D16A0(void* object, int kind)
{
    int result = 0;

    if (object != 0) {
        int valid = 0;
        if ((*(int*)((u8*)object + 4) & 0x1FF0) == kind) {
            u8 type = ((u8*)object)[0xFF1];
            if (type == 0 || type == 6) {
                valid = 1;
            }
        }
        result = valid;
    }
    return result;
}
