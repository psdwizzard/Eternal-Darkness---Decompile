typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef union ParameterData {
    u16 value14;
    u8 value7;
} ParameterData;

typedef struct Parameter {
    u8 ctrl;
    u8 pad01;
    ParameterData paraData;
} Parameter;

typedef struct ParameterInfo {
    u8 numPara;
    u8 pad01[3];
    Parameter* paraArray;
} ParameterInfo;

typedef struct Emitter {
    char pad00[0xC];
    ParameterInfo* paraInfo;
    u32 flags;
    char pad14[0x28];
    u32 vid;
    char pad40[0xC];
    float fade;
} Emitter;

extern void fn_801B7E84(u32, u8, u8);
extern void fn_801B7F6C(u32, u8, u16);

static inline u8 clip127(u8 value)
{
    if (value > 0x7f) {
        return 0x7f;
    }
    return value;
}

void fn_801C8CC0(Emitter* emitter, float vol, float xPan, float yPan, float zPan, float pitch)
{
    u32 handle;
    u16 value14;
    u8 i;
    Parameter* ctrl;
    handle = emitter->vid;
    if ((emitter->flags & 0x00100000) != 0) {
        fn_801B7E84(handle, 7, clip127(127.0f * (emitter->fade * vol)));
    } else {
        fn_801B7E84(handle, 7, clip127(127.0f * vol));
    }

    fn_801B7E84(handle, 10, clip127(64.0f * (1.0f + xPan)));

    fn_801B7E84(handle, 0x83, clip127(64.0f * (1.0f - zPan)));

    pitch = 8192.0f * pitch;
    if ((u32)pitch > 0x3fff) {
        value14 = 0x3fff;
    } else {
        value14 = (u16)(u32)pitch;
    }
    fn_801B7F6C(handle, 0x84, value14);

    if (emitter->paraInfo != 0) {
        ctrl = emitter->paraInfo->paraArray;
        for (i = 0; i < emitter->paraInfo->numPara; i++) {
            if (ctrl->ctrl < 0x40 || ctrl->ctrl == 0x80 || ctrl->ctrl == 0x84) {
                fn_801B7F6C(handle, ctrl->ctrl, ctrl->paraData.value14);
            } else {
                fn_801B7E84(handle, ctrl->ctrl, ctrl->paraData.value7);
            }
            ctrl++;
        }
    }
}
