typedef unsigned char u8;

extern void* lbl_8064D544;
extern int lbl_8064D538;

void fn_801D1790(void* target, int value)
{
    void* saved = target;

    if (saved == 0) {
        return;
    }
    *(int*)((u8*)saved + 0x34) = value;
    target = lbl_8064D544;
    while (target != 0) {
        if (*(int*)((u8*)target + 0xC) == *(int*)((u8*)saved + 0xC) &&
            *(int*)((u8*)target + 4) == lbl_8064D538 &&
            ((u8*)target)[0xFF1] == 6) {
            *(int*)((u8*)target + 0x34) = value;
            return;
        }
        target = *(void**)((u8*)target + 0x14);
    }
}
