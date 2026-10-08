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
    u8 pad38[0x10];
    Vec3 vector;
    u8 pad54[0x1C];
    struct MotionState* source;
    struct MotionState* next;
    u8 pad78[0x10];
} MotionState;

typedef struct Entry {
    u8 data[0x14];
} Entry;

extern Vec3 lbl_8023B7D8;
extern float lbl_80651460;
extern float lbl_80651464;
extern float lbl_8064D7A0;

extern void fn_801F7034(MotionState*, int);
extern void fn_801F8994(MotionState*, const Vec3*, float);
extern void fn_801F8620(void);
extern int fn_801FA410(int);

static MotionState first[12] = {0};
static MotionState second[12] = {0};
static MotionState current_first = {0};
static MotionState current_second = {0};
static Entry entries[5] = {0};

MotionState* fn_801F7AF8(void)
{
    Vec3 values = lbl_8023B7D8;

    fn_801F7034(&second[10], 1);
    fn_801F7034(&first[10], 1);
    second[10].next = &first[10];
    first[10].vector = values;
    second[10].vector = values;
    fn_801F8994(&second[10], &current_first.position, current_first.field_34);
    fn_801F8994(&first[10], &current_second.position, current_first.field_34);
    fn_801F8620();
    fn_801FA410(10);
    lbl_8064D7A0 = lbl_80651464;
    second[10].value = lbl_80651460;
    first[10].value = lbl_80651460;
    return &second[10];
}
