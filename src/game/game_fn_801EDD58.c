typedef struct Entry {
    int object;
    int unused;
    int type;
    int parameter;
    int value;
    int state;
    int flags;
} Entry;

extern Entry lbl_8063BC98[];
extern int lbl_8064D630;
extern void* lbl_8064D678;

extern void fn_800FBE38(void*, int, int, void*);
extern int fn_801EDF5C(const void*, const void*);
extern void fn_801EDEC4(int, int, int, int);
extern void fn_801EDE34(int, int, int, int);

void fn_801EDD58(void)
{
    fn_800FBE38(lbl_8063BC98, lbl_8064D630, sizeof(Entry), fn_801EDF5C);
    {
    int i;
    for (i = 0; i < lbl_8064D630; i++) {
        Entry* entry = &lbl_8063BC98[i];
        if (entry->type < 2) {
            goto generic;
        }
        if (entry->type <= 9) {
            if (lbl_8064D678 == 0) {
                fn_801EDEC4(i, entry->type, 13, entry->value);
            } else {
                fn_801EDEC4(i, entry->type, 12, entry->value);
            }
            goto finished;
        } else {
generic:
            fn_801EDEC4(i, ((volatile Entry*)entry)->type, entry->parameter, entry->value);
        }
finished:
        fn_801EDE34(entry->object, i, entry->flags, entry->state);
    }
    }
}
