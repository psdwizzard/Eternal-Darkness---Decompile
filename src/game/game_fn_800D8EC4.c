typedef unsigned int u32;

extern u32 lbl_8064F42C;
extern u32 lbl_80651ABC;
typedef struct Defaults {
    u32 second;
    u32 first;
} Defaults;

extern void fn_8012C478(void *, int, void *, u32);
extern void* fn_8012C62C(void *, int, u32 *, u32 *, u32 *, int);

void fn_800D8EC4(void *unused, void *object, void *argument)
{
    volatile Defaults values;
    u32 call_value;
    u32 first;
    u32 second;
    u32 third;
    u32 other;
    u32 shared;

    (void)unused;
    call_value = lbl_8064F42C;
    values.first = call_value;
    values.second = lbl_80651ABC;
    fn_8012C478(object, 14, argument, call_value);
    shared = ((Defaults *)&values)->first;
    other = ((Defaults *)&values)->second;
    third = shared;
    second = other;
    first = shared;
    fn_8012C62C(object, 8, &first, &second, &third, 4);
}
