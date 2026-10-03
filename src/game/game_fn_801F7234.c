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

extern const float lbl_80651478;

extern void fn_801FA354(MotionState*);
extern void fn_801F692C(Vec3);
extern void fn_801F6998(Vec3);
extern void fn_801F69E0(float);
extern void fn_801F6950(Vec3);
extern void fn_801F69BC(Vec3);
extern void fn_80211AAC(Vec3*, Vec3*);

static MotionState first[12] = {0};
static MotionState second[12] = {0};
static MotionState current_first = {0};
static MotionState current_second = {0};

void fn_801F7234(int flags)
{
    MotionState* a;
    MotionState* b;
    int enabled = flags & 1;
    int i;
    Vec3 delta;

    if (enabled) {
        if (current_first.callback != 0) {
            current_first.callback(&current_first);
        }
        if (current_second.callback != 0) {
            current_second.callback(&current_second);
        }
    }
    if (flags & 2) {
        a = first;
        b = second;
        for (i = 0; i < 12; i++, a++, b++) {
            if (a->callback != 0) {
                a->callback(a);
            }
            if (b->callback != 0) {
                b->callback(b);
            }
        }
    }
    if (enabled) {
        if (current_first.field_40 != 0) {
            fn_801FA354(&current_first);
        }
        if (current_second.field_40 != 0) {
            fn_801FA354(&current_second);
        }
    }
    if (current_first.position.x == current_second.position.x &&
        current_first.position.y == current_second.position.y &&
        current_first.position.z == current_second.position.z) {
        current_second.position.x += lbl_80651478;
    }
    fn_801F692C(current_first.position);
    fn_801F6998(current_second.position);
    fn_801F69E0(current_first.field_34);
    fn_801F6950(current_first.vector);
    delta.x = current_second.position.x - current_first.position.x;
    delta.y = current_second.position.y - current_first.position.y;
    delta.z = current_second.position.z - current_first.position.z;
    fn_80211AAC(&delta, &delta);
    fn_801F69BC(delta);
}
