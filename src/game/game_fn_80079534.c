typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct ObjState {
    char pad0[0x40];
    unsigned char unk40;
    unsigned char unk41;
    char pad42[0x45 - 0x42];
    unsigned char unk45;
} ObjState;

typedef struct ObjData {
    char pad0[0xC];
    ObjState *unkC;
} ObjData;

typedef struct Actor {
    char pad0[0x14E];
    short unk14E;
    char pad150[0x15C - 0x150];
    short unk15C;
} Actor;

extern void *fn_80201B3C(void);
extern unsigned int fn_8011FAEC(void *);
extern ObjData *fn_80201B8C(void *);
extern void fn_800CC4DC(void *);
extern int fn_80079008(void *, void *);
extern unsigned char fn_80204508(void *, void *);
extern void *fn_8012AB2C(void *);
extern void fn_80201E78(Vec3 *, void *);
extern void fn_8013F3C0(void *, Vec3 *, Vec3 *, float);
extern unsigned int fn_8013FBE4(void *, void *, void *, int, int);
extern void *fn_801A717C(void);
extern void *fn_80201B44(void);
extern void fn_801A74A0(void *, void *);
extern void fn_801A74A8(void *, void *);
extern void fn_801A7538(void *, int);
extern void fn_801A7518(void *, int);
extern void fn_801A7470(void *, int);
extern void fn_801A764C(void *, Vec3 *);
extern void fn_8020104C(int, void *, void *, void *, float);
extern void fn_8011FA8C(void *, int, int);
extern unsigned int fn_8013017C(void *);
extern int fn_801305D4(void *);
extern void fn_801301B0(void *, int, int);

extern float lbl_8064E910;
extern float lbl_8064E928;
extern float lbl_8064E92C;

void fn_80079534(void *obj, void *arg1, void *model, Actor *actor, Vec3 *pos)
{
    Vec3 from;
    Vec3 target;
    char hit[0x18];
    char seg[0x48];
    ObjState *state;
    void *player;
    unsigned int flags;
    void *coll;
    void *sound;
    void *self;
    float offset;
    float radius;

    player = fn_80201B3C();
    flags = fn_8011FAEC(model);
    state = fn_80201B8C(obj)->unkC;
    fn_800CC4DC(obj);

    state->unk40 = state->unk40 > 1 ? state->unk40 - 1 : 0;
    actor->unk14E = actor->unk14E >= 1 ? actor->unk14E - 1 : 0;
    state->unk45 = state->unk45 >= 1 ? state->unk45 - 1 : 0;

    if (actor->unk14E <= 0 && player != 0 && fn_80079008(obj, model) != 0 &&
        fn_80204508(obj, player) != 0) {
        coll = fn_8012AB2C(model);
        fn_80201E78(&target, player);
        from = target;
        offset = lbl_8064E928;
        radius = lbl_8064E92C;
        pos->z += offset;
        from.z += offset;
        fn_8013F3C0(seg, pos, &from, radius);
        if (fn_8013FBE4(coll, seg, hit, 0, 8) == 0) {
            sound = fn_801A717C();
            self = fn_80201B44();
            fn_801A74A0(sound, arg1);
            fn_801A74A8(sound, self);
            fn_801A7538(sound, 2);
            fn_801A7518(sound, 1);
            fn_801A7470(sound, -1);
            fn_801A764C(sound, pos);
            fn_8020104C(0x3A, arg1, self, sound, lbl_8064E910);
        }
        pos->z -= lbl_8064E928;
        actor->unk14E = 90;
    }

    if (flags & 0x10) {
        fn_8011FA8C(model, 0x10, 0);
        if (++actor->unk15C > 120) {
            state->unk41 = 3;
            actor->unk15C = 0;
        }
    } else if (actor->unk15C != 0) {
        actor->unk15C = 0 > actor->unk15C - 1 ? 0 : actor->unk15C - 1;
    }

    if ((fn_8013017C(model) & 0x40) && fn_801305D4(model) == 0) {
        fn_801301B0(model, 0x40, 0);
    }
}
