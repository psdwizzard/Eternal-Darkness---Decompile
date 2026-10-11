typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct SpawnRequest {
    Vec3 position;
    int positionPad;
    int kind;
    int subtype;
    int param18;
    int param1C;
    int param20;
    int param24;
    int count;
    int owner;
    int enabled;
    u16 flags;
    s8 active;
    u8 pad37;
} SpawnRequest;

typedef struct SpawnEntry {
    s16 x, y, z;
    s16 owner;
    unsigned int active;
    Vec3 axis;
    float angle;
    u16 subtype, param18, kind;
    s16 param1C;
    u16 pad24, count, value;
    u16 pad2A;
} SpawnEntry;

typedef struct SpawnList {
    u8 pad[0x14];
    int count;
    SpawnEntry *entries;
} SpawnList;

typedef struct ObjectData {
    u8 pad[0x90];
    int resource;
} ObjectData;

typedef struct ListNode80204CE4 ListNode80204CE4;
typedef struct Object80201DE0 Object80201DE0;
typedef struct Object80201D54 Object80201D54;
typedef struct Object802015A4 Object802015A4;
typedef struct Entry Entry;

extern SpawnList *lbl_8064D0BC;
extern void fn_80043F44(SpawnRequest *request);
extern int fn_80034708(void *request);
extern void *fn_80204A8C(void);
extern int fn_80204CE4(void *object, ListNode80204CE4 *node);
extern void *fn_80201B8C(unsigned char *object);
extern void *fn_80201BC8(void *object);
extern void *fn_80201B94(unsigned char *object);
extern void fn_80201DE0(Object80201DE0 *object, void *value);
extern Entry *fn_80072354(int index);
extern void fn_80045918(void *object, const Vec3 *axis, float angle);
extern void fn_80201D54(Object80201D54 *object, void *value);
extern void fn_802015A4(Object802015A4 *object);
extern int fn_800CCA44(void *object);
extern int fn_801E8328(unsigned int mode, unsigned int object);

void fn_80044BAC(int mask)
{
    SpawnRequest request;
    Vec3 position;
    int i;
    ListNode80204CE4 *node;
    void *object;
    SpawnEntry *entry;

    for (i = 0; i < lbl_8064D0BC->count; i++) {
        node = fn_80204A8C();
        entry = &lbl_8064D0BC->entries[i];
        position.x = entry->x;
        position.y = entry->y;
        position.z = entry->z;
        fn_80043F44(&request);
        request.owner = entry->owner;
        request.kind = entry->kind;
        request.subtype = entry->subtype;
        request.param18 = entry->param18;
        request.position = position;
        request.count = entry->count;
        request.param1C = entry->param1C;
        request.active = entry->active;
        if (mask & request.active) {
            object = (void *)fn_80034708(&request);
            fn_80204CE4(object, node);
            fn_80072354(((ObjectData *)fn_80201B8C(object))->resource);
            fn_80045918(fn_80201BC8(object), &entry->axis, entry->angle);
            fn_80201DE0(fn_80201B94(object), (void *)(unsigned int)entry->value);
            fn_80201D54(object, (void *)(int)entry->owner);
            fn_802015A4(object);
            fn_800CCA44(object);
            fn_801E8328(1, (unsigned int)object);
        }
    }
}
