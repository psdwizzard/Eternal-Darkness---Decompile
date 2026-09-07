extern void* memset(void*, int, unsigned long);

void fn_801E5FB0(void* object)
{
    if (object != 0) {
        memset((char*)object + 0x1A, 0, 0x5E6);
    }
}
