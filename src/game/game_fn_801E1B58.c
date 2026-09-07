extern int fn_80201AE4(void);
extern void* fn_80201B9C(void);
extern void* fn_80204844(void*, int);
extern void* fn_80201B8C(void);
extern void* fn_80201814(void*);
extern void* fn_80201BC8(void);
extern void fn_8012C478(void*, int, int);

void fn_801E1B58(int id, int enabled)
{
    int current = fn_80201AE4();
    if (current == id &&
        fn_80204844(fn_80201B9C(), 0x22) != 0 &&
        fn_80201814(*(void**)((char*)*(void**)((char*)fn_80201B8C() + 0x3C) + 0x18)) != 0) {
        void* context = fn_80201BC8();
        if (enabled != 0) {
            fn_8012C478(context, 0xF, 1);
        } else {
            fn_8012C478(context, 0xF, 0);
        }
    }
}
