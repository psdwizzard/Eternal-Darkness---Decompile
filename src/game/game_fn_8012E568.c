typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Copy16 {
    u32 word[4];
} Copy16;

typedef struct ResourceObject {
    u8 pad_00[0xE];
    u16 joint_index;
} ResourceObject;

typedef struct ResourceEntry {
    u32 unknown_00;
    ResourceObject* object;
} ResourceEntry;

typedef struct Object {
    Vec3 position;
    Vec3 optional_position;
    u8 pad_018[0x14];
    Copy16 properties;
    void* spawn_context;
    u8 pad_040[0x114];
    Vec3* points;
    Copy16* records;
    u8 pad_15C[0xE4];
    ResourceEntry** resources;
    u32 copied_244;
    u8 pad_248[8];
    u32 copied_250;
    u32 flags;
    u8 pad_258[4];
    void* link_25C;
    u8 pad_260[4];
    Vec3 relative_position;
    u8 pad_270[4];
    float radius;
    u8 pad_278[0x1C];
    u32 copied_294;
    u8 pad_298[0x10];
    u8* states;
} Object;


extern void* fn_8012E504(void*, float, float, float);
extern int fn_801261F4(void*);
extern void fn_8011FB44(void *, void *);
extern void fn_80127F90(void*, int, Vec3*);
extern void fn_80211A6C(const Vec3*, const Vec3*, Vec3*);
extern float fn_8011F788(void*, float);
extern void fn_8011F7A0(void*, const Vec3*);


void* fn_8012E568(Object* source, int resource_index, void* data)
{
    const Vec3* optional_position = data;
    Object* created;
    ResourceObject* resource_object;
    Vec3 relative;
    Vec3 final_position;
    float radius;
    int i;

    created = fn_8012E504(source->spawn_context, source->position.x,
                          source->position.y, source->position.z);
    resource_object = source->resources[resource_index]->object;
    fn_801261F4(created);

    created->copied_294 = source->copied_294;
    fn_8011FB44(source, 0);
    created->properties = source->properties;
    created->copied_250 = source->copied_250;
    created->copied_244 = source->copied_244;
    if (optional_position != 0) {
        created->optional_position = *optional_position;
    }

    for (i = 0; i < 137; i++) {
        created->points[i] = source->points[i];
        created->records[i] = source->records[i];
        created->states[i] = source->states[i];
    }

    fn_80127F90(source, resource_object->joint_index, &relative);
    fn_80211A6C(&relative, &source->position, &relative);

    radius = 24.0f;
    switch (resource_index) {
    case 0:
        relative.z += radius;
        break;
    case 2:
        radius = 20.0f;
        break;
    case 3:
        radius = 20.0f;
        break;
    case 1:
        relative.z += 20.0f;
        radius = 20.0f;
        break;
    }

    fn_8011F788(created, radius);
    final_position = relative;
    fn_8011F7A0(created, &final_position);
    created->flags |= 0x400;
    return created;
}
