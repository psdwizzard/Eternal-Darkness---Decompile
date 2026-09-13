typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct EffectState {
    s32 unk00;
    s32 unk04;
    u8 pad08[4];
    s32 duration;
    s32 lifetime;
    u8 pad14[8];
    Vec3 position;
    s32 type;
    u16 strength;
    u8 pad2E[2];
    u16 rate;
    u16 radius;
    u8 pad34[3];
    u8 enabled;
    u8 mode;
    u8 pad39[0xF];
    void (*update)(void);
    u8 pad4C[0x18];
    s32 owner_id;
    void (*finish)(void);
    u8 pad6C[4];
    s32 active;
} EffectState;

extern EffectState lbl_80303B30;
extern const float lbl_8064E064;
extern const float lbl_8064E15C;

extern void fn_8014CBC0(void*);
extern void fn_80149CC4(void*, Vec3*, s32, s32, s32);
extern int fn_80035628(void*);
extern s32 fn_801D39E0(s32);
extern int fn_80201B54();
extern int fn_801E8328();
extern void fn_801FDA7C(void);
extern void fn_8014CA98(void);

void fn_80031544(void* object, s32 arg2, s32 arg3)
{
    Vec3 position;
    s32 lifetime = 30000;

    fn_8014CBC0(&lbl_80303B30);
    fn_80149CC4(object, &position, arg2, arg3, 0);
    lbl_80303B30.unk00 = 0;
    lbl_80303B30.position = position;
    lbl_80303B30.type = fn_801D39E0(fn_80035628(object));
    lbl_80303B30.unk04 = 0;
    lbl_80303B30.duration = 600;
    lbl_80303B30.lifetime = lifetime;
    lbl_80303B30.radius = 50;
    lbl_80303B30.update = fn_801FDA7C;
    lbl_80303B30.strength = 50;
    lbl_80303B30.rate = lbl_8064E064 + (float)lbl_80303B30.lifetime / lbl_8064E15C;
    lbl_80303B30.owner_id = fn_80201B54(object);
    lbl_80303B30.finish = fn_8014CA98;
    lbl_80303B30.active = 1;
    lbl_80303B30.enabled = 0;
    lbl_80303B30.mode = 4;
    fn_801E8328(0x14, &lbl_80303B30);
}
