typedef struct Descriptor {
    unsigned char pad[0x90];
    void* create;
    void* destroy;
    void* update;
    void* unknown;
    void* attach;
    void* set_value;
    unsigned char pad2[0x14];
    unsigned char enabled;
} Descriptor;

typedef struct InstanceList {
    unsigned char count;
    unsigned char pad[0x87];
    void* instances[16];
} InstanceList;

extern void fn_801489B4(Descriptor* descriptor, InstanceList* list);
extern void fn_80148D08(void* object, void* other);
extern void fn_80184818(unsigned char* descriptor);

void fn_80148A34(Descriptor* descriptor, InstanceList* list)
{
    fn_801489B4(descriptor, list);
    descriptor->update = fn_80148D08;
    descriptor->destroy = fn_80184818;
    descriptor->enabled |= 8;
    list->count = 1;
}
