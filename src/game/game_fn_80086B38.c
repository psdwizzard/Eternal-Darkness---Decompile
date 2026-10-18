/* Set up the menu object chain when entering screen 0x53/0x59. */

typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;
typedef struct Vec3 { f32 x, y, z; } Vec3;
typedef struct Vec3s { s16 x, y, z; } Vec3s;

typedef struct ChainLink {
    void *object;
    Vec3s coords[4];
    Vec3 position;
    u8 pad28[0x6C];
    u32 handles[2];
    u8 pad9C[0x1C];
} ChainLink;

typedef struct ModelSlot {
    u32 handle;
    u32 pad4;
} ModelSlot;

typedef struct ChainState {
    u8 pad0[0x6C];
    ChainLink links[5];
    u8 pad404[0x28];
    s8 selected;
    u8 pad42D[0x1B];
    ModelSlot slots[4];
    u8 pad468[0x1C8];
    s8 current;
} ChainState;

typedef struct ChainView {
    u8 pad0[0x24];
    Vec3 delta;
    Vec3 axis;
    Vec3 start;
    u8 pad48[6];
    u8 startActive;
    u8 pad4F[9];
    Vec3 up;
    Vec3 pivot;
    Vec3 end;
    u8 pad7C[6];
    u8 endActive;
} ChainView;

typedef struct GameState {
    u8 pad0[8];
    int busy;
} GameState;

extern char lbl_80244870[];
extern GameState lbl_803003C8;
extern ChainView lbl_8031CBA0;
extern ChainState lbl_8031CD84;
extern int lbl_8064CDC4;
extern int lbl_8064D18C;
extern const f32 lbl_8064EA14;

extern void fn_80084264(ChainLink *);
extern void fn_80084404(void *, int, f32);
extern void fn_8012C478(u32, int, int);
extern Vec3s *fn_80158ABC(int, int, void *);
extern void *fn_8015C28C(int);
extern int fn_8015C4A4(u32, int);
extern u32 fn_801E741C(const char *);
extern int fn_80201814(int);
extern int fn_802019EC(int, int);
extern u32 fn_80201BC8(int);
extern void PSVECSubtract(const Vec3 *, const Vec3 *, Vec3 *);
extern void PSVECNormalize(const Vec3 *, Vec3 *);
extern void C_VECReflect(const Vec3 *, const Vec3 *, Vec3 *);

void fn_80086B38(int screen, int reset)
{
    int ids[5];
    Vec3s *coords;
    int slot;
    int i;
    char *strings = lbl_80244870;

    if (reset != 0) {
        lbl_8064CDC4 = 0;
    }
    switch (screen) {
    case 0x53:
        for (slot = 0; slot < 4; slot++) {
            lbl_8031CD84.slots[slot].handle = fn_80201BC8(fn_80201814(fn_802019EC(slot + 0x898, 0x53)));
            if (lbl_8031CD84.slots[slot].handle != 0) {
                fn_8012C478(lbl_8031CD84.slots[slot].handle, 0xF, slot == lbl_8031CD84.current);
            }
        }
        break;
    case 0x59:
        if (lbl_803003C8.busy != 0) {
            break;
        }
        fn_8015C28C(2);
        ids[0] = fn_8015C4A4(fn_801E741C(strings + 0x724), 2);
        ids[1] = fn_8015C4A4(fn_801E741C(strings + 0x730), 2);
        ids[2] = fn_8015C4A4(fn_801E741C(strings + 0x73C), 2);
        ids[3] = fn_8015C4A4(fn_801E741C(strings + 0x748), 2);
        ids[4] = fn_8015C4A4(fn_801E741C(strings + 0x754), 2);
        for (i = 0; i < 5; i++) {
            coords = fn_80158ABC(ids[i], 2, 0);
            lbl_8031CD84.links[i].position.x = coords->x;
            lbl_8031CD84.links[i].position.y = coords->y;
            lbl_8031CD84.links[i].position.z = coords->z;
        }

        ids[0] = fn_8015C4A4(fn_801E741C(strings + 0x760), 2);
        ids[1] = fn_8015C4A4(fn_801E741C(strings + 0x770), 2);
        ids[2] = fn_8015C4A4(fn_801E741C(strings + 0x780), 2);
        ids[3] = fn_8015C4A4(fn_801E741C(strings + 0x790), 2);
        for (i = 0; i < 4; i++) {
            lbl_8031CD84.links[1].coords[i] = *fn_80158ABC(ids[i], 2, 0);
        }

        ids[0] = fn_8015C4A4(fn_801E741C(strings + 0x7A0), 2);
        ids[1] = fn_8015C4A4(fn_801E741C(strings + 0x7B0), 2);
        ids[2] = fn_8015C4A4(fn_801E741C(strings + 0x7C0), 2);
        ids[3] = fn_8015C4A4(fn_801E741C(strings + 0x7D0), 2);
        for (i = 0; i < 4; i++) {
            lbl_8031CD84.links[2].coords[i] = *fn_80158ABC(ids[i], 2, 0);
        }

        ids[0] = fn_8015C4A4(fn_801E741C(strings + 0x7E0), 2);
        ids[1] = fn_8015C4A4(fn_801E741C(strings + 0x7F0), 2);
        ids[2] = fn_8015C4A4(fn_801E741C(strings + 0x800), 2);
        ids[3] = fn_8015C4A4(fn_801E741C(strings + 0x810), 2);
        for (i = 0; i < 4; i++) {
            lbl_8031CD84.links[3].coords[i] = *fn_80158ABC(ids[i], 2, 0);
        }

        lbl_8031CBA0.delta.x = lbl_8031CD84.links[1].position.x - lbl_8031CD84.links[0].position.x;
        lbl_8031CBA0.delta.y = lbl_8031CD84.links[1].position.y - lbl_8031CD84.links[0].position.y;
        lbl_8031CBA0.delta.z = lbl_8031CD84.links[1].position.z - lbl_8031CD84.links[0].position.z;
        lbl_8031CBA0.start = lbl_8031CD84.links[0].position;
        lbl_8031CBA0.end = lbl_8031CD84.links[1].position;
        PSVECSubtract(&lbl_8031CBA0.delta, &lbl_8031CBA0.up, &lbl_8031CBA0.axis);
        PSVECNormalize(&lbl_8031CBA0.axis, &lbl_8031CBA0.axis);

        for (i = 0; i < 5; i++) {
            lbl_8031CD84.links[i].handles[0] = 0;
            lbl_8031CD84.links[i].handles[1] = 0;
        }
        lbl_8031CD84.links[1].handles[0] = fn_80201BC8(fn_80201814(fn_802019EC(0x8D9, lbl_8064D18C)));
        lbl_8031CD84.links[2].handles[1] = fn_80201BC8(fn_80201814(fn_802019EC(0x8DA, lbl_8064D18C)));
        lbl_8031CD84.links[3].handles[1] = fn_80201BC8(fn_80201814(fn_802019EC(0x8DB, lbl_8064D18C)));
        fn_80084404(&lbl_8031CD84.links[1], 0, lbl_8064EA14);
        fn_80084404(&lbl_8031CD84.links[2], 0, lbl_8064EA14);
        fn_80084404(&lbl_8031CD84.links[3], 0, lbl_8064EA14);
        lbl_8031CBA0.startActive = 1;
        lbl_8031CBA0.endActive = 1;
        C_VECReflect(&lbl_8031CBA0.axis, &lbl_8031CBA0.up, &lbl_8031CBA0.pivot);
        lbl_8031CD84.selected = 1;
        fn_80084264(&lbl_8031CD84.links[2]);
        lbl_8031CD84.selected = -1;
        break;
    }
}
