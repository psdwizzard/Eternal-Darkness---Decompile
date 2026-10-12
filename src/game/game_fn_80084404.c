/* Rotate one link of the menu object chain and propagate to the next links. */

typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;
typedef struct Vec3 { f32 x, y, z; } Vec3;
typedef f32 Mtx[3][4];
typedef struct Color4 { u32 v[4]; } Color4;

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
    u8 pad4[0x3C];
    Vec3 offset;
    u8 pad4C[0x18];
    u8 colorSources[2][0xC];
    u8 pad7C[4];
    f32 rotation[3];
    u8 pad8C[8];
    u32 handles[2];
    u8 pad9C[0x19];
    s8 axis;
    u8 padB6[2];
} ChainLink;

typedef struct ChainState {
    u8 pad0[0x6C];
    ChainLink links[5];
    u8 pad404[0x28];
    s8 selected;
} ChainState;

typedef struct GameState {
    u8 pad[0x11E];
    u8 flag11E;
} GameState;

extern GameState lbl_8031CBA0;
extern ChainState lbl_8031CD84;
extern u32 *lbl_8064C4E0;
extern const f32 lbl_8064EA0C, lbl_8064EA14, lbl_8064EA2C, lbl_8064EA80;
extern const f32 lbl_8064EA9C, lbl_8064EAF0;
/* Retail reloads the lower rotation bound on both clamp paths. */
extern const volatile f32 lbl_8064EAA0;

extern void fn_8007D744(int);
extern void fn_80084168(int, int);
extern void fn_80084264(ChainLink *);
extern Vec3 fn_80084984(int, ChainLink *, ChainLink *, f32);
extern void fn_8012CDF0(u32, int, Color4 *, int);
extern void fn_8017A244(void *, Color4 *, f32);
extern int fn_801A98F4(int, int);
extern void fn_801E7974(u32 *, u32);
extern int fn_801E79FC(u32 *, u32);
extern void fn_80210FDC(Mtx, Mtx, Mtx);
extern void fn_80211268(Mtx, char, f32);
extern void fn_80211710(Mtx, const Vec3 *, Vec3 *);
extern void fn_80211A6C(const Vec3 *, const Vec3 *, Vec3 *);
extern void fn_80211C78(const Vec3 *, const Vec3 *, Vec3 *);

static inline f32 maximum(f32 value, f32 lower)
{
    if (value > lower) {
        lower = value;
    }
    return lower;
}

static inline f32 absolute(f32 value)
{
    if (value < *(const volatile f32 *)&lbl_8064EA14) {
        value = -value;
    }
    return value;
}

static inline f32 clampRotation(f32 value)
{
    return (lbl_8064EA0C < maximum(value, lbl_8064EAA0)) ? lbl_8064EA0C : maximum(value, lbl_8064EAA0);
}

void fn_80084404(void *self, int side, f32 delta)
{
    Mtx rotation;
    Mtx rotX;
    Mtx rotY;
    Mtx rotZ;
    Mtx rotZY;
    Vec3 oldPosition;
    Vec3 moved;
    Color4 color;
    Vec3 newPosition;
    Color4 colorCopy;
    ChainLink *link;
    ChainLink *end;
    ChainLink *prev;
    ChainLink *next;
    int wasMoving;
    f32 angle;
    f32 value;
    int diff;
    int i;

    link = self;
    oldPosition = link->object->position;
    prev = link - 1;
    next = link + 1;
    if (link->axis >= 0 && lbl_8064EA14 != delta) {
        link->rotation[0] = lbl_8064EA14;
        link->rotation[1] = lbl_8064EA14;
        link->rotation[2] = lbl_8064EA14;
        link->rotation[link->axis] = delta / lbl_8064EA80;
        value = link->rotation[link->axis];
        link->rotation[link->axis] = clampRotation(value);
        fn_80211268(rotX, 'x', link->rotation[0]);
        fn_80211268(rotY, 'y', link->rotation[1]);
        fn_80211268(rotZ, 'z', link->rotation[2]);
        fn_80210FDC(rotZ, rotY, rotZY);
        fn_80210FDC(rotZY, rotX, rotation);
        fn_80211710(rotation, &link->offset, &link->offset);
        fn_80211710(rotation, &link->object->position, &link->object->position);
    } else if (link->handles[side] != 0 && link->object->active != 0) {
        newPosition = fn_80084984(side, link, prev, delta / lbl_8064EA80);
        link->object->position = newPosition;
    }

    if (prev->object->active == 0) {
        link->object->active = 0;
        if (next < &lbl_8031CD84.links[5]) {
            next->object->active = 0;
        }
    }
    if (next < &lbl_8031CD84.links[5]) {
        wasMoving = link->object->moving[side];
        if (prev->object->active != 0) {
            fn_80084264(link);
            fn_80211C78(&prev->object->pivot, &link->object->position, &link->object->pivot);
            fn_80084264(next);
        }
        if (&lbl_8031CD84.links[lbl_8031CD84.selected] == link && link->handles[side] != 0 &&
            lbl_8064EA14 != delta) {
            fn_80211A6C(&oldPosition, &link->object->position, &moved);
            moved.x = absolute(moved.x);
            moved.y = absolute(moved.y);
            moved.z = absolute(moved.z);
            if (link->object->active == 0 || moved.x > lbl_8064EAF0 || moved.y > lbl_8064EAF0 ||
                moved.z > lbl_8064EAF0) {
                link->object->angles[side] += delta / lbl_8064EA9C;
                angle = lbl_8064EA2C * link->object->angles[side];
                diff = link->object->soundAngles[side] - (u16)angle;
                if (diff > 2000 || diff < -2000) {
                    link->object->soundAngles[side] = angle;
                    fn_801A98F4(0x113, 100);
                }
                link->object->moving[side] = 0;
            } else if (wasMoving == 0) {
                fn_801A98F4(0x114, 100);
                link->object->moving[side] = 1;
            }
            for (i = 0; i < 2; i++) {
                if (link->handles[i] != 0) {
                    fn_8017A244(link->colorSources[i], &color, link->object->angles[i]);
                    colorCopy = color;
                    fn_8012CDF0(link->handles[i], 0xF, &colorCopy, 0);
                }
            }
        }
    }

    if (next < &lbl_8031CD84.links[5] && next->object->active != 0) {
        if (side == 0) {
            fn_80084404(next, 0, lbl_8064EA14);
        } else {
            fn_80084404(next, 1, lbl_8064EA14);
        }
    } else {
        for (link++; link < &lbl_8031CD84.links[5]; link++) {
            link->object->active = 0;
        }    }

    if (fn_801E79FC(lbl_8064C4E0, 0x13A) != 0 && fn_801E79FC(lbl_8064C4E0, 0x13B) != 0 &&
        lbl_8031CBA0.flag11E != 0) {
        fn_801E7974(lbl_8064C4E0, 0x101);
        fn_80084168(0, 0);
    }
    fn_8007D744(4);
}
