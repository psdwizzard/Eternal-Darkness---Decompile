typedef unsigned short u16;

extern void *fn_80128E30(void *object);
extern int fn_801290D0(void *object);
extern void fn_80128F74(void *object, int flags);
extern void fn_8012880C(void *queue, int clear_optional_b0,
                        int clear_optional_a8);
extern void fn_801A7550(void *object, int value);
extern void fn_80128C28(void *object, void *callback, void *value);
extern void fn_80204230(void);

int fn_802025D8(void *unused1, int unused2, void *owner, void *effect,
                void *output)
{
    void *runtime;
    int flags;

    runtime = fn_80128E30(owner);
    *(u16 *)((char *)output + 0x34) = 0;
    flags = fn_801290D0(owner);
    fn_80128F74(owner, flags |= 2);
    fn_8012880C(runtime, 0, 0);
    fn_801A7550(effect, 0x14);
    fn_80128C28(runtime, fn_80204230, effect);
    return 1;
}
