extern int fn_8016A598(void*);
extern double fn_8016A694(void*, int);
extern void fn_80163BB4(void*, const char*, ...);
extern void* fn_8017AF64(void);
extern void fn_8017AF78(void);
extern int fn_80220A68(int, void*, int);
extern int fn_802213DC(int);
extern int fn_80220B4C(int);
extern void fn_8017BA60(const char*, int);

int fn_80176A94(void* state)
{
    void* handle;
    int id;
    int result;

    handle = fn_8017AF64();
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    result = (int)fn_8016A694(state, 1);
    id = result;
    result = fn_80220A68(id, handle, 0);
    if (result == 0 || result == -6) {
        result = fn_802213DC(id);
        if (result == 0) {
            int name = fn_80220B4C(id);
            if (name != 0) {
                fn_8017BA60("Couldn't unmount: ", name);
            }
        } else {
            fn_8017BA60("Couldn't format: ", result);
        }
    } else {
        fn_8017BA60("Couldn't mount card: ", result);
    }

    fn_8017AF78();
    return 0;
}
