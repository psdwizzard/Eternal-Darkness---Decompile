typedef unsigned char u8;

extern int fn_801FA250(void*, int, void*);
extern void fn_801A6EE0(int);
extern void fn_801FA01C(void*, int, int, int, int, int, int, int, void*, int);
extern u8 lbl_8063D378[];

int fn_801FA198(void* resource, void* state, int parent_mode, int child_mode,
                int set_global, int endpoint, int reverse, int clear_existing,
                void* resource_handle)
{
    int index = fn_801FA250(resource, 2, resource_handle);
    int result = 1;

    if (index != -1) {
        fn_801A6EE0(index);
        fn_801FA01C(state, index, parent_mode, child_mode, endpoint, reverse,
                    set_global, clear_existing, resource_handle, 0);
        if (set_global == 0) {
            *(int*)(lbl_8063D378 + 0x40) = 1;
        }
    } else {
        result = 0;
    }
    return result;
}
