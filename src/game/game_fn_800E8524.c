extern void *fn_80201BC8();
extern int fn_80128EAC(void *);
extern int fn_8012A1FC(void *, int);
extern int fn_8012A1BC(void *, int);
extern unsigned int fn_800FBFB0(void);
#define fn_800FBFB0() ((int)fn_800FBFB0())
extern void fn_801291F0(void *, int, unsigned char);
extern void *fn_801294DC(void *, int, int, int);
extern void fn_80129FD0(void *, int, int);

#pragma opt_propagation off
void fn_800E8524(void *object, int enabled)
{
    void *state = fn_80201BC8(object);
    int low = 4;

    if (low != fn_80128EAC(state)) {
        int high;
        int random;
        int value;

        low = fn_8012A1FC(state, 4);
        high = fn_8012A1BC(state, 4);
        random = low + fn_800FBFB0() % (high - low);

        if (enabled != 0) {
            int delta = random - low;
            value = delta > 2 ? delta : 2;
            value = value > 15 ? 15 : (delta > 2 ? delta : 2);
        } else {
            value = 2;
        }

        fn_801291F0(state, 4, (unsigned char)value);
        fn_801294DC(state, 4, 53, 1);
        if (enabled != 0) {
            fn_80129FD0(state, random << 17, 0);
        }
    }
}
#pragma opt_propagation reset
