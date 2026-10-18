typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct EventData {
    u8 pad[0x88];
    u32 value;
} EventData;

typedef struct SpawnState {
    u8 pad[0x94];
    int object_id;
    int field_98;
} SpawnState;

typedef struct EventSlot {
    u8 pad[0x12];
    u8 active;
    u8 kind;
    u8 rest[0x18];
} EventSlot;

typedef struct Owner {
    u8 pad_00[0x38];
    int object_id;
    union {
        struct {
            u8 pad_3c[0x88];
            SpawnState *spawn;
        } fields;
        struct {
            u8 pad_3c[0x1C];
            EventSlot slots[3];
        } event_data;
    } data;
} Owner;

typedef struct SoundInfo {
    u8 pad[0x44];
    int id;
} SoundInfo;

typedef struct Related {
    u8 pad[0x8C];
    SoundInfo *sound;
} Related;

typedef struct SearchResult {
    u8 pad[8];
    Vec3 position;
    u8 rest[0x14];
} SearchResult;

/* Entry layouts from fn_8006ED3C and fn_80201814. */
typedef struct Entry {
    int id;
} Entry;

typedef struct Entry80201814 {
    struct Entry80201814 *prev;
    struct Entry80201814 *next;
    int unk8;
    int unkC;
    int id;
} Entry80201814;

extern const Vec3 lbl_802396B0;
extern const Vec3 lbl_802396BC;
extern int lbl_802FC5BC[];
extern const float lbl_8064EDA8;

extern void *fn_801A717C(void);
extern void fn_801A7228(void *);
extern void fn_801A7470(EventData *, u32);
extern Entry *fn_8006ED3C(Owner *, int, int *);
extern Entry80201814 *fn_80201814(int);
extern void *fn_80201BC8(void *);
extern void *fn_80205868(void *, int, void *, u32);
extern void fn_8012C198(u8 *);
extern int fn_80201A84(void *);
extern void *fn_80201B8C(u8 *);
extern void fn_8020104C(int, int, int, int, float);
extern u64 fn_8020123C(int, int, int, int);
extern void fn_8012B690(void *, const void *, void *);
extern int fn_8011F6A4(void *, int, int, int, void *, int);
extern void fn_8014D478(void *, Vec3 *, float *, int, int, int *, int);

/* Scheduled by fn_8009D638 through fn_8006DEF8 with the owner as context. */
int fn_8009D760(void *context)
{
    int index;
    SpawnState *state;
    void *object;
    Owner *owner = context;
    EventData *event;
    int spawned;
    Entry80201814 *entry;
    Vec3 origin;
    Vec3 position;
    Vec3 direction;
    SearchResult search;

    event = fn_801A717C();
    state = owner->data.fields.spawn;
    spawned = 0;
    fn_8006ED3C(owner, 0x11, &index);
    if ((entry = fn_80201814(owner->object_id)) != 0) {
        void *created;
        origin = lbl_802396B0;
        object = fn_80201BC8(entry);
        created = fn_80205868(object, 0, &origin, 0x24000);
        if (created != 0) {
            void *new_object = fn_80201BC8(created);
            fn_8012C198((u8 *)new_object);
            state->object_id = fn_80201A84(new_object);
            spawned = 1;
            state->field_98 = 0;
        } else {
            Related *related = fn_80201B8C((u8 *)entry);
            state->object_id = 0;
            state->field_98 = 0;
            fn_8020104C(0x51, 0, related->sound->id, 0, lbl_8064EDA8);
        }
        owner->data.event_data.slots[index].active = 1;
        owner->data.event_data.slots[index].kind = 3;
        fn_801A7470(event, 0xB);
        fn_8020123C(0x35, 0, owner->object_id, (int)event);
        direction = lbl_802396BC;
        fn_8012B690(object, &direction, &position);
        if (fn_8011F6A4(object, 0, 0, -1, &search, 1) != -1) {
            position = search.position;
        }
        fn_8014D478(object, &position, &origin.x, 4, 4, lbl_802FC5BC + 6, 1);
    }
    fn_801A7228(event);
    return spawned;
}
