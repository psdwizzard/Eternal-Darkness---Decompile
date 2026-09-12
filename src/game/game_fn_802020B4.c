typedef unsigned int u32;

typedef struct Object802020B4 Object802020B4;

struct Object802020B4 {
    unsigned char padding[0x1C];
    u32 flags;
};

extern void* fn_80201B54(Object802020B4* object);
extern void* fn_80158598(void* object, int index);
extern int fn_80157E1C(void* collection);
extern void* fn_80157E24(void* collection, int index);
extern Object802020B4* fn_80201814(void* object);
extern int fn_80201B5C(Object802020B4* object);

void fn_802020B4(Object802020B4* object, int enabled)
{
    int i;
    void* collection;
    int count;

    if (object != 0) {
        collection = fn_80158598(fn_80201B54(object), 0);
        if (collection != 0) {
            count = fn_80157E1C(collection);
            for (i = 0; i < count; i++) {
                fn_802020B4(fn_80201814(fn_80157E24(collection, i)), enabled);
            }
        }

        if (enabled != 0) {
            if (fn_80201B5C(object) == 0x15) {
                return;
            }
            object->flags |= 8;
        } else {
            object->flags = object->flags & ~8;
        }
    }
}
