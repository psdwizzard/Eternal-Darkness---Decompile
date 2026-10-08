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
    u8 pad54[0x18];
    void (*callback)(struct MotionState*);
    struct MotionState* source;
    struct MotionState* next;
    u8 pad78[0x10];
} MotionState;

typedef struct Entry {
    u8 data[0x14];
} Entry;

extern Vec3 lbl_8023B7E4;
extern int lbl_8064C3A0;
extern int lbl_8064C3A4;
extern int lbl_8064D798;
extern int lbl_8064D79C;
extern int lbl_8064D7BC;
extern float lbl_80651464;
extern float lbl_8065148C;
extern float lbl_80651490;
extern float lbl_80651494;
extern float lbl_80651498;
extern float lbl_8065149C;

extern void fn_801F7034(MotionState*, int);
extern int fn_801FA410(int);
extern void fn_801F76D8(int, int, int, float);
extern void fn_801F7804(MotionState*);
extern void fn_801F7AD4(MotionState*);

static MotionState first[12] = {0};
static MotionState second[12] = {0};
static MotionState current_first = {0};
static MotionState current_second = {0};
static Entry entries[5] = {0};

void fn_801F7C78(void)
{
    Vec3 initial = lbl_8023B7E4;
    float zero;
    int i;

    lbl_8064C3A0 = 2;
    lbl_8064D798 = 0;
    lbl_8064C3A4 = 2;
    lbl_8064D79C = 0;
    fn_801F7034(&current_first, 1);
    fn_801F7034(&current_second, 1);
    current_second.position.x = lbl_8065148C;
    current_first.next = &current_second;
    fn_801FA410(2);
    fn_801F76D8(0, 0, 0, lbl_80651464);
    current_first.callback = fn_801F7804;
    current_second.callback = fn_801F7804;
    zero = lbl_8065148C;
    lbl_8064D7BC = 0;

    for (i = 0; i < 12; i++) {
        fn_801F7034(&second[i], 1);
        fn_801F7034(&first[i], 1);
        first[i].position.x = zero;
        second[i].next = &first[i];
        first[i].vector = initial;
        second[i].vector = initial;
    }

    if (current_first.source != 0) {
        current_first.vector = current_first.source->vector;
    }

    second[0].callback = fn_801F7AD4;
    second[1].callback = fn_801F7804;
    second[8].field_34 = lbl_80651498;
    second[8].position.x = lbl_80651490;
    second[8].position.y = lbl_80651494;
    second[8].position.z = lbl_8065148C;
    first[8].position = second[8].position;
    first[8].position.x = lbl_8065149C;
}
