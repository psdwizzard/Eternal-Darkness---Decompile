typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct MotionState {
    Vec3 position;
    unsigned char pad0C[0x6C];
    float time;
    void* resource;
} MotionState;

typedef struct MotionGlobals {
    unsigned char pad00[0xC];
    float time;
} MotionGlobals;

extern MotionGlobals lbl_8063E9C8;
extern float fn_801F8FAC(Vec3*, void*, float);

void fn_801FA774(MotionState* state)
{
    Vec3 position;

    state->time = fn_801F8FAC(&position, state->resource, lbl_8063E9C8.time);
    state->position = position;
}
