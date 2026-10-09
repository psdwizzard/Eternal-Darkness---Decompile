typedef signed int s32;

typedef struct Object Object;
typedef struct Owner Owner;

extern void *fn_80201B9C(void);
extern Object *fn_80204844(Object *object, int type);
extern void *fn_8006D444(void *object);
extern s32 fn_8006D2C8(Owner *owner, s32 kind);
extern s32 fn_8006B96C(s32 event, s32 mode);
/* The retail caller supplies an event argument unused by the callee. */
extern void fn_8006F6A4();

void fn_80046774(s32 event)
{
    Owner *owner;

    owner = (Owner *)fn_8006D444(fn_80204844(fn_80201B9C(), 0x20));
    if (fn_8006D2C8(owner, 0xD) != 0 && fn_8006B96C(event, 5) == -1) {
        fn_8006F6A4(owner, event);
    }
}
