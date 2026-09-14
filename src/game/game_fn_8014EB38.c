typedef unsigned char u8;

typedef struct Coord3 {
    short x, y, z;
} Coord3;

typedef struct InstanceList {
    u8 count;
    u8 pad[0x87];
    void* entries[1];
} InstanceList;

extern unsigned int lbl_8065053C;
extern unsigned short lbl_80650540;

extern void fn_8014F320(void*, u8, short);
extern void fn_8018199C(void*, Coord3*, Coord3*, void*);
extern void fn_80185108(void*);
extern void fn_801851A0(void*, Coord3*);

/* NonMatching: behavior-complete honest C. Retail overwrites r4 for the entry
 * multiply, schedules the two SDA21 loads in the opposite order, and allocates
 * the loop index/current pointer to r29/r31 rather than r31/r29. */
void fn_8014EB38(u8* object, int index)
{
    int i;
    int count;
    u8* entry;
    void** current;
    InstanceList* list;
    Coord3 position;
    Coord3 config;

    entry = object + 0xEBC + index * 0x174;
    *(unsigned int*)&config = lbl_8065053C;
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
        for (i = 0; i < count; i++, current++) {
            fn_80185108(*current);
            fn_801851A0(*current, &position);
        }
    }
}
