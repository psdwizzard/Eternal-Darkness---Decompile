typedef struct Triple {
    unsigned int x;
    unsigned int y;
    unsigned int z;
} Triple;

extern void *fn_80201BC8();
extern void* fn_80201C24();
extern int fn_801579F4(void *);
extern void* fn_8012C62C(void *, int, unsigned int *, unsigned int *, unsigned int *, int);
extern void *fn_80201814();
extern unsigned int lbl_8064F48C;
extern unsigned int lbl_8064F490;
extern unsigned int lbl_8064F494;
extern unsigned int lbl_8064F498;
extern unsigned int lbl_8064F49C;
extern unsigned int lbl_8064F4A0;

#pragma opt_common_subs off
void fn_800DB430(void *context)
{
    void *object;
    int count;
    Triple first;

    object = fn_80201BC8(context);
    count = fn_801579F4(fn_80201C24(context));
    first.x = lbl_8064F494;
    first.y = lbl_8064F490;
    first.z = lbl_8064F48C;
    fn_8012C62C(object, 15, &first.z, &first.y, &first.x, 4);
    if (count > 0) {
        Triple second;
        object = fn_80201BC8(fn_80201814(count));
        second.x = lbl_8064F4A0;
        second.y = lbl_8064F49C;
        second.z = lbl_8064F498;
        fn_8012C62C(object, 15, &second.z, &second.y, &second.x, 4);
    }
}
#pragma opt_common_subs reset
