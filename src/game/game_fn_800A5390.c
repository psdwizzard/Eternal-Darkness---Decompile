typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct ActorData {
    char pad0[0x44];
    int unk44;
    char pad48[0xBC - 0x48];
    int unkBC;
} ActorData;

typedef struct Actor {
    char pad0[0x8C];
    ActorData *data;
    char pad90[0x9E - 0x90];
    unsigned char state;
    unsigned char substate;
} Actor;

typedef struct Node Node;
typedef struct Object Object;
typedef struct Data Data;
typedef struct State State;
typedef struct Position Position;
typedef struct Entry80201814 Entry80201814;
typedef struct Object80201D1C Object80201D1C;
typedef struct Object80201D34 Object80201D34;
typedef struct Object80201D3C Object80201D3C;
typedef struct Object80201D54 Object80201D54;

extern unsigned char *lbl_8064C4E0;
extern void *lbl_8064C4E4;
extern int lbl_8064C544;
extern void *lbl_8064C5B4;
extern int lbl_8064C5C0;
extern int lbl_8064C948;
extern int lbl_8064D18C;
extern const float lbl_8064EEF8;
extern const float lbl_8064EEFC;
extern const float lbl_8064EF00;

extern int fn_800073E4(void *object, int value, int apply);
extern int fn_8002A508(void *callback);
extern int fn_8002AA18(void *callback, void *unused, int run);
extern void fn_800A5330(int object);

extern void fn_80046F28(void *object, void *value);
extern void fn_80046FC4(int model_id, int notify);
extern void *fn_8004918C(void);
extern void fn_8004948C(void *object, void *destination, int mode);
extern void fn_80067A18(int object_id);
extern int fn_8006D4DC(int value);
extern void fn_800CF598(void *object);
extern void fn_800CF904(int enabled);
extern void fn_8011DE18(void);
extern void fn_8011E174(unsigned int mask, int enabled);
extern void fn_8011F104(Vec3 *value, float x, float y, float z);
extern void fn_8011F114(Vec3 *destination, Vec3 *source);
extern void *fn_8011FB4C(void *object);
extern void fn_80120AD0(Object *object, const Position *position, unsigned short value,
                        unsigned int state, float first, float second);
extern float fn_8012B750(void *object);
extern void fn_8012B7A0(void *object);
extern void fn_8012C478(State *object, int index, int enabled);
extern void fn_8013B83C(void *object);
extern Node *fn_80155DB4(unsigned int id);
extern void fn_801568C0(Object *object, void *value);
extern void fn_801568FC(Object *object, void *value);
extern void fn_8015C948(int value08, int value1C, int value20, int value0C, int value10,
                        int duration, int value04, int kind, int callback,
                        int callback_arg, int value18);
extern void fn_801A7864(Data *data);
extern int fn_801AAE68(unsigned short id, unsigned char arg4, unsigned char arg5,
                       float magnitude, Vec3 *position, signed char active,
                       unsigned char arg8, unsigned char arg9, unsigned short kind,
                       unsigned int flags);
extern void fn_801AC350(signed char value, int detailed, int drain);
extern void fn_801D7E70(int value, int flag);
extern void fn_801E7974(unsigned char *bits, unsigned int index);
extern void fn_801E79A0(unsigned char *bits, unsigned int index);
extern int fn_801E8328(unsigned int word0, unsigned int word4);
extern void fn_801F6ED0(void *previous, void *replacement);
extern void fn_801FA4F0(unsigned short state, int token);
extern unsigned long long fn_8020123C(int kind, int arg1, int arg2, int arg3);
extern Entry80201814 *fn_80201814(int id);
extern int fn_80201AE4(void);
extern int fn_80201AF8(int value);
extern int fn_80201B44(void);
extern int fn_80201B54(int *object);
extern void *fn_80201B8C(unsigned char *object);
extern void *fn_80201BC8(void *object);
extern void fn_80201D1C(Object80201D1C *object, unsigned char value);
extern void fn_80201D34(Object80201D34 *object, int value);
extern void fn_80201D3C(Object80201D3C *object, int value);
extern void fn_80201D54(Object80201D54 *object, void *value);

void fn_800A5390(void *object, Vec3 *target, Actor *actor, int unused, int arg4, int arg5, int arg6)
{
    Vec3 position;
    int skip;
    int id;
    void *handler;
    void *newObject;
    void *model;
    int owner;
    Actor *newActor;
    void *result;
    void *value;

    if (arg6 != 0) {
        if (lbl_8064C948 != 0) {
            fn_801E7974(lbl_8064C4E0, 0x39A);
        } else {
            fn_801E79A0(lbl_8064C4E0, 0x39A);
        }
    }
    skip = fn_8006D4DC(0x17);
    id = fn_80201B54(object);
    fn_801568FC((Object *)fn_80155DB4((unsigned int)object), (void *)fn_8002AA18);
    fn_80201D3C(object, 1);
    actor->state = 2;
    fn_8011F114(&position, target);
    if (skip != 0) {
        fn_80067A18(id);
        fn_801E8328(2, (unsigned int)object);
        fn_80201D34(object, 0);
        fn_80201D1C(object, 1);
    } else if (arg4 != 0) {
        lbl_8064C544 = 0;
        fn_800CF598(object);
        fn_80067A18(id);
        fn_80120AD0((Object *)target, 0, 0, 0x101, lbl_8064EEFC, lbl_8064EEF8);
        fn_80201D34(object, 0x15);
        fn_80201D1C(object, 1);
    } else if (arg5 != 0) {
        switch (actor->substate) {
        case 3:
            fn_80201D34(object, 4);
            fn_80201D1C(object, 1);
            break;
        case 4:
            fn_80201D34(object, 5);
            fn_80201D1C(object, 1);
            break;
        case 6:
            fn_8011E174(0x400, 0);
            fn_80201D34(object, 6);
            fn_80201D1C(object, 1);
            break;
        }
    }

    owner = actor->data->unkBC;
    newObject = fn_80201814(owner);
    handler = fn_80155DB4((unsigned int)newObject);
    model = fn_80201BC8(newObject);
    newActor = fn_80201B8C(newObject);
    fn_801568FC(handler, (void *)fn_800073E4);
    fn_801568C0(handler, (void *)fn_8002A508);
    fn_80201D3C(newObject, 0);
    fn_8020123C(0xC0, fn_80201B54(newObject), actor->data->unkBC, 1);
    newActor->state = 1;
    newActor->substate = 1;
    newActor->data->unkBC = 0;
    result = fn_8011FB4C(model);
    lbl_8064C5B4 = handler;
    fn_80201AF8(owner);
    actor->data->unkBC = 0;

    if (skip == 0 && (int)result != lbl_8064D18C) {
        fn_8015C948((int)result, 0, 0, 0, 4, 1, 1, 0x11, (int)fn_800A5330, (int)model, 1);
        fn_801AC350(0, 1, 0);
        lbl_8064C5C0 = 1;
    } else if (skip != 0) {
        fn_801F6ED0(lbl_8064C4E4, model);
        lbl_8064C4E4 = model;
        fn_80201D54(newObject, (void *)lbl_8064D18C);
        fn_80046F28(newObject, (void *)lbl_8064D18C);
        if (owner == fn_80201AE4()) {
            fn_80046FC4(lbl_8064D18C, 0);
        }
        fn_8012C478(model, 0xF, 1);
        fn_8011F104(model, position.x, position.y, position.z);
        fn_8012B750(target);
        fn_8012B7A0(model);
        if (newActor->data->unk44 != 0) {
            fn_8020123C(0x51, 0, newActor->data->unk44, 0);
        }
    } else {
        lbl_8064C4E4 = model;
        fn_8013B83C(model);
        fn_801FA4F0(2, 1);
        fn_801F6ED0(lbl_8064C4E4, model);
        fn_8011DE18();
    }

    if (skip == 0) {
        fn_800CF904(1);
        fn_801D7E70(fn_80201B44(), 1);
    }
    value = fn_8004918C();
    fn_8004948C(newObject, value, 0);
    fn_801A7864(value);
    fn_801AAE68(0x2B1, 0x64, 0, lbl_8064EF00, &position, 2, 1, 0, lbl_8064D18C, 0);
}
