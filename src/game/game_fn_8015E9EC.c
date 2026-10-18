typedef unsigned int u32;

extern char lbl_805FAA40[];
extern char lbl_805E2BDC[];
extern void DCInvalidateRange(void*, u32);
extern void ARQPostRequest(void*, int, int, int, u32, void*, u32, void*);
extern int OSReceiveMessage(void*, int, int);
extern void fn_8015E8E8(void);

void fn_8015E9EC(u32 value, void* destination, u32 size)
{
    unsigned long long aligned;

    DCInvalidateRange(destination, aligned = (unsigned long long)((size + 31) & ~31));
    ARQPostRequest(lbl_805FAA40, 8, 1, 0, value, destination, (u32)aligned,
                fn_8015E8E8);
    OSReceiveMessage(lbl_805E2BDC, 0, 1);
}
