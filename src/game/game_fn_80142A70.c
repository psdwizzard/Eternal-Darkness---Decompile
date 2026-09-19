typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;

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

extern PoolSlot lbl_805B1310[];
extern WorkEntry lbl_805B1400[];
extern Quad lbl_805B38C0[];
extern u8 lbl_8064D038;
extern char lbl_8064BA08[];
extern float lbl_80650430;
extern float lbl_80650434;
extern int fn_801429A8(void);
extern float fn_800ED720(float);
extern void fn_8017960C(Point3s*, Point3s*, Vec3*);
extern void fn_80211B64(Vec3*, Vec3*, Vec3*);
extern float fn_80211B08(Vec3*);
extern void fn_80211A90(Vec3*, Vec3*, float);
extern float fn_80211B44(Vec3*, Vec3*);
extern int fn_80179EB8(float*);

PoolSlot* fn_80142A70(u8 count, Point3s* ring, s16 z_offset, u16 value,
                     void* owner, void* first, void* second, int flagged)
{
    int slot_index = fn_801429A8();
    PoolSlot* slot = &lbl_805B1310[slot_index];
    Quad* quads = &lbl_805B38C0[slot_index * 7];
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

    for (i = 0; i < count; i++) {
        Point3s* current = &ring[i];
        Point3s* next = &ring[(i + 1) % count];
        quads[i].point[0] = *current;
        quads[i].point[1] = *current;
        quads[i].point[1].z += z_offset;
        quads[i].point[2] = *next;
        quads[i].point[2].z += z_offset;
        quads[i].point[3] = *next;
    }

    work = &lbl_805B1400[slot_index * 7];
    for (i = 0; i < count; i++) {
        Quad* quad = &quads[i];
        PlaneEntry* plane = &work[i].plane[0];
        PlaneEntry* back = &work[i].plane[1];
        Vec3 edge0;
        Vec3 edge1;
        Vec3 point;
        float dx;
        float dy;
        float dz;

        plane->kind = 20;
        plane->flags = 0;
        plane->center.x = (quad->point[0].x + quad->point[1].x +
                           quad->point[2].x + quad->point[3].x) >> 2;
        plane->center.y = (quad->point[0].y + quad->point[1].y +
                           quad->point[2].y + quad->point[3].y) >> 2;
        plane->center.z = (quad->point[0].z + quad->point[1].z +
                           quad->point[2].z + quad->point[3].z) >> 2;
        dx = plane->center.x - quad->point[0].x;
        dy = plane->center.y - quad->point[0].y;
        dz = plane->center.z - quad->point[0].z;
        plane->radius = fn_800ED720(dx * dx + dy * dy + dz * dz);
        plane->point_count = 4;
        plane->callback = lbl_8064BA08;
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
