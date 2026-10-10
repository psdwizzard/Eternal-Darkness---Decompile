typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct ShortCoord3 {
    short x, y, z;
} ShortCoord3;

typedef struct Emitter {
    ShortCoord3 position;
    short pad6;
    float rotation[4];
    short scale;
} Emitter;

typedef struct Action {
    u8 pad00;
    u8 value01;
    u8 pad02;
    s8 value03;
    s16 value04;
    s16 value06;
    s16 value08;
    u8 pad0A[0xA];
    u8 value14;
    u8 pad15[3];
    u8 flags18;
    u8 value19;
    u8 pad1A[2];
    u16 value1C;
    u8 pad1E[0x32];
    float value50;
    u8 pad54[0x24];
    u32 value78;
    u8 pad7C[0x14];
    void (*callback)(void);
    void* handle;
    Vec3 position;
    u8 params[6];
    u8 typeAA;
} Action;

typedef struct EmitterSlot {
    int pad0;
    Action* action;
} EmitterSlot;

typedef struct Manager {
    u8 pad00[0x34];
    int value34;
} Manager;

typedef struct Params {
    u32 word;
    u16 half;
} Params;

extern u32 lbl_80651BA8;
extern u16 lbl_80651BAC;
extern Vec3 lbl_8023A70C;
extern u8 lbl_8030F540[];
extern Action lbl_805AD564;
extern const float lbl_80650270;

extern Manager* fn_8015E4A4(void);
extern void fn_801857B4(Action*);
extern void fn_801D38BC(int, u32*, s16*);
extern void fn_80185A44(void);
extern void* memcpy(void*, const void*, unsigned int);
extern int fn_801E8328();
extern void fn_801869DC(void*);
extern ShortCoord3* fn_8017FDE4(void*);
extern void fn_801869E4(void*, u16, u16, int);

void fn_801349BC(Emitter* emitter, EmitterSlot* slot)
{
    u32 positionWord;
    Params params;
    Vec3 position;
    Manager* manager;
    Action* action;
    s8 kind;
    u16 value;
    u16 scale;
    ShortCoord3* dest;
    Action* effect;

    kind = lbl_8030F540[0x1E0];
    params.word = lbl_80651BA8;
    params.half = lbl_80651BAC;
    position = lbl_8023A70C;
    manager = fn_8015E4A4();
    action = slot->action;
    if (action == 0) {
        slot->action = &lbl_805AD564;
        position.x = emitter->position.x;
        position.y = emitter->position.y;
        position.z = emitter->position.z;
        effect = &lbl_805AD564;
        fn_801857B4(effect);
        fn_801D38BC(kind, &positionWord, &effect->value04);
        value = (manager->value34 - (*(int*)(lbl_8030F540 + 0x1C8) >> 1)) * 2;
        effect->value01 = 100;
        effect->value03 = -10;
        effect->value08 = value;
        effect->value06 = value;
        effect->value19 = 16;
        effect->value14 = 0;
        effect->value1C = emitter->scale * 4;
        effect->value50 = lbl_80650270;
        effect->flags18 |= 2;
        effect->value78 = positionWord;
        effect->callback = fn_80185A44;
        effect->position = position;
        memcpy(effect->params, &params, 6);
        effect->handle = 0;
        effect->typeAA = 0x80;
        fn_801E8328(0x10, effect);
        slot->action = &lbl_805AD564;
    } else {
        scale = emitter->scale * 4;
        fn_801869DC(action->handle);
        dest = fn_8017FDE4(action->handle);
        dest->x = emitter->position.x;
        dest->y = emitter->position.y;
        dest->z = emitter->position.z;
        fn_801869E4(action->handle, scale, scale, 0);
        lbl_805AD564.position = position;
    }
}
