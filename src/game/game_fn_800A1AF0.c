typedef unsigned int u32;

extern void* fn_8012C62C(void*, int, u32*, u32*, u32*, int);
extern void fn_8012F58C(void*, int, int, int, int, int);
extern void fn_8012C278(void*, int, int, int, u32*, u32*, u32*, int);

/* NonMatching: behavior- and size-exact. Volatile-qualified source reads and
 * explicit temporaries recover retail's load order and register allocation.
 * GC/1.3 still materializes &third one instruction before retail does. */
void fn_800A1AF0(void* object, int index, int active, int copy_values,
                 volatile u32* first_in, volatile u32* second_in,
                 volatile u32* third_in, int mode)
{
    u32 first;
    u32 second;
    u32 third;

    if (copy_values) {
        u32 first_value;
        u32 second_value;
        u32 third_value;
        second_value = *second_in;
        first_value = *first_in;
        third_value = *third_in;
        second = second_value;
        third = third_value;
        first = first_value;
        fn_8012C62C(object, index, &first, &second, &third, mode);
        if (!active) {
            fn_8012F58C(object, index, 0, 0, 0, 2);
        }
    } else {
        fn_8012C278(object, index, active, copy_values, (u32*)first_in,
                    (u32*)second_in, (u32*)third_in, mode);
    }
}
