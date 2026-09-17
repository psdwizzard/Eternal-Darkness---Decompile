typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct ObjectState {
    Vec3 origin;
    u8 pad0C[0x3C];
    Vec3 position;
    u8 pad54[0x34];
} ObjectState;

typedef struct Globals {
    ObjectState first[12];
    ObjectState second[12];
    ObjectState third;
} Globals;

typedef float Matrix34[3][4];

extern Globals lbl_8063C6B8;
extern const u32 lbl_8023B814[3];
extern const float lbl_806514C4;

extern void fn_801795A4(Vec3*, Vec3*, Vec3*);
extern void fn_80211380(Matrix34, Vec3*, float);
extern void fn_80211710(Matrix34, Vec3*, Vec3*);

void fn_801FA66C(int index, int save, float amount)
{
    Vec3 difference;
    Vec3 axis;
    Matrix34 transform;
    Globals* data = &lbl_8063C6B8;
    int offset = index * sizeof(ObjectState);
    ObjectState* target = data->second;
    target = (ObjectState*)((u8*)target + offset);

    *(u32*)&axis.x = lbl_8023B814[0];
    *(u32*)&axis.y = lbl_8023B814[1];
    *(u32*)&axis.z = lbl_8023B814[2];

    fn_801795A4((Vec3*)((u8*)data->first + offset), &target->origin, &difference);
    fn_80211380(transform, &difference, lbl_806514C4 * amount);
    fn_80211710(transform, &axis, &target->position);

    if (save != 0) {
        ObjectState* saved = &data->third;
        saved->position = target->position;
    }
}
