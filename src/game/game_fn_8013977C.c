typedef unsigned short u16;

typedef struct Resource {
    unsigned char pad00[0x14];
    u16 count;
} Resource;

typedef struct Child {
    int unused;
    int id;
    unsigned char pad08[8];
} Child;

typedef struct Slot {
    unsigned char pad00[0x44];
    Resource* resource;
    Child* children;
} Slot;

typedef struct Object {
    unsigned char pad00[0x16];
    unsigned char state;
} Object;

extern Object* fn_80134F08(int);
extern void fn_801354A0(Object*);

#pragma opt_propagation off
#pragma optimization_level 1
int fn_8013977C(Slot* slot)
{
    int zero;
    int offset;
    int i;
    int result;
    Slot* saved;

    offset = 0;
    saved = slot;
    zero = offset;
    result = 0;
    i = 0;
    while (i < saved->resource->count) {
        Object* object = fn_80134F08(*(int*)((char*)saved->children + offset + 4));
        if (object != 0) {
            object->state = zero;
            fn_801354A0(object);
            result++;
        }
        offset += 0x10;
        i++;
    }
    return result;
}
#pragma opt_propagation reset
#pragma optimization_level reset
