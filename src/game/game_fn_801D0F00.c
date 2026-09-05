extern void fn_801DA890(int);
extern void fn_801E20D0(int);
extern int fn_80201AE4(void);
extern void* fn_80201B9C(void);
extern void* fn_80204844(void*, int);
extern int fn_80201B54(void);
extern void fn_8020123C(int, int, int, int);

void fn_801D0F00(int object)
{
    fn_801DA890(object);
    fn_801E20D0(object);
    if (object == fn_80201AE4()) {
        if (fn_80204844(fn_80201B9C(), 0x22) != 0) {
            int value = fn_80201B54();
            fn_8020123C(0xE8, value, value, 0);
        }
    }
}
