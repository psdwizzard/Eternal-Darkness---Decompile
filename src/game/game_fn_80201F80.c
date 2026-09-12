typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Object80201F80 Object80201F80;

struct Object80201F80 {
    u8 padding[0x24];
    void* value;
};

extern u32 fn_80201CCC(void* value);
extern u32 fn_80201E50(void* value, u32 flags);

int fn_80201F80(Object80201F80* object, int operation, u32 mask)
{
    int result = 0;

    if (object != 0 && object->value != 0) {
        u32 flags = fn_80201CCC(object->value);

        switch (operation) {
        case 0:
            flags &= ~mask;
            fn_80201E50(object->value, flags);
            result = 1;
            break;
        case 1:
            flags |= mask;
            fn_80201E50(object->value, flags);
            result = 1;
            break;
        case 2:
            if ((flags & mask) == mask) {
                flags &= ~mask;
            } else {
                flags |= mask;
            }
            fn_80201E50(object->value, flags);
            result = 1;
            break;
        }
    }
    return result;
}
