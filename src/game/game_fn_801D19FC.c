extern void* fn_80201814(void*);
extern void* fn_80201C24(void);
extern void* fn_80157924(void*);
extern void fn_8017FD6C(void*);
extern void fn_802006D4(void*, void*, int, int, int);
extern void fn_8020123C(int, void*, void*, int);

void fn_801D19FC(void* object, int value)
{
    if (fn_80201814(object) != 0) {
        void* current = fn_80157924(fn_80201C24());
        if (current != 0) {
            fn_8017FD6C(current);
        }
        fn_802006D4(object, object, -1, 75, 0);
        fn_8020123C(75, object, object, value);
    }
}
