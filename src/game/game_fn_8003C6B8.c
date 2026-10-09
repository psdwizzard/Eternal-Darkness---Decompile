typedef int s32;

extern void *fn_801294DC(void *, s32, s32, s32);
extern void fn_80128C28(void *, void (*)(), s32);
extern void fn_80128C44(void *, void (*)(), s32);
extern void fn_80201D2C(void *, s32);
extern void fn_80201D14(void *, s32);
extern void fn_80204810(void);

void fn_8003C6B8(void *object, void *resource, s32 id)
{
    s32 tag;
    void *created;

    created = fn_801294DC(resource, 0x2B, 0x20, 10);
    if (created != 0) {
        tag = (id << 8) | 0x77;
        fn_80128C28(created, fn_80204810, tag);
        fn_80128C44(created, fn_80204810, tag);
        fn_80201D2C(object, 0x37);
        fn_80201D14(object, 1);
    }
}
