typedef unsigned char u8;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct SpawnState {
    u8 pad[0x94];
    int object_id;
    int field_98;
} SpawnState;

typedef struct Owner {
    u8 pad_00[0x38];
    int object_id;
    u8 pad_3c[0x88];
    SpawnState *spawn;
} Owner;

typedef struct EventEntry {
    int id;
    int field_04;
    short count;
} EventEntry;

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

extern int lbl_802FC5BC[];
extern const float lbl_8064EDAC;
extern const float lbl_8064EDB0;
extern const float lbl_8064EDB4;
extern const float lbl_8064EDB8;

extern EventEntry *fn_8006ED3C(Owner *, int, int *);
extern void *fn_80201814(int);
extern void *fn_80201BC8(void *);
extern void *fn_80201B8C(u8 *);
extern void fn_8020104C(int, int, int, int, float);
extern void fn_8012B690(void *, const void *, void *);
extern int fn_8011F6A4(void *, int, int, int, void *, int);
extern void fn_8014D478(void *, Vec3 *, float *, int, int, int *, int);

int fn_8009D940(Owner *owner)
{
    int index;
    SpawnState *state;
    EventEntry *event;
    int spawned;
    void *entry;
    void *object;
    /* Local offset transformed into the spawned object's space. */
    Vec3 origin = { 0.0f, 0.0f, 250.0f };
    Vec3 position;
    Vec3 rotation;
    SearchResult search;

    state = owner->spawn;
    event = fn_8006ED3C(owner, 0x11, &index);
    spawned = 0;
    entry = fn_80201814(state->object_id);
    event->count++;
    if (entry != 0) {
        object = fn_80201BC8(entry);
        fn_8012B690(object, &origin, &position);
        if (fn_8011F6A4(object, 0, 0, -1, &search, 1) != -1) {
            position = search.position;
            position.z += lbl_8064EDAC;
        }
        rotation.x = lbl_8064EDB0;
        rotation.y = lbl_8064EDB0;
        rotation.z = lbl_8064EDB4;
        fn_8014D478(object, &position, (float *)&rotation, 4, 4, lbl_802FC5BC + 6, 5);
        spawned = 1;
    }
    if (event->count >= 10) {
        Related *related = fn_80201B8C(fn_80201814(owner->object_id));
        state->object_id = 0;
        state->field_98 = 0;
        fn_8020104C(0x51, 0, related->sound->id, 0, lbl_8064EDB8);
    }
    return spawned;
}

