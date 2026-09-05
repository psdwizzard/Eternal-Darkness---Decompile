typedef unsigned char u8;
typedef signed short s16;

extern void *fn_80200C20(void *);
extern void *fn_80201814();
extern void* fn_80201B94();
extern int fn_80036D5C(void *);
extern void fn_80036DA4(void *, int);
extern void *fn_80201B8C();
extern int fn_80201C50(void *);

void fn_80077880(void *object, void *state, void *handle)
{
    void *resolved;
    void *secondary;
    u8 *info;
    int flags;

    resolved = fn_80201814(fn_80200C20(handle));
    secondary = fn_80201B94(resolved);
    flags = fn_80036D5C(object);
    fn_80036DA4(object, flags | 0x80);
    info = (u8 *)fn_80201B8C(resolved);
    *(s16 *)((u8 *)state + 0x152) = *(s16 *)(info + 0x98);
    *(s16 *)((u8 *)state + 0x154) = *(s16 *)(info + 0x9A);
    *(s16 *)((u8 *)state + 0x156) = fn_80201C50(secondary);
}
