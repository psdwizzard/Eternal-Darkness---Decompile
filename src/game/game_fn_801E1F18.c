typedef signed short s16;
typedef unsigned int u32;
typedef int s32;

typedef struct Pair Pair;
struct Pair {
    s16 first;
    s16 second;
};

extern void fn_801E2408(void);
extern void fn_801D0CA4(void);
extern void* fn_801D0D78(s32, u32, u32, u32, void*, u32, u32, u32, u32, u32);
extern void* fn_801D38E8(u32);
extern void fn_801D38BC(void*, Pair*, Pair*);
extern s32 fn_801CEB2C(u32);
extern void fn_801CE594(u32, u32, u32, s32, s32, s16, s32, s32,
                       u32, s32, s32, s32, void*, void*, Pair*);

void* fn_801E1F18(s32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4,
                  u32 arg5, u32 arg6, u32 arg7, u32 arg8)
{
    Pair pair1;
    Pair pair3;
    Pair pair2;
    void* work = fn_801D0D78(arg0, arg1, arg2, arg3, fn_801E2408,
                             arg5, arg6, arg7, arg8, arg4);
    void* value = fn_801D38E8(arg1);
    fn_801D38BC(value, &pair1, &pair2);
    pair3 = pair1;
    fn_801CE594(arg1, arg2, arg3, fn_801CEB2C(arg1), 250, pair2.first,
                128, 0, arg3, 138, 0, 600, fn_801D0CA4, work, &pair3);
    return work;
}
