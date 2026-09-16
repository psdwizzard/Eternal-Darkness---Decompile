typedef unsigned char u8;

typedef struct Coord3 {
    short x, y, z;
} Coord3;

typedef struct InstanceList {
    u8 count;
    u8 pad[0x87];
    void* entries[1];
} InstanceList;

typedef struct Entry {
    u8 data[0x174];
} Entry;

extern volatile unsigned int lbl_8065053C;
extern volatile unsigned short lbl_80650540;

extern void fn_8014F320(void*, u8, short);
extern void fn_8018199C(void*, Coord3*, Coord3*, void*);
extern void fn_80185108(void*);
extern void fn_801851A0(void*, Coord3*);

void fn_8014EB38(u8* object, int index)
{
    void** current;
    int count;
    u8* entry;
    int i;
    InstanceList* list;
    Coord3 position;
    Coord3 config;
    unsigned int configXY;

    entry = (u8*)((Entry*)object + index) + 0xEBC;
    configXY = lbl_8065053C;
    *(unsigned int*)&config = configXY;
    config.z = lbl_80650540;

    if (*(void**)(entry + 0x94) != 0) {
        fn_8014F320(entry, object[0], *(short*)(object + 0x2A));

        position.x = (short)*(float*)(object + 0x40);
        position.y = (short)*(float*)(object + 0x44);
        position.z = (short)*(float*)(object + 0x48);
        fn_8018199C(*(void**)(entry + 0x94), &position, &config, entry);

        list = *(InstanceList**)(entry + 0x170);
        count = list->count;
        current = list->entries;
        for (i = 0; i < count; current++, i++) {
            fn_80185108(*current);
            fn_801851A0(*current, &position);
        }
    }
}
