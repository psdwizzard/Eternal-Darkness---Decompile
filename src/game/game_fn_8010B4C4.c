/* Remaining difference: MWCC emits a local signed-integer conversion
 * bias instead of referencing the shared retail symbol lbl_8064FE78. */
typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Int3 {
    int x;
    int y;
    int z;
} Int3;

typedef struct Record {
    char pad[0x32];
    short value;
} Record;

typedef struct Object {
    void *primary;
    Record *secondary;
} Object;

typedef struct Slot {
    int depth;
    Vec3 *model;
    char pad8[0x1C];
    Object *actor;
    void *owner;
} Slot;

extern short fn_8015784C(Object *);
extern int fn_8010D414(void *);
extern void fn_801F69F0(const Int3 *, Vec3 *, int);
extern void fn_8011F0E8(Vec3 *, Vec3 *);
extern int lbl_8064CCB0;

int fn_8010B4C4(Slot *slot, int x, int y, float scale)
{
    Vec3 world;
    Int3 position;
    register int upper;
    short lower;

    fn_8015784C(slot->actor);
    /* ASM: mr uses the callee's sign-extended short directly; a C
     * assignment adds a redundant extsh. */
    asm { mr upper, r3 }
    lower = fn_8010D414(slot->actor);
    slot->depth = lower + (int)(scale * (float)(upper - lower));
    position.x = x + 320;
    position.y = y + 165;
    position.z = slot->depth;
    fn_801F69F0(&position, &world, 0);
    fn_8011F0E8(slot->model, &world);
    if (slot->depth <= lower) {
        slot->depth = lower;
        lbl_8064CCB0 = 0;
        position.x = 320;
        position.y = 165;
        position.z = slot->depth;
        fn_801F69F0(&position, &world, 0);
        fn_8011F0E8(slot->model, &world);
        return 1;
    }
    return 0;
}
