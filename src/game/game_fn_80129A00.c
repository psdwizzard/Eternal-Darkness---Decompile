typedef unsigned char u8;

#define FN_80128E30_RETURN u8*
#define FN_80128E30_PARAMETERS void*
extern FN_80128E30_RETURN fn_80128E30(FN_80128E30_PARAMETERS);
extern int fn_80129C2C(void*, u8*, int, int, int);
extern void fn_80129CE8(void*, u8*, int, int, int);
extern void fn_80129BA4(u8*, float, float);
extern void fn_80129DE0(void*, u8*, int, int);

u8* fn_80129A00(void* owner, int value, int flags, float a, float b)
{
    u8* entry = fn_80128E30(owner);
    if (fn_80129C2C(owner, entry, value, flags, 5)) {
        u8* resource = *(u8**)(entry + 0xB8);
        if (resource != 0) {
            *(u8*)(*(u8**)((u8*)owner + 0x40) + 0x884) = resource[0xD];
        }
        fn_80129CE8(owner, entry, value, flags, 5);
        fn_80129BA4(entry, a, b);
        fn_80129DE0(owner, entry, !(flags & 0x10000), 1);
    } else {
        entry = 0;
    }
    return entry;
}
