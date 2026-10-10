typedef unsigned char u8;

typedef float Matrix[3][4];

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct ShortCoord3 {
    short x, y, z;
} ShortCoord3;

typedef struct EffectConfig {
    u8 kind;              /* 0x00 */
    u8 count;             /* 0x01 */
    u8 alpha;             /* 0x02 */
    signed char speed;    /* 0x03 */
    u8 pad4[2];
    unsigned short life;  /* 0x06 */
    short spread;         /* 0x08 */
    u8 padA[0xA];
    short size;           /* 0x14 */
    u8 pad16[2];
    u8 color[4];          /* 0x18 */
    u8 pad1C;
    u8 fade;              /* 0x1D */
    u8 pad1E[2];
    u8 mode;              /* 0x20 */
    u8 pad21;
    u8 flag;              /* 0x22 */
    u8 pad23[0x71];
} EffectConfig;

typedef struct Emitter {
    ShortCoord3 position;
    short pad6;
    float rotation[4];
} Emitter;

typedef struct EmitterSlot {
    int pad0;
    void* effect;
} EmitterSlot;

extern Vec3 lbl_8023A6E8;
extern void* lbl_8064CF54;
extern const float lbl_80650228;

extern void fn_802114E0(Matrix output, void* angles);
extern void fn_80211710(Matrix m, Vec3* in, Vec3* out);
extern void fn_80211AAC(Vec3* in, Vec3* out);
extern void fn_80179E60(short* destination, float* source);
extern void fn_80179BC0(Vec3* source, ShortCoord3* destination);
extern void fn_8019D560(void* config);
extern void* fn_80152F90(Vec3* position, void* rotation, u8* config, u8 kind);
extern void* fn_80156938(void* object);
extern ShortCoord3* fn_8017FDE4(void* object);
extern ShortCoord3* fn_8017FDEC(void* object);
extern void fn_80180384(void* object, int value);

void fn_8013430C(Emitter* emitter, EmitterSlot* slot)
{
    Matrix matrix;
    EffectConfig config;
    Vec3 up;
    Vec3 dir;
    Vec3 position;
    short rotation[4];
    ShortCoord3* dest;
    ShortCoord3* angles;

    up = lbl_8023A6E8;
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
        fn_8019D560(&config);
        config.kind = 0x10;
        config.count = 10;
        config.life = 0xFFFF;
        config.spread = 0x40;
        config.speed = -2;
        config.alpha = 0x80;
        config.size = 12;
        config.color[0] = 0x80;
        config.color[1] = 0x80;
        config.color[2] = 0x80;
        config.color[3] = 0x80;
        config.mode = 5;
        config.flag = 0;
        config.fade = 0x40;
        slot->effect = fn_80152F90(&position, rotation, (u8*)&config, 200);
        if (slot->effect != 0) {
            if ((lbl_8064CF54 = fn_80156938(slot->effect)) != 0) {
                fn_80180384(lbl_8064CF54, 20);
            }
        }
    } else {
        lbl_8064CF54 = fn_80156938(slot->effect);
        dest = fn_8017FDE4(lbl_8064CF54);
        angles = fn_8017FDEC(lbl_8064CF54);
        dest->x = emitter->position.x;
        dest->y = emitter->position.y;
        dest->z = emitter->position.z;
        fn_802114E0(matrix, emitter->rotation);
        fn_80211710(matrix, &up, &dir);
        fn_80211AAC(&dir, &dir);
        fn_80179BC0(&dir, angles);
    }
}
