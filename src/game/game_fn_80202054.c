typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Object80202054 Object80202054;

struct Object80202054 {
    unsigned char padding[0x24];
    void* value;
};

extern u32 fn_80201CCC(void* value);
extern void fn_80201E50(void* value, u32 flags);

void fn_80202054(Object80202054* object, u16 enabled)
{
    if (object != 0 && object->value != 0) {
        u32 flags = fn_80201CCC(object->value);
        u32 updated = flags & ~4;

        if (enabled != 0) {
            updated = flags | 4;
        }
        fn_80201E50(object->value, updated);
    }
}
