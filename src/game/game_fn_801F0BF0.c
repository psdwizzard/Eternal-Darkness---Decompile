typedef signed long s32;
typedef unsigned char u8;

#pragma use_lmw_stmw on

extern void fn_801ED468(s32);
extern void fn_801F08B8(void*, void*, void*);

void fn_801F0BF0(u8* context, void* arg, s32 upper_half)
{
    u8* item;
    s32 i;
    void** lists = (void**)(context + 0x138);

    fn_801ED468(0x1B);
    if (upper_half != 0) {
        i = 0x1000;
        do {
            item = lists[i];
            while (item != 0) {
                fn_801F08B8(item, context, arg);
                item = *(u8**)(item + 0x10);
            }
            i++;
        } while (i < 0x2000);
    } else {
        i = 0;
        do {
            item = lists[i];
            while (item != 0) {
                fn_801F08B8(item, context, arg);
                item = *(u8**)(item + 0x10);
            }
            i++;
        } while (i < 0x1000);
    }
}
