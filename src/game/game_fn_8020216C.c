typedef unsigned int u32;

typedef struct Object8020216C Object8020216C;

struct Object8020216C {
    unsigned char padding[0x24];
    void* data;
};

extern u32 fn_80201CCC(void* data);

u32 fn_8020216C(Object8020216C* object)
{
    if (object != 0 && object->data != 0) {
        return fn_80201CCC(object->data) & 0xFF800;
    }
    return -1;
}
