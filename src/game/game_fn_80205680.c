typedef unsigned int u32;
typedef unsigned long long u64;

extern int fn_80201B54(void *object);
extern int fn_80201B5C(void *object);
extern u64 fn_8020123C(int kind, int parent, int object, int value);
extern void fn_80201D34(void *object, int value);
extern void fn_80201D1C(void *object, int value);

void fn_80205680(void *object, int parent, int value)
{
    u32 result;

    if (object != 0) {
        if (value != fn_80201B5C(object)) {
            result = 0;
            if (fn_80201B5C(object) != 0) {
                result = fn_8020123C(0xF0, parent, fn_80201B54(object), value) &
                         0xFFFFFFFFULL;
            }

            if (result == 0) {
                fn_80201D34(object, value);
                fn_80201D1C(object, 1);
            }
        }
    }
}
