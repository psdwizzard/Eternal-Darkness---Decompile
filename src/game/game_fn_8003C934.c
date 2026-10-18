typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef int s32;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Object80201C48 Object80201C48;
typedef struct Entry80201814 Entry80201814;
typedef struct Entry { char data[0xE0]; } Entry;
typedef struct ActorData {
    u8 pad[0x90];
    s32 index;
    s32 kind;
} ActorData;
extern unsigned int rand(void);
extern void *fn_80201B8C(u8 *object);
extern void *fn_80201B94(u8 *object);
extern void *fn_80201BC8(void *object);
extern s32 fn_800360B0(void *object, u16 *flags);
extern void *fn_80201C48(Object80201C48 *object);
extern Entry *fn_80072354(int index);
extern void fn_8011F114(Vec3 *destination, Vec3 *source);
extern Entry80201814 *fn_80201814(int id);
extern u8 fn_80204578(void *object, const Vec3 *position);
extern s32 fn_80066D04(s32 context, s32 index);

s32 fn_8003C934(void *object, s32 enabled)
{
    Vec3 position;
    u16 flags;
    ActorData *data;
    Object80201C48 *owner;
    Vec3 *transform;
    s32 roll;
    s32 eligible;
    void *targetId;
    Entry *entry;
    Entry80201814 *target;
    s8 first, second, third, limit;

    roll = (s32)rand() % 100;
    data = fn_80201B8C(object);
    owner = fn_80201B94(object);
    transform = fn_80201BC8(object);
    fn_800360B0(object, &flags);
    eligible = (flags & 0x80) ? 0 : enabled;
    eligible = data->kind == 4 ? 0 : eligible;
    targetId = fn_80201C48(owner);
    entry = fn_80072354(data->index);
    fn_8011F114(&position, transform);
    target = fn_80201814((s32)targetId);
    first = entry->data[0x2C];
    second = entry->data[0x34];
    third = entry->data[0x3C];
    if (target && !fn_80204578(target, &position) && eligible && fn_80066D04((s32)object, 0)) {
        second = 0;
        first = 0;
        third = 100;
    }
    if (!fn_80066D04((s32)object, 3)) {
        eligible = 0;
        flags |= 1;
    }
    if (!fn_80066D04((s32)object, 2)) {
        eligible = 0;
        flags |= 2;
    }
    if (!fn_80066D04((s32)object, 0)) {
        eligible = 0;
    }
    second += first;
    third += second;
    limit = 100;
    if (enabled) limit = second;
    if (flags & 1) roll = limit;
    if (flags & 2) {
        if (flags & 1) {
            if (eligible) roll = third;
            else roll = third + 1;
        } else roll = first;
    }
    if (roll <= first) return 4;
    if (roll <= limit) return 5;
    if (roll <= third && eligible) return 6;
    return -1;
}
