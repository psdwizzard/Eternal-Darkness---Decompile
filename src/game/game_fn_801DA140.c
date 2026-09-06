typedef unsigned char u8;
typedef unsigned int u32;

extern void* lbl_8064D544;
extern u32 fn_8017FDA0(void*);
extern u32 fn_8017FDFC(void*);
extern int fn_8017FEAC(void*);

void fn_801DA140(int owner, int value, void* output)
{
    u8 first;
    void* found = 0;
    char* node = lbl_8064D544;

    while (node != 0) {
        if (*(int*)(node + 0xC) == owner &&
            (*(int*)(node + 4) & 0x1FF0) == 0x1010 &&
            *(u8*)(node + 0xFF1) == 2 &&
            *(int*)(node + 0xBC) == value &&
            *(void**)(node + 0x18C) != 0) {
            found = *(void**)((char*)*(void**)(node + 0x18C) + 0x88);
            break;
        }
        node = *(char**)(node + 0x14);
    }

    if (found != 0) {
        u8 second;
        first = fn_8017FDA0(found);
        second = fn_8017FDFC(found);
        if (second != first && fn_8017FEAC(found) == 0) {
            *(u32*)((char*)output + 0xE8) = 1;
            *(u8*)((char*)output + 0x1BF) = 0;
        }
    }
}
