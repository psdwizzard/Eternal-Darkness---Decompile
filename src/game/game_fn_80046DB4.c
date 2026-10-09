typedef signed int s32;

extern void fn_80046C98(s32 enabled);
extern s32 fn_80201B44(void);
extern void fn_801D16E4(s32 object_id, s32 enabled);
extern void fn_801E1B58(s32 object_id, s32 enabled);
extern void fn_80047080(s32 object_id);
extern void fn_80046E98(s32 object_id);

void fn_80046DB4(s32 enabled)
{
    s32 object_id;

    fn_80046C98(enabled);
    object_id = fn_80201B44();
    fn_801D16E4(object_id, enabled);
    fn_801E1B58(object_id, enabled);
    if (enabled != 0) {
        fn_80047080(object_id);
    } else {
        fn_80046E98(object_id);
    }
}
