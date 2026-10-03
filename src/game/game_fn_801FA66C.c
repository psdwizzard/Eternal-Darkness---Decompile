typedef unsigned char u8;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct MotionState {
    Vec3 position;
    u8 pad0C[0x24];
    float value;
    float field_34;
    u8 pad38[8];
    int field_40;
    u8 pad44[4];
    Vec3 vector;
    u8 pad54[0x18];
    void (*callback)(struct MotionState*);
    struct MotionState* source;
    u8 pad74[0x14];
} MotionState;

typedef float Matrix34[3][4];

extern const Vec3 lbl_8023B814;
extern const float lbl_806514C4;

extern void fn_801795A4(Vec3* from, Vec3* to, Vec3* difference);
extern void fn_80211380(Matrix34 transform, Vec3* axis, float angle);
extern void fn_80211710(Matrix34 transform, Vec3* in, Vec3* out);

static MotionState first[12] = {0};
static MotionState second[12] = {0};
static MotionState current_first = {0};

void fn_801FA66C(int index, int save, float amount)
{
    Vec3 difference;
    Vec3 axis = lbl_8023B814;
    Matrix34 transform;
    MotionState* target = &second[index];

    fn_801795A4(&first[index].position, &target->position, &difference);
    fn_80211380(transform, &difference, lbl_806514C4 * amount);
    fn_80211710(transform, &axis, &target->vector);

    if (save != 0) {
        current_first.vector = target->vector;
    }
}
