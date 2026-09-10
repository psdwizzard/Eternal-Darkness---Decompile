typedef unsigned char u8;

typedef struct Vector3 {
    int x;
    int y;
    int z;
} Vector3;

typedef struct MotionState {
    Vector3 position;
    u8 pad0C[0x28];
    float value34;
    u8 pad38[8];
    int active;
    u8 pad44[4];
    Vector3 direction;
    u8 pad54[0x1C];
    struct MotionState* source;
} MotionState;

extern void fn_80088F4C(void);
extern MotionState lbl_8063D378;
extern MotionState lbl_8063D400;

void fn_801FA354(void)
{
    MotionState* source;

    fn_80088F4C();

    source = lbl_8063D378.source;
    if (source != 0) {
        lbl_8063D378.position = source->position;
        lbl_8063D378.value34 = source->value34;
        lbl_8063D378.direction = source->direction;
    }

    source = lbl_8063D400.source;
    if (source != 0) {
        lbl_8063D400.position = source->position;
        lbl_8063D400.value34 = source->value34;
    }

    lbl_8063D378.active = 0;
    lbl_8063D400.active = 0;
}
