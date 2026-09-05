typedef unsigned int u32;
typedef signed int s32;

extern void fn_801D0BBC(u32, u32, void*, s32*);
extern s32 fn_801D0814(u32, u32, u32, void*, void*, u32, void*, u32, s32*);

s32 fn_801D0794(u32 arg0, u32 arg1, u32 arg2, void* arg3, void* arg4,
                u32 arg5, void* arg6, u32 arg7)
{
    s32 dispatch_data;

    fn_801D0BBC(arg0, arg2, arg3, &dispatch_data);
    return fn_801D0814(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                       &dispatch_data);
}
