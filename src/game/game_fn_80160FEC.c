typedef struct Child {
    char _pad00[0x194];
    int state;
} Child;

typedef struct Object {
    char _pad00[0x14];
    Child* child;
} Object;

extern char lbl_8024F5C0[];
extern void __longjmp(Child*, int);
extern void message(Object*, char*);
extern void exit(int);

void luaD_breakrun(Object* object, int state)
{
    Child* child = object->child;

    if (child != 0) {
        child->state = state;
        __longjmp(object->child, 1);
    } else {
        if (state != 4) {
            message(object, lbl_8024F5C0);
        }
        exit(1);
    }
}
