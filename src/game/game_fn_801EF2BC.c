typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ValueSet {
    short values[12];
    u32 flags;
} ValueSet;

extern void* lbl_8064D5FC;
extern u16 fn_801F6034(short, int);
extern void fn_8015DB84(void*, void*, int);
extern u16 fn_8022892C(void*);
extern u16 fn_8022893C(void*);

int fn_801EF2BC(ValueSet* set, int index, int value, int* out0, int* out1)
{
    u32 data[8];
    int selected;

    if (set != 0) {
        if (set->flags & (1 << index)) {
            selected = fn_801F6034(set->values[index], value);
        } else {
            selected = set->values[index];
        }
        fn_8015DB84(lbl_8064D5FC, data, selected);
        *out0 = fn_8022892C(data);
        *out1 = fn_8022893C(data);
    }
    return 0;
}
