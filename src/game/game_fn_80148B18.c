typedef unsigned char u8;

typedef struct Descriptor {
    u8 pad00[0x90];
    void* create;
    unsigned int createData;
    void* destroy;
    unsigned int destroyData;
    void* query;
    unsigned int queryData;
    u8 padA8[0x14];
    u8 enabled;
} Descriptor;

extern void* memset(void*, int, unsigned int);
extern void fn_801847AC(u8*);
extern void* fn_801849E0(void*, void*, u8*);
extern void fn_80148FE8();
extern void fn_801493D4(void*, short*, void*, void*, u8*);

void fn_80148B18(Descriptor* descriptor, u8* list)
{
    descriptor->create = fn_801849E0;
    descriptor->createData = 0;
    descriptor->destroy = fn_80148FE8;
    descriptor->destroyData = 0;
    descriptor->query = fn_801493D4;
    descriptor->queryData = 0;
    descriptor->enabled = 1;
    list[0] = 1;
    memset(list + 0x88, 0, 0x40);
    fn_801847AC((u8*)descriptor);
}
