#pragma use_lmw_stmw on
typedef struct Triple {
    unsigned int x;
    unsigned int y;
    unsigned int z;
} Triple;

extern void* fn_80201C24();
extern int fn_801579F4(void *);
extern void *fn_80201814();
extern void *fn_80155DB4(void *);
extern void *fn_80201BC8();
extern int fn_80201B44();
extern void fn_800DB95C(void *);
extern void fn_800DB874(void *);
extern unsigned int fn_80157C98(void *, int, int);
extern void fn_8002A754(void *, void *);
extern unsigned int fn_80157864(void *, int);
extern void* fn_8012C62C(void *, int, unsigned int *, unsigned int *, unsigned int *, int);
extern unsigned int lbl_80651AC4;
extern unsigned int lbl_80651AC0;
extern unsigned int lbl_8064F4A4;
extern unsigned int lbl_80651ACC;
extern unsigned int lbl_80651AC8;
extern unsigned int lbl_8064F4A8;

void fn_800DB4F4(void *context, int mode)
{
    int count = fn_801579F4(fn_80201C24(context));
    if (count > 0) {
        void *linked = fn_80201814(count);
        void *linked_action = fn_80155DB4(linked);
        void *object = fn_80201BC8(linked);
        void *state = fn_80201C24(linked);
        int owner = fn_80201B44();
        void *owner_action;
        fn_800DB95C(object);
        fn_800DB874(linked);
        fn_80157C98(state, 0x200, 0);
        owner_action = fn_80155DB4(fn_80201814(owner));
        fn_8002A754(linked_action, owner_action);
        if (mode == 1) {
            unsigned int z;
            unsigned int y;
            unsigned int x;
            x = lbl_80651AC4;
            y = lbl_80651AC0;
            z = lbl_8064F4A4;
            fn_8012C62C(object, 15, &z, &y, &x, 0);
        } else if (fn_80157864(state, 0) != 0) {
            unsigned int z;
            unsigned int y;
            unsigned int x;
            x = lbl_80651ACC;
            y = lbl_80651AC8;
            z = lbl_8064F4A8;
            fn_8012C62C(object, 15, &z, &y, &x, 0);
        }
    }
}
