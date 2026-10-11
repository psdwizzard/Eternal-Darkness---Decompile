typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct SpawnRequest {
    Vec3 position;
    float facing;
    int kind;
    int subtype;
    int param18;
    int param1C;
    int param20;
    int param24;
    int count;
    int owner;
    int enabled;
    s16 requestFlags;
    s8 activeMask;
} SpawnRequest;
typedef struct SpawnRecord {
    s16 x, y, z;
    s16 kind;
    int flags;
    Vec3 axis;
    float angle;
    char pad1C[4];
    u16 mode1B, mode1A, mode1D, mode1C;
    u16 mode2B, mode2A, mode2D, mode2C;
    u16 mode3B, mode3A, mode3D, mode3C;
    u16 extra;
    u16 pad3A;
} SpawnRecord;
typedef struct SpawnList {
    char pad[0x24];
    int count;
    SpawnRecord *records;
} SpawnList;
typedef struct ListNode {
    struct ListNode *previous;
    struct ListNode *next;
    unsigned int value;
} ListNode;
typedef struct ObjectData {
    char pad[0x90];
    int model;
} ObjectData;
extern SpawnList *lbl_8064D0BC;
extern int *lbl_8064C5A8;
extern void *fn_80204A8C(void);
extern void fn_80043F44(SpawnRequest *);
extern int fn_80034708(void *);
extern int fn_80204CE4(void *, ListNode *);
extern void *fn_80201B8C(u8 *);
extern void *fn_80072354(int);
extern void *fn_80201BC8(void *);
extern void fn_80045918(void *, const Vec3 *, float);
extern void *fn_80201B94(void *);
extern void fn_80201DE0(void *, void *);
extern void fn_80201D54(void *, void *);
extern void fn_802015A4(void *);
extern int fn_801E8328(unsigned int, unsigned int);

void fn_80044F84(int mask)
{
    int offset;
    int i;
    Vec3 position;
    SpawnRequest request;
    void *object;
    ListNode *group;
    SpawnRecord *record;

    i = 0;
    offset = 0;
    for (; i < lbl_8064D0BC->count; i++) {
        group = (ListNode *)fn_80204A8C();
        record = (SpawnRecord *)((char *)lbl_8064D0BC->records + offset);
        position.x = (float)record->x;
        position.y = (float)record->y;
        position.z = (float)record->z;
        fn_80043F44(&request);
        request.owner = record->kind;
        request.activeMask = (s8)record->flags;
        switch (*lbl_8064C5A8) {
        case 1:
            request.kind = record->mode1A;
            request.subtype = record->mode1B;
            request.param18 = record->mode1C;
            request.count = record->mode1D;
            break;
        case 2:
            request.kind = record->mode2A;
            request.subtype = record->mode2B;
            request.param18 = record->mode2C;
            request.count = record->mode2D;
            break;
        case 3:
            request.kind = record->mode3A;
            request.subtype = record->mode3B;
            request.param18 = record->mode3C;
            request.count = record->mode3D;
            break;
        }
        if (request.kind != 0 || request.kind != 0) {
            request.position = position;
            if (mask & request.activeMask) {
                object = (void *)fn_80034708(&request);
                fn_80204CE4(object, group);
                fn_80072354(((ObjectData *)fn_80201B8C((u8 *)object))->model);
                fn_80045918(fn_80201BC8(object), &record->axis, record->angle);
                fn_80201DE0(fn_80201B94(object), (void *)(unsigned int)record->extra);
                fn_80201D54(object, (void *)(int)record->kind);
                fn_802015A4(object);
                fn_801E8328(1, (unsigned int)object);
            }
        }
        offset += 0x3C;
    }
}
