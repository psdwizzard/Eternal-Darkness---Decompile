typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct RuntimeObject {
    u8 type;
    u8 state;
    u16 pad2;
    u16 mode;
    u8 pad6[14];
    u32 flags14;
    u32 flags18;
    u32 flags1C;
    u32 flags20;
    u8 pad24[6];
    u16 timer;
    u8 pad2C[4];
    u32 value30;
    u32 value34;
    u8 pad38[0x5C];
    u32 value94;
    u8 pad98[0x10];
    s32 ownerA8;
    u8 padAC[0x10];
    u8 classBC;
    u8 padBD[3];
    void *component;
    void *effect;
    u8 padC8[0x3C];
    u16 field104;
    u16 field106;
} RuntimeObject;

typedef struct Component {
    u8 pad[8];
    s32 kind;
    u8 padC[0x3C];
    s32 enabled;
} Component;

typedef struct ObjectState {
    s32 unused;
    RuntimeObject **installed;
} ObjectState;

extern u32 lbl_802FC5BC[];
extern void *fn_80201B8C();
extern void *fn_80201BC8();
extern int fn_80201B54();
extern void *fn_80149E04(void);
extern void fn_80147E88(RuntimeObject *object);
extern void fn_801498AC(RuntimeObject *object, Component *component);
extern void fn_80187968(RuntimeObject *object);
extern int fn_801E8328();
extern s32 fn_801D39E0(s32 kind);
extern void *fn_8014C68C(s32 owner, s32 kind, s32 enabled, s32 *value,
                         s32 time, s32 interval, s32 duration);
extern s32 fn_80066D04(void *object, s32 index);
extern void fn_8012C478(s32 state, s32 index, s32 enabled);

void fn_80067EB8(void *object)
{
    ObjectState *state = fn_80201B8C(object);
    RuntimeObject **installed = state != 0 ? state->installed : 0;
    Component *component;
    RuntimeObject *runtime;

    if (installed != 0) {
        s32 object_state = (s32)fn_80201BC8(object);
        s32 value;
        s32 second;
        s32 third;

        (*installed)->component = fn_80149E04();
        runtime = *installed;
        component = runtime->component;
        if (component != 0) {
            fn_80147E88(runtime);
            fn_801498AC(runtime, component);
            runtime->classBC = 12;
            component->kind = 17;
            component->enabled = 1;
            runtime->value94 = 0;
            fn_80187968(runtime);
            runtime->state = 15;
            runtime->mode = 6;
            runtime->flags14 = 1;
            runtime->flags18 = 1;
            runtime->flags1C = 0;
            runtime->flags20 = 1;
            runtime->value30 = lbl_802FC5BC[0];
            runtime->value34 = lbl_802FC5BC[3];
            runtime->timer = 300;
            runtime->ownerA8 = fn_80201B54(object);
            fn_801E8328(17, *installed);
        }
        value = fn_801D39E0(2);
        (*installed)->effect = fn_8014C68C(fn_80201B54(object), 17, 1,
                                           &value, 1000, 100000, 300);
        second = fn_80066D04(object, 2);
        third = fn_80066D04(object, 3);
        if (second != 0) {
            fn_8012C478(object_state, 2, 1);
        }
        if (third != 0) {
            fn_8012C478(object_state, 3, 1);
        }
        fn_8012C478(object_state, 0, 1);
        (*installed)->field104 = 0;
        (*installed)->field106 = 0;
    }
}
