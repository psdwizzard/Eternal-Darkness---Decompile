typedef unsigned int u32;

typedef struct Owner {
    unsigned char pad_00[0x38];
    void *resource;
} Owner;

extern void *fn_80201B9C();
extern void *fn_80204844(void *heap, int size);
extern Owner *fn_8006D444(void *);
extern int fn_8006BCE4(Owner *owner);
extern void fn_8006D1DC(void);
extern void *fn_80201814(void *);
extern void fn_8006E754(Owner *owner, int value);
extern void fn_8006F544(Owner *owner, int value);
extern void fn_80070C3C(void);
extern int fn_801A5CE0(void);
extern int fn_801A5D04(void);
extern void fn_801A5C30(int value);
extern void fn_80070F74(Owner *owner);
extern void fn_8006E644(int kind, Owner *owner);
extern void fn_8006BD78(Owner *owner);
extern void fn_802020B4(void *object, int value);
extern void fn_8011E174(int value, int zero);

void fn_8006E53C(void)
{
    Owner *owner;
    void *object;
    int kind;

    object = fn_80204844(fn_80201B9C(), 0x20);
    if (object != 0 && (owner = fn_8006D444(object)) != 0) {
        kind = fn_8006BCE4(owner);
        if (kind != -1) {
            fn_8006D1DC();
            switch (kind) {
            case 9:
            case 11:
            case 16:
            case 17:
            case 18:
            case 19:
            case 29:
            case 32:
            case 33:
            case 35:
            case 36:
                fn_80201814(owner->resource);
                fn_8006E754(owner, 1);
                fn_8006F544(owner, 1);
                fn_80070C3C();
                if (!fn_801A5CE0() && !fn_801A5D04()) {
                    fn_801A5C30(1);
                }
                break;
            default:
                fn_80070F74(owner);
                break;
            }
            fn_8006E644(kind, owner);
            fn_8006BD78(owner);
            fn_802020B4(object, 1);
        }
        fn_8011E174(0x100, 0);
    }
}
