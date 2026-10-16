typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Record {
    char pad[0x32];
    short value;
} Record;

typedef struct Object {
    void *primary;
    Record *secondary;
} Object;

typedef struct Int3 {
    int x, y, z;
} Int3;

typedef struct Slot {
    int depth;
    Vec3 *model;
    char pad8[0x1C];
    Object *actor;
    void *owner;
} Slot;

extern int lbl_8064CCB4;
extern double lbl_8064FE78;
extern short fn_8015784C(Object *);
extern void fn_801F69F0(const Int3 *, Vec3 *, int);
extern void fn_8011F0E8(Vec3 *, Vec3 *);

int fn_8010B5E4(Slot *slot, int x, int y, float scale)
{
    Vec3 world;
    Int3 pos;
    register int target;
    register int screenX;
    register int screenY;
    register int base;

    fn_8015784C(slot->actor);
    /* ASM: lwz and mr load the base while preserving the callee's
     * sign-extended short result. C adds a redundant extsh; keeping the
     * load here also preserves the retail instruction order. */
    asm {
        lwz base, lbl_8064CCB4
        mr target, r3
    }
    screenX = x + 320;
    screenY = y + 165;
    slot->depth = target - (int)(scale * (float)(target - base));
    pos.x = screenX;
    pos.y = screenY;
    pos.z = slot->depth;
    fn_801F69F0(&pos, &world, 0);
    fn_8011F0E8(slot->model, &world);
    if (slot->depth >= target) {
        slot->depth = target;
        pos.x = screenX;
        pos.y = screenY;
        pos.z = slot->depth;
        fn_801F69F0(&pos, &world, 0);
        fn_8011F0E8(slot->model, &world);
        return 1;
    }
    return 0;
}
