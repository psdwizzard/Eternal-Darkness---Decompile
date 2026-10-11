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
    s16 count;
    Vec3 axis;
    float angle;
    u16 subtype1, kind1, param1;
    u16 subtype2, kind2, param2;
    u16 subtype3, kind3, param3;
    s16 param1C, param20;
    u16 param24;
    u16 active;
    u16 flags;
} SpawnEntry;

typedef struct SpawnList {
    u8 pad[0x20];
    SpawnEntry *entries;
} SpawnList;

typedef struct ObjectData {
    u8 pad[0x90];
    int resource;
} ObjectData;

extern SpawnList *lbl_8064D0BC;
extern int *lbl_8064C5A8;
extern void fn_80043F44(SpawnRequest *request);
extern int fn_80034708(void *request);
extern void *fn_80201B8C(void *object);
extern void *fn_80201BC8(void *object);
extern void *fn_80072354(int index);
extern void fn_80045918(void *object, const Vec3 *axis, float angle);
extern void fn_80201D54(void *object, void *value);
extern void fn_802015A4(void *object);
extern int fn_800CCA44(void *object);
extern int fn_801E8328(unsigned int mode, unsigned int object);

void fn_80044D50(int index, int mask)
{
    SpawnRequest request;
    Vec3 position;
    SpawnEntry *entry;
    void *object;

    entry = &lbl_8064D0BC->entries[index];
    position.x = entry->x;
    position.y = entry->y;
    position.z = entry->z;
    fn_80043F44(&request);
    switch (*lbl_8064C5A8) {
    case 1:
        request.kind = entry->kind1;
        request.subtype = entry->subtype1;
        request.count = entry->param1;
        break;
    case 2:
        request.kind = entry->kind2;
        request.subtype = entry->subtype2;
        request.count = entry->param2;
        break;
    case 3:
        request.kind = entry->kind3;
        request.subtype = entry->subtype3;
        request.count = entry->param3;
        break;
    }
    /* The retail code repeats this test before filling the request. */
    if (request.kind != 0 || request.kind != 0) {
        request.owner = entry->count;
        request.position = position;
        request.param1C = entry->param1C;
        request.param20 = entry->param20;
        request.flags = entry->flags;
        request.param24 = entry->param24;
        request.active = entry->active;
        if (mask & request.active) {
            object = (void *)fn_80034708(&request);
            fn_80072354(((ObjectData *)fn_80201B8C(object))->resource);
            fn_80045918(fn_80201BC8(object), &entry->axis, entry->angle);
            fn_80201D54(object, (void *)(int)entry->count);
            fn_802015A4(object);
            fn_800CCA44(object);
            fn_801E8328(1, (unsigned int)object);
        }
    }
}
