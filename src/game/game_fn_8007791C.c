typedef struct Vec3f {
    float x, y, z;
} Vec3f;

typedef struct OwnerInfo {
    char pad0[0x152];
    short unk152;
    short unk154;
    short unk156;
} OwnerInfo;

typedef struct ObjExtra {
    char pad0[0x1BE];
    unsigned char unk1BE;
} ObjExtra;

typedef struct ObjData {
    char pad0[0x44];
    ObjExtra *unk44;
    char pad48[0x8C - 0x48];
    OwnerInfo *unk8C;
    char pad90[0x9F - 0x90];
    unsigned char unk9F;
} ObjData;

typedef struct SpawnParams {
    Vec3f pos;
    float facing;
    int unk10;
    int unk14;
    char pad18[0x24 - 0x18];
    int unk24;
    int unk28;
    int unk2C;
} SpawnParams;

extern int fn_801A717C(void);
extern int fn_80201B44(void);
extern int fn_80201BC8(int);
extern int fn_80201B54(int);
extern void fn_8011F114(Vec3f *, int);
extern int fn_80201B94(int);
extern ObjData *fn_80201B8C(int);
extern int fn_80067728(unsigned char);
extern void fn_801AC9F4(int, int, Vec3f *, int);
extern void fn_801A74A0(int, int);
extern void fn_801A74A8(int, int);
extern void fn_801A7538(int, int);
extern void fn_801A7518(int, int);
extern unsigned long long fn_8020123C(int, int, int, int);
extern void fn_801A7228(int);
extern void fn_8011FA8C(int, int, int);
extern void fn_80077F90(int);
extern int fn_80066D04(int, int);
extern void fn_800685A4(int, int);
extern void fn_8012C478(int, int, int);
extern float fn_8012B750(int);
extern void fn_80043F44(SpawnParams *);
extern int fn_80034708(SpawnParams *);
extern void fn_801261F4(int);
extern void fn_8012B7A0(int, float);
extern void fn_80201D54(int, int);
extern void fn_800CCA44(int);
extern void fn_802015A4(int);
extern int fn_80201C48(int);
extern int fn_80201814(int);
extern void fn_800359A0(int, int);
extern void fn_801E8328(int, int);

void fn_8007791C(int obj)
{
    SpawnParams params;
    Vec3f pos;
    float facing;
    int enabled;
    int sound;
    int model;
    int id;
    int self;
    int other;
    int newObj;
    int newModel;
    OwnerInfo *owner;
    ObjData *data;
    int target;

    sound = fn_801A717C();
    self = fn_80201B44();
    model = fn_80201BC8(obj);
    id = fn_80201B54(obj);
    fn_8011F114(&pos, model);
    other = fn_80201B94(obj);
    data = fn_80201B8C(obj);
    owner = data->unk8C;
    enabled = fn_80067728(data->unk9F);

    fn_801AC9F4(0x1A3, 100, &pos, 2);
    fn_801AC9F4(0x11, 100, &pos, 2);
    fn_801AC9F4(0x273, 100, &pos, 2);

    fn_801A74A0(sound, id);
    fn_801A74A8(sound, self);
    fn_801A7538(sound, 2);
    fn_801A7518(sound, 30);
    fn_8020123C(0x27, id, self, sound);
    fn_801A7228(sound);

    fn_8011FA8C(model, 0xC0, 0);
    fn_80077F90(model);

    if (fn_80066D04(obj, 1)) {
        if (fn_80066D04(obj, 0) && enabled) {
            fn_800685A4(model, 0);
        } else {
            fn_8012C478(model, 0, 0);
        }
        if (fn_80066D04(obj, 2) && enabled) {
            fn_800685A4(model, 2);
        } else {
            fn_8012C478(model, 2, 0);
        }
        if (fn_80066D04(obj, 3) && enabled) {
            fn_800685A4(model, 3);
        } else {
            fn_8012C478(model, 3, 0);
        }
        if (enabled) {
            fn_800685A4(model, 1);
        }
    }
    fn_8012C478(model, 0xF, 0);

    facing = fn_8012B750(model);
    fn_80043F44(&params);
    params.unk10 = owner->unk152;
    params.unk14 = owner->unk154;
    params.facing = facing;
    params.unk28 = 7;
    params.pos = pos;
    params.unk24 = owner->unk156;
    newObj = fn_80034708(&params);

    newModel = fn_80201BC8(newObj);
    if (newModel) {
        fn_801261F4(newModel);
        fn_8012B7A0(newModel, params.facing);
    }
    fn_80201D54(newObj, params.unk2C);
    fn_800CCA44(newObj);
    fn_80201B8C(newObj);
    data = fn_80201B8C(newObj);
    data->unk44->unk1BE = 1;
    fn_802015A4(newObj);
    target = fn_80201814(fn_80201C48(other));
    fn_800359A0(newObj, target);
    fn_801E8328(1, newObj);
}
