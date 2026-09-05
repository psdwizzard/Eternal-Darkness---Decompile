extern int fn_8016A598(void*);
extern double fn_8016A694(void*, int);
extern void fn_80163BB4(void*, const char*, ...);
extern void fn_8020104C(int, void*, void*, int, float);
extern const char lbl_8024FF54[];

#pragma opt_propagation off
int fn_8016D480(void* state)
{
    int count;
    int x;
    void* context;
    unsigned int flags;
    int y;
    float z;

    context = state;
    count = fn_8016A598(context);
    flags = 0;
    switch (count) {
    case 4:
        flags = (int)fn_8016A694(context, 4);
    case 3:
        x = (int)fn_8016A694(context, 1);
        y = (int)fn_8016A694(context, 2);
        z = (float)fn_8016A694(context, 3);
        break;
    default:
        fn_80163BB4(context, lbl_8024FF54, count);
        return 0;
    }
    if (x != 0) {
        fn_8020104C(y, 0, (void*)x, flags, z);
    }
    return 0;
}
#pragma opt_propagation reset
