typedef unsigned char u8;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct CameraInput {
    Vec3 position;
    u8 pad0C[0x10];
    Vec3 orientation;
    u8 pad28[4];
    Vec3 target;
    u8 pad38[0x1C];
    float scale;
    u8 pad58[0x29];
    u8 snap;
} CameraInput;

typedef struct CameraState {
    u8 pad00[0x4C8];
    Vec3 position;
    u8 pad4D4[0x24];
    float blend;
    float scale;
} CameraState;

typedef struct MotionState {
    u8 pad00[0x30];
    float blend;
} MotionState;

typedef struct Runtime {
    u8 pad00[0x1C8];
    int flags;
} Runtime;

extern CameraState lbl_8063CD18, lbl_8063C6B8;
extern MotionState lbl_8063D378, lbl_8063D400;
extern Runtime lbl_8030F540;
extern int lbl_8064CF60[2];
extern int lbl_8064CF68, lbl_8064D738;
extern float lbl_80650228, lbl_80650244, lbl_80650254;
extern int fn_801FA410(int index);
extern void fn_801FA748(int index, Vec3* position);

void fn_8013310C(CameraInput* input)
{
    lbl_8064CF60[lbl_8064D738 ^ 1] = 0;
    if (lbl_8064CF60[lbl_8064D738] == 0) {
        lbl_8064CF60[lbl_8064D738] = 1;
        if (lbl_8064CF68 != 0) {
            fn_801FA410(9);
            lbl_8063CD18.blend = lbl_80650228;
            lbl_8063C6B8.blend = lbl_80650228;
            lbl_8063D378.blend = lbl_80650228;
            lbl_8063D400.blend = lbl_80650228;
            input->snap = 1;
            lbl_8064CF68 = 0;
        }
        if (input->snap == 0 && !(lbl_8030F540.flags & 1)) {
            {
                float delta = input->position.x - lbl_8063CD18.position.x;
                float amount = lbl_80650244;
                lbl_8063CD18.position.x += delta * amount;
            }
            {
                float delta = input->position.y - lbl_8063CD18.position.y;
                float amount = lbl_80650244;
                lbl_8063CD18.position.y += delta * amount;
            }
            {
                float delta = input->position.z - lbl_8063CD18.position.z;
                float amount = lbl_80650244;
                lbl_8063CD18.position.z += delta * amount;
            }
            {
                float delta = input->target.x - lbl_8063C6B8.position.x;
                float amount = lbl_80650244;
                lbl_8063C6B8.position.x += delta * amount;
            }
            {
                float delta = input->target.y - lbl_8063C6B8.position.y;
                float amount = lbl_80650244;
                lbl_8063C6B8.position.y += delta * amount;
            }
            {
                float delta = input->target.z - lbl_8063C6B8.position.z;
                float amount = lbl_80650244;
                lbl_8063C6B8.position.z += delta * amount;
            }
            {
                float delta = lbl_80650254 * input->scale - lbl_8063CD18.scale;
                float amount = lbl_80650244;
                lbl_8063CD18.scale += delta * amount;
            }
        } else {
            lbl_8063CD18.position.x = input->position.x;
            lbl_8063CD18.position.y = input->position.y;
            lbl_8063CD18.position.z = input->position.z;
            lbl_8063C6B8.position.x = input->target.x;
            lbl_8063C6B8.position.y = input->target.y;
            lbl_8063C6B8.position.z = input->target.z;
            lbl_8063CD18.scale = lbl_80650254 * input->scale;
        }
        fn_801FA748(9, &input->orientation);
    }
}
