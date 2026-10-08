typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Point3s { s16 x, y, z; } Point3s;
typedef struct Quad { Point3s point[4]; } Quad;

typedef struct PoolSlot {
    u16 value;
    u8 flags;
    u8 count;
    u16 index;
    u8 pad6[2];
    void* owner;
    void* first;
    void* second;
} PoolSlot;

typedef struct PlaneEntry {
    s16 kind;
    u8 flags;
    u8 pad3;
    Vec3 center;
    float radius;
    Vec3 normal;
    float distance;
    u8 axis;
    u8 pad25[3];
    s16 point_count;
    u8 pad2A[2];
    void* callback;
    u8 state;
    u8 pad31[3];
    void* link;
} PlaneEntry;

typedef struct WorkEntry { PlaneEntry plane[2]; } WorkEntry;

static PoolSlot slots[12] = {0};
static WorkEntry work_entries[84] = {0};
static Quad quad_entries[84] = {0};
extern u8 lbl_8064D038;
extern char lbl_8064BA08;
extern const float lbl_80650430;
extern const float lbl_80650434;
extern int fn_801429A8(void);
extern float fn_800ED720(float);
extern void fn_8017960C(Point3s*, Point3s*, Vec3*);
extern void fn_80211B64(Vec3*, Vec3*, Vec3*);
extern float fn_80211B08(Vec3*);
extern void fn_80211A90(Vec3*, Vec3*, float);
extern float fn_80211B44(Vec3*, Vec3*);
extern int fn_80179EB8(float*);

PoolSlot* fn_80142A70(u8 count, Point3s* ring, s16 z_offset, u32 value,
                     void* owner, void* first, void* second, int flagged)
{
    Point3s* next;
    int slot_index = fn_801429A8();
    Quad* quads;
    int n;
    int j;
    PoolSlot* slot = &slots[slot_index];
    WorkEntry* work;
    int i;

    slot->flags |= 1;
    slot->value = value;
    slot->owner = owner;
    slot->count = count;
    slot->first = first;
    slot->second = second;
    slot->index = (u16)slot_index;
    if (flagged) {
        slot->flags |= 2;
    }

    n = count;
    quads = &quad_entries[slot_index * 7];
    for (i = 0; i < n; i++) {
        Quad* quad = &quads[i];
        Point3s* current = &ring[i];
        next = &ring[(s16)((i + 1) % slot->count)];
        quad->point[0] = *current;
        quad->point[1].x = current->x;
        quad->point[1].y = current->y;
        quad->point[1].z = z_offset + current->z;
        quad->point[2].x = next->x;
        quad->point[2].y = next->y;
        quad->point[2].z = z_offset + next->z;
        quad->point[3] = *next;
    }

    work = &work_entries[slot_index * 7];
    for (j = 0; j < n; quads++, j++) {
        Quad* quad = quads;
        PlaneEntry* plane = &work[j].plane[0];
        PlaneEntry* back = &work[j].plane[1];
        Vec3 edge0;
        Vec3 edge1;
        Vec3 point;

        plane->kind = 20;
        plane->flags = 0;
        plane->center.x = (quad->point[0].x + quad->point[1].x +
                           quad->point[2].x + quad->point[3].x) >> 2;
        plane->center.y = (quad->point[0].y + quad->point[1].y +
                           quad->point[2].y + quad->point[3].y) >> 2;
        plane->center.z = (quad->point[0].z + quad->point[1].z +
                           quad->point[2].z + quad->point[3].z) >> 2;
        plane->radius = fn_800ED720(
            (plane->center.x - quad->point[0].x) *
                (plane->center.x - quad->point[0].x) +
            (plane->center.y - quad->point[0].y) *
                (plane->center.y - quad->point[0].y) +
            (plane->center.z - quad->point[0].z) *
                (plane->center.z - quad->point[0].z));
        plane->point_count = 4;
        plane->callback = &lbl_8064BA08;
        plane->state = 0;
        plane->link = 0;
        *back = *plane;

        fn_8017960C(&quad->point[1], &quad->point[0], &edge0);
        fn_8017960C(&quad->point[2], &quad->point[0], &edge1);
        fn_80211B64(&edge0, &edge1, &plane->normal);
        fn_80211A90(&plane->normal, &plane->normal,
                    lbl_80650430 / fn_80211B08(&plane->normal));
        fn_80211A90(&plane->normal, &back->normal, lbl_80650434);
        point.x = quad->point[0].x;
        point.y = quad->point[0].y;
        point.z = quad->point[0].z;
        plane->distance = -fn_80211B44(&plane->normal, &point);
        back->distance = -fn_80211B44(&back->normal, &point);
        plane->axis = fn_80179EB8((float*)&plane->normal);
        back->axis = plane->axis;
    }

    lbl_8064D038++;
    return slot;
}
