extern void* memset(void*, int, unsigned long);

extern void* fn_801848AC(void*, void*, void*);
extern void fn_80184740(void*);
extern void fn_80148B98(void*, void*, void*);
extern void fn_80148C0C(void*, void*);
extern void fn_80185000(unsigned char*, unsigned short);

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

void fn_801489B4(Descriptor* descriptor, InstanceList* list)
{
    descriptor->create = fn_801848AC;
    descriptor->destroy = fn_80184740;
    descriptor->update = fn_80148C0C;
    descriptor->unknown = 0;
    descriptor->attach = fn_80148B98;
    descriptor->set_value = fn_80185000;
    descriptor->enabled = 1;
    list->count = 16;
    memset(list->instances, 0, sizeof(list->instances));
}
