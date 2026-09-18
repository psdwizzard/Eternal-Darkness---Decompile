typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Descriptor {
    int state;
    int field4;
    u8 pad8[4];
    int duration;
    int limit;
    u8 pad14[8];
    Vec3 position;
    int resource_kind;
    u16 field2C;
    u16 field2E;
    u16 scaled_limit;
    u16 field32;
    u8 pad34[3];
    u8 enabled;
    u8 mode;
    u8 pad39[0xF];
    void (*update)(void);
    u8 pad4C[0x18];
    void *owner;
    void (*callback)(void);
} Descriptor;

extern Descriptor lbl_803254C8;
extern float lbl_8064F430;
extern float lbl_8064F434;
extern void fn_801FDA7C(void);
extern void fn_8014CA98(void);
extern void fn_8014CBC0(Descriptor *);
extern void fn_80149CC4(void *, Vec3 *, void *, void *, int);
extern int fn_801D39E0(int);
extern void *fn_80201B54(void *);
extern int fn_801E8328();

void fn_800D9064(void *object, void *arg1, void *arg2)
{
    Vec3 position;
    int limit = 30000;

    fn_8014CBC0(&lbl_803254C8);
    fn_80149CC4(object, &position, arg1, arg2, 0);
    lbl_803254C8.state = 0;
    lbl_803254C8.position = position;
    lbl_803254C8.resource_kind = fn_801D39E0(3);
    lbl_803254C8.field4 = 0;
    lbl_803254C8.duration = 300;
    lbl_803254C8.limit = limit;
    lbl_803254C8.field32 = 50;
    lbl_803254C8.update = fn_801FDA7C;
    lbl_803254C8.field2C = 100;
    lbl_803254C8.scaled_limit = (u16)(lbl_8064F430 + (float)lbl_803254C8.limit / lbl_8064F434);
    lbl_803254C8.owner = fn_80201B54(object);
    lbl_803254C8.callback = fn_8014CA98;
    lbl_803254C8.enabled = 0;
    lbl_803254C8.mode = 4;
    fn_801E8328(20);
}
