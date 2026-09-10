typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct ObjectState {
    u8 pad00[0x48];
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
extern const volatile u32 lbl_8023B814[3];
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
    int offset = index * 0x88;
    ObjectState* target = (ObjectState*)((u8*)data + 0x660 + offset);

    axis.x = ((const Vec3*)lbl_8023B814)->x;
    axis.y = ((const Vec3*)lbl_8023B814)->y;
    axis.z = ((const Vec3*)lbl_8023B814)->z;

    fn_801795A4((Vec3*)((u8*)data + offset), (Vec3*)target, &difference);
    fn_80211380(transform, &difference, lbl_806514C4 * amount);
    fn_80211710(transform, &axis, &target->position);

    if (save != 0) {
        ObjectState* saved = (ObjectState*)((u8*)data + 0xCC0);
        saved->position = target->position;
    }
}
