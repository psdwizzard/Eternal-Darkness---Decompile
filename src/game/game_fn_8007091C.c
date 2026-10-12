typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct SpawnRequest {
    Vec3 position;
    float scale;
    u32 kind;
    u32 subtype;
    u32 param18;
    u32 param1C;
    u32 param20;
    u32 param24;
    u32 count;
    void *owner;
    u32 enabled;
    u16 flags;
    u8 active;
    u8 pad37;
} SpawnRequest;

extern void fn_80043F44(SpawnRequest *);
extern void *fn_80034708(SpawnRequest *);
extern void *fn_80201BC8(void *);
extern void *fn_8011F950(void *);
extern void fn_80201D54(void *, void *);
extern void fn_802015A4(void *);
extern int fn_801E8328(u32, u32);
extern void fn_80036E8C(void *);
extern void fn_80201750(void *);

void *fn_8007091C(u32 kind, u32 subtype, u32 count,
                  void *owner, const Vec3 *position, float scale)
{
    SpawnRequest request;
    void *object;
    void *model;

    fn_80043F44(&request);
    request.kind = kind;
    request.subtype = subtype;
    request.owner = owner;
    request.count = count;
    request.scale = scale;
    request.position = *position;

    switch (kind) {
    case 0x79: request.param18 = 0x57; break;
    case 0x78: request.param18 = 0x56; break;
    case 0x71: request.param18 = 0x9C; break;
    case 0x75: request.param18 = 0xAB; break;
    case 0x72: request.param18 = 0x55; break;
    case 0x77: request.param18 = 0x87; break;
    case 0x6E: request.param18 = 0x58; break;
    }

    object = fn_80034708(&request);
    if (object != 0) {
        model = fn_80201BC8(object);
        if (model != 0 && fn_8011F950(model) != 0) {
            fn_80201D54(object, request.owner);
            fn_802015A4(object);
            fn_801E8328(1, (u32)object);
        } else {
            fn_80036E8C(object);
            fn_80201750(object);
            return 0;
        }
    }
    return object;
}
