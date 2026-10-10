typedef unsigned char u8;

typedef float Matrix[3][4];

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct ShortCoord3 {
    short x, y, z;
} ShortCoord3;

typedef struct EffectDesc {
    u8 prefix[0x14];
    float scale;
    u8 mode;
    u8 phase;
    u8 reserved[0x7A];
} EffectDesc;

typedef struct Emitter {
    ShortCoord3 position;
    short pad6;
    float rotation[4];
    short scale;
} Emitter;

typedef struct EmitterSlot {
    int pad0;
    void* effect;
} EmitterSlot;

extern Vec3 lbl_8023A6F4;
extern void* lbl_8064CF50;
extern const float lbl_80650228;
extern const float lbl_80650268;

extern void fn_802114E0(Matrix output, void* angles);
extern void fn_80211710(Matrix m, Vec3* in, Vec3* out);
extern void fn_80211AAC(Vec3* in, Vec3* out);
extern void fn_80179E60(short* destination, float* source);
extern void fn_80179BC0(Vec3* source, ShortCoord3* destination);
extern void fn_801A19BC(void* descriptor);
extern void* fn_80154158(Vec3* position, void* rotation, void* descriptor);
extern unsigned int fn_800FBFB0(void);
extern void* fn_80156938(void* object);
extern ShortCoord3* fn_8017FDE4(void* object);
extern ShortCoord3* fn_8017FDEC(void* object);
extern void fn_80180374(void* object, int value);
extern void fn_80180384(void* object, int value);

void fn_8013454C(Emitter* emitter, EmitterSlot* slot)
{
    Matrix matrix;
    EffectDesc desc;
    Vec3 up;
    Vec3 dir;
    Vec3 position;
    short rotation[4];
    ShortCoord3* dest;
    ShortCoord3* angles;

    up = lbl_8023A6F4;
    if (slot->effect == 0) {
        position.x = emitter->position.x;
        position.y = emitter->position.y;
        position.z = emitter->position.z;
        if (0.0f == emitter->rotation[0] &&
            0.0f == emitter->rotation[1] &&
            0.0f == emitter->rotation[2] &&
            0.0f == emitter->rotation[3]) {
            emitter->rotation[3] = lbl_80650228;
        }
        fn_802114E0(matrix, emitter->rotation);
        fn_80211710(matrix, &up, &dir);
        fn_80211AAC(&dir, &dir);
        fn_80179E60(rotation, &dir.x);
        fn_801A19BC(&desc);
        desc.scale = emitter->scale / lbl_80650268;
        desc.phase = (fn_800FBFB0() + 30) & 31;
        slot->effect = fn_80154158(&position, rotation, &desc);
        if (slot->effect != 0) {
            if ((lbl_8064CF50 = fn_80156938(slot->effect)) != 0) {
                fn_80180374(lbl_8064CF50, 200);
                fn_80180384(lbl_8064CF50, 20);
            }
        }
    } else {
        lbl_8064CF50 = fn_80156938(slot->effect);
        dest = fn_8017FDE4(lbl_8064CF50);
        angles = fn_8017FDEC(lbl_8064CF50);
        dest->x = emitter->position.x;
        dest->y = emitter->position.y;
        dest->z = emitter->position.z;
        fn_802114E0(matrix, emitter->rotation);
        fn_80211710(matrix, &up, &dir);
        fn_80211AAC(&dir, &dir);
        fn_80179BC0(&dir, angles);
    }
}
