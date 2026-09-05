typedef unsigned char u8;
typedef struct Runtime80095D10 {
    u8 pad00[0x68];
    int* values;
} Runtime80095D10;

extern void *fn_80201BC8(void *);
extern void *fn_80201B8C(void *);
extern void* fn_80201B3C(void);
extern int fn_80128EAC(void*);
extern int fn_80038308(void*, int, short*);
extern int fn_80038464(void*, int, short*);
extern int fn_80201B64(void*);
extern const float lbl_8064ECD4;

#pragma global_optimizer off
int fn_80095D10(register void* object)
{
    register void* owner;
    register int* values;
    register void* current;
    register int kind;
    register float ratio;
    short numerator;
    short denominator;

    owner = fn_80201BC8(object);
    values = ((Runtime80095D10*)fn_80201B8C(object))->values;
    if (values[0] != 0) {
        return 1;
    }
    if (values[1] != 0) {
        return 2;
    }

    current = fn_80201B3C();
    kind = fn_80128EAC(owner);
    fn_80038308(current, 1, &numerator);
    fn_80038464(current, 1, &denominator);
    ratio = (float)(numerator / denominator);

    if (fn_80201B64(object) == 5 || kind == 46 || kind == 47) {
        return 3;
    }
    if ((values[11] & 0x400) != 0) {
        return 7;
    }
    if (ratio < lbl_8064ECD4) {
        return 5;
    }
    if ((values[11] & 1) != 0) {
        return 6;
    }
    return 4;
}
#pragma global_optimizer reset
