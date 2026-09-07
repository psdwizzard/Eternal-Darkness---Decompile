typedef struct Object Object;
typedef struct Child Child;

struct Child {
    void* pad0;
    Child* next;
    Object* object;
};

struct Object {
    char pad0[0x14];
    Child* children;
    char pad18[4];
    unsigned int (*callback2)(Object*, void*);
    unsigned int (*callback1)(Object*, void*, unsigned int);
    char pad24[0x14];
    void* callback_arg;
    char pad3c[8];
    unsigned int flags;
};

#pragma use_lmw_stmw on

extern unsigned int lbl_8064D0D0;
extern void fn_8015644C(unsigned int, Object*);

int fn_80156480(Object* object, unsigned int events, unsigned int control)
{
    int clear_mask;
    int set_mask;
    unsigned int result = 0;
    Child* child;
    unsigned int flags;

    clear_mask = (control & 0x80) != 0 ? 0x80 : 0x10;
    if ((control & 0x100) != 0) {
        set_mask = 0x100;
    } else {
        set_mask = 0x40;
        if ((control & 0x20) != 0)
            set_mask = 0x20;
    }

    flags = object->flags;
    if ((flags & 2) != 0) {
        flags |= set_mask;
        object->flags = flags;
        object->flags &= ~clear_mask;
    } else if ((flags & clear_mask) != 0) {
        result = 1;
    } else if ((flags & set_mask) == 0) {
        child = object->children;
        object->flags |= clear_mask;
        lbl_8064D0D0++;
        while (child != 0) {
            result |= fn_80156480(child->object, events, control);
            child = child->next;
        }
        lbl_8064D0D0--;

        if ((events & 1) != 0 && object->callback1 != 0) {
            unsigned int callback_result = object->callback1(object, object->callback_arg,
                                                               control & 0x800);
            fn_8015644C(callback_result, object);
        }
        if ((events & 2) != 0 && object->callback2 != 0) {
            unsigned int callback_result = object->callback2(object, object->callback_arg);
            fn_8015644C(callback_result, object);
        }
        object->flags |= set_mask;
        object->flags &= ~clear_mask;
    }
    return result;
}
