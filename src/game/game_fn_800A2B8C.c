typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Action800A2B8C {
    u8 pad00;
    u8 value10;
    u8 pad02;
    signed char value13;
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
    u32 value94;
    Vec3 position;
    u8 params[6];
    u8 typeAA;
} Action800A2B8C;

typedef struct Runtime800A2B8C {
    u8 pad000[0x84];
    u16 flags84;
    u8 pad086[2];
    Vec3 position88;
    float value94;
    float value98;
    u8 pad09C[0x30];
    Action800A2B8C actionCC;
} Runtime800A2B8C;

typedef struct Params800A2B8C {
    u32 word;
    u16 half;
} Params800A2B8C;

typedef struct Context800A2B8C {
    u8 pad00[0x64];
    Runtime800A2B8C* runtime;
} Context800A2B8C;

extern u32 lbl_80651A18;
extern u16 lbl_80651A1C;
extern float lbl_8064EE70;
extern float lbl_8064EE8C;
extern float lbl_8064EE90;
extern float lbl_8064EE94;
extern double lbl_8064EE98;

extern void *fn_80201B8C();
extern void* fn_80035628(void*);
extern void fn_801857B4(Action800A2B8C*);
extern void fn_801D38BC(void*, u32*, s16*);
extern void fn_80185A44(void);
#define FN_80201E78_RETURN void
#define FN_80201E78_PARAMETERS Vec3*, void*
extern FN_80201E78_RETURN fn_80201E78(FN_80201E78_PARAMETERS);extern void* memcpy(void*, const void*, unsigned int);
extern int fn_801E8328();

/* NonMatching: behavior-complete and size-exact. The remaining divergence is
 * MWCC scheduling/register allocation around the u16-to-float conversion and
 * the four float constant loads in the action initializer. */
void fn_800A2B8C(void* object, u16 value)
{
    Context800A2B8C* context = ((Context800A2B8C*)fn_80201B8C());
    Runtime800A2B8C* runtime = context->runtime;
    Action800A2B8C* action;
    u32 positionWord;
    s16 actionValue;
    Params800A2B8C params;
    Vec3 position;
    void* source;

    if ((runtime->flags84 & 0x20) == 0 && *(u32*)((u8*)runtime + 0x160) == 0) {
        params.word = lbl_80651A18;
        params.half = lbl_80651A1C;
        runtime->flags84 |= 0x20;
        source = fn_80035628(object);
        action = &runtime->actionCC;
        *(u32*)((u8*)runtime + 0x160) = 0;
        fn_801857B4(action);
        fn_801D38BC(source, &positionWord, &actionValue);
        action->value04 = actionValue;
        action->value08 = 0;
        action->value06 = 0;
        action->value10 = 100;
        action->value13 = -10;
        action->value19 = 16;
        action->value78 = positionWord;
        action->value1C = value;
        action->value14 = 0;
        action->value50 = lbl_8064EE8C;
        action->flags18 |= 3;
        action->callback = fn_80185A44;
        runtime->value98 = lbl_8064EE90;
        runtime->value94 = lbl_8064EE94 * (float)value;
        fn_80201E78(&position, object);
        runtime->position88 = position;
        runtime->position88.z = lbl_8064EE70;
        action->position = runtime->position88;
        memcpy(action->params, &params, 6);
        action->value94 = 0;
        action->typeAA = 2;
        fn_801E8328(16, action);
    }
}
