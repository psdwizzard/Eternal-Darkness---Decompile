typedef unsigned char u8;

typedef struct MotionObject {
    u8 pad00[0x7C];
    void* resource;
} MotionObject;

typedef struct MotionGlobals {
    void* entry;
    MotionObject* object;
    float scale;
    float time;
    int value;
    int type;
} MotionGlobals;

extern MotionGlobals lbl_8063E9C8;
extern const float lbl_80651464;
extern const double lbl_80651480;
extern const float lbl_806514C8;
extern void fn_80144C40(void);
extern unsigned int fn_80144710(unsigned int, int, int);
extern int fn_801F9A38(void*, int);

void fn_801FA9C8(short amount)
{
    float delta;
    float result;
    float time;

    fn_80144C40();
    delta = (float)amount / lbl_8063E9C8.scale;
    if (fn_80144710(0x1000000, 1, 0) != 0) {
        delta *= lbl_806514C8;
    }

    {
        float zero = lbl_80651464;
        lbl_8063E9C8.time += delta;
        time = zero > lbl_8063E9C8.time ? zero : lbl_8063E9C8.time;
    }
    if ((float)fn_801F9A38(lbl_8063E9C8.object->resource, 1) < time) {
        result = (float)fn_801F9A38(lbl_8063E9C8.object->resource, 1);
    } else {
        result = lbl_80651464 > lbl_8063E9C8.time ? lbl_80651464 : lbl_8063E9C8.time;
    }
    lbl_8063E9C8.time = result;
}
