extern int fn_80201AE4(void);
extern void* fn_80201B9C(void);
extern void* fn_80204844(void*, int);
extern void fn_802020B4(void*, int);

void fn_801E1B04(int id, int enabled)
{
    int current = fn_80201AE4();
    if (current == id) {
        fn_802020B4(fn_80204844(fn_80201B9C(), 34), enabled);
    }
}
