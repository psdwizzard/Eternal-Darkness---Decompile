extern int fn_80201AE4(void);
extern void fn_80046C90(int enabled);
extern void fn_801D16E4(int id, int disabled);
extern void fn_801E1B58(int id, int enabled);
extern void fn_80047080(int object_id);
extern void fn_80046E98(int object_id);

void fn_80046E20(int enabled)
{
    int object_id = fn_80201AE4();

    fn_80046C90(enabled);
    fn_801D16E4(object_id, enabled);
    fn_801E1B58(object_id, enabled);
    if (enabled != 0) {
        fn_80047080(object_id);
    } else {
        fn_80046E98(object_id);
    }
}
