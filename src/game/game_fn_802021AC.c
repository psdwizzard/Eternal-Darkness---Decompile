typedef unsigned int u32;

typedef struct Object802021AC Object802021AC;

struct Object802021AC {
    unsigned char padding[0x24];
    void* data;
};

extern u32 fn_80201CCC(void* data);

u32 fn_802021AC(Object802021AC* object)
{
    if (object != 0 && object->data != 0) {
        return fn_80201CCC(object->data) & 0x800000;
    }
    return 0;
}
