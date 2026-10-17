typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct SpawnRequest {
    u8 position[0x10];
    u32 kind;
    u32 subtype;
    u32 param18;
    u32 param1C;
    u32 param20;
    u32 param24;
    u32 count;
    u32 owner;
    u32 enabled;
    u16 flags;
    u8 active;
    u8 pad37;
} SpawnRequest;

typedef struct SpawnInfo {
    Vec3 position;
    float scale;
    int kind;
    int field14;
    int pad18;
    int field1c;
    int field20;
    int field24;
    int field28;
} SpawnInfo;

extern void *fn_80201BC8(void *);
extern void fn_8011F114(Vec3 *, Vec3 *);
extern int fn_80201B54(int *);
extern int fn_80035628(void *);
extern int fn_800CAC5C(int, int, int *, int *, int *);
extern void fn_80043F44(SpawnRequest *);
extern float fn_8012B750(void *);
extern int fn_800CA554(void *, u32);
extern void *fn_801DD200(int, SpawnInfo *, int, int, int, u16, int);
extern void fn_801DE5D4(void *, int);

void *fn_800CA3A0(void *object, int type, Vec3 *position, register int argOption)
{
    union {
        SpawnRequest request;
        SpawnInfo info;
    } spawn;
    Vec3 sourcePosition;
    int kind;
    int subtype;
    int value;
    int mode;
    register int usePosition;
    register unsigned int option;
    int id;
    void *result;
    Vec3 *source;

    option = argOption;
    result = 0;
    usePosition = 0;
    source = fn_80201BC8(object);
    fn_8011F114(&sourcePosition, source);
    id = fn_80201B54(object);
    mode = fn_80035628(object);
    if (fn_800CAC5C(type, mode, &kind, &subtype, &value)) {
        fn_80043F44(&spawn.request);
        spawn.info.kind = kind;
        spawn.info.field14 = subtype;
        spawn.info.scale = fn_8012B750(source);
        spawn.info.field28 = 40;
        if (position != 0) {
            usePosition = 1;
            spawn.info.position = *position;
        }
        result = fn_801DD200(id, &spawn.info, (int)fn_800CA554,
                            ((u32)id << 8) | 0x78, usePosition, 200, option);
        fn_801DE5D4(result, value);
    }
    return result;
}
