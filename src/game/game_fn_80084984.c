/* Constrain a menu-chain link's movement to its boundary plane. */
typedef unsigned char u8;
typedef signed char s8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;
typedef struct Vec3 { f32 x, y, z; } Vec3;
typedef struct ShortCoord3 { s16 x, y, z; } ShortCoord3;
typedef f32 Mtx[3][4];

typedef struct ChainObject {
    f32 angles[2];
    Vec3 position;
    Vec3 pivot;
    u8 pad20[0xC];
    u16 soundAngles[2];
    u8 moving[2];
    u8 active;
} ChainObject;

typedef struct ChainLink {
    ChainObject *object;
    ShortCoord3 vertices[4];
    Vec3 origin;
    Vec3 axes[2];
    u8 pad40[0x78];
} ChainLink;

typedef struct BoundaryEntry {
    u16 type;
    u16 pad02;
    const void *data;
} BoundaryEntry;

typedef struct Boundary {
    u16 type;
    u8 flags;
    u8 pad03;
    Vec3 center;
    f32 radius;
    Vec3 normal;
    f32 distance;
    s8 axis;
    u8 pad25[3];
    u16 count;
    u8 pad2A[2];
    const u16 *indices;
    s8 innerCount;
    u8 pad31[3];
    const BoundaryEntry *inner;
} Boundary;

typedef struct MenuConstants {
    u8 pad[0x294];
    Vec3 eye;
    Vec3 direction;
    Vec3 up;
} MenuConstants;
typedef struct ChainState { u8 pad[0x42C]; u8 selected; } ChainState;
typedef union QuadIndices { u32 words[2]; u16 indices[4]; } QuadIndices;

extern MenuConstants lbl_80239208;
extern ChainState lbl_8031CD84;
extern const f32 lbl_8064EA08, lbl_8064EA14, lbl_8064EA18;
extern const f32 lbl_8064EAFC, lbl_8064EB00;
extern const u32 lbl_8064EAF4, lbl_8064EAF8;

extern void fn_801F68D4(Vec3 *);
extern void C_MTXLookAt(Mtx, Vec3 *, Vec3 *, Vec3 *);
extern u32 PSMTXInverse(const Mtx, Mtx);
extern void PSMTXMultVec(Mtx, const Vec3 *, Vec3 *);
extern void PSVECScale(const Vec3 *, Vec3 *, f32);
extern void PSVECAdd(const Vec3 *, const Vec3 *, Vec3 *);
extern void PSVECSubtract(const Vec3 *, const Vec3 *, Vec3 *);
extern void PSVECNormalize(const Vec3 *, Vec3 *);
extern f32 PSVECDotProduct(const Vec3 *, const Vec3 *);
extern void PSVECCrossProduct(const Vec3 *, const Vec3 *, Vec3 *);
extern void C_VECHalfAngle(const Vec3 *, const Vec3 *, Vec3 *);
extern u32 fn_80178F14(int, int, int, int, int, int);
extern void fn_8017960C(ShortCoord3 *, ShortCoord3 *, Vec3 *);
extern void fn_80179DB0(f32 *, s16 *);
extern int fn_80179EB8(f32 *);
extern int fn_8013DF4C(const Vec3 *, const Vec3 *, const Vec3 *, f32, Vec3 *);
extern int fn_8013D560(const void *, const Boundary *, const void *);
extern f32 fn_8013C068(const Vec3 *, const Boundary *, const s16 *, Vec3 *);

Vec3 fn_80084984(int side, ChainLink *link, ChainLink *previous, f32 amount)
{
    Mtx view;
    Mtx inverse;
    Boundary boundary;
    Vec3 eye;
    Vec3 direction;
    Vec3 movement;
    Vec3 pivot;
    Vec3 result;
    Vec3 initial;
    Vec3 up;
    Vec3 edge1;
    Vec3 edge2;
    Vec3 vertex;
    Vec3 intersection;
    Vec3 closest;
    QuadIndices indices;
    MenuConstants *constants = &lbl_80239208;

    eye = constants->eye;
    direction = constants->direction;
    up = constants->up;
    fn_801F68D4(&initial);
    if (lbl_8064EA14 == amount) {
        return link->object->position;
    }

    /* Transform the selected control axis into a movement direction. */
    pivot = link->object->pivot;
    if (link->axes[side].z >= lbl_8064EAFC) {
        up.z = lbl_8064EA14;
        up.y = lbl_8064EA18;
    }
    C_MTXLookAt(view, &eye, &up, &link->axes[side]);
    PSMTXInverse(view, inverse);
    if (side == 0) {
        direction.x = lbl_8064EA08;
    } else {
        direction.y = lbl_8064EA08;
    }
    PSMTXMultVec(view, &direction, &direction);
    PSVECScale(&direction, &direction, amount);
    PSVECAdd(&direction, &pivot, &movement);
    PSVECNormalize(&movement, &movement);

    /* Construct the four-vertex boundary, including its sphere and plane. */
    indices.words[0] = lbl_8064EAF4;
    indices.words[1] = lbl_8064EAF8;
    boundary.type = 0;
    boundary.flags = 0;
    boundary.center.x =
        (link->vertices[indices.indices[0]].x +
         link->vertices[indices.indices[1]].x +
         link->vertices[indices.indices[2]].x +
         link->vertices[indices.indices[3]].x) >> 2;
    boundary.center.y =
        (link->vertices[indices.indices[0]].y +
         link->vertices[indices.indices[1]].y +
         link->vertices[indices.indices[2]].y +
         link->vertices[indices.indices[3]].y) >> 2;
    boundary.center.z =
        (link->vertices[indices.indices[0]].z +
         link->vertices[indices.indices[1]].z +
         link->vertices[indices.indices[2]].z +
         link->vertices[indices.indices[3]].z) >> 2;
    boundary.radius = lbl_8064EB00 * (f32)fn_80178F14(
        (int)boundary.center.x, (int)boundary.center.y, (int)boundary.center.z,
        link->vertices[indices.indices[0]].x, link->vertices[indices.indices[0]].y,
        link->vertices[indices.indices[0]].z);

    fn_8017960C(&link->vertices[1], &link->vertices[0], &edge1);
    PSVECNormalize(&edge1, &edge1);
    fn_8017960C(&link->vertices[2], &link->vertices[0], &edge2);
    PSVECNormalize(&edge2, &edge2);
    PSVECCrossProduct(&edge1, &edge2, &boundary.normal);
    PSVECNormalize(&boundary.normal, &boundary.normal);
    fn_80179DB0(&vertex.x, &link->vertices[0].x);
    boundary.distance = -PSVECDotProduct(&boundary.normal, &vertex);
    boundary.axis = fn_80179EB8(&boundary.normal.x);
    boundary.count = 4;
    boundary.inner = 0;
    boundary.innerCount = 0;
    boundary.indices = indices.indices;
    /* Clamp an intersection outside the face to its nearest edge. */
    if (fn_8013DF4C(&link->origin, &movement, &boundary.normal,
                    boundary.distance, &intersection) != 0 &&
        fn_8013D560(&intersection, &boundary, link->vertices) == 0) {
        if ((int)lbl_8031CD84.selected == 2 && side == 0) {
            movement = pivot;
        } else {
            fn_8013C068(&intersection, &boundary, &link->vertices[0].x, &closest);
            PSVECSubtract(&closest, &link->origin, &movement);
            PSVECNormalize(&movement, &movement);
        }
    }
    movement.x = -movement.x;
    movement.y = -movement.y;
    movement.z = -movement.z;
    C_VECHalfAngle(&previous->object->pivot, &movement, &result);
    return result;
}
