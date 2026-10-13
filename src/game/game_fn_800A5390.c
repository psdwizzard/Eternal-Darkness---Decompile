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

extern int lbl_8064C4E0;
extern int lbl_8064C4E4;
extern int lbl_8064C544;
extern void *lbl_8064C5B4;
extern int lbl_8064C5C0;
extern int lbl_8064C948;
extern int lbl_8064D18C;
extern const float lbl_8064EEF8;
extern const float lbl_8064EEFC;
extern const float lbl_8064EF00;

extern void fn_800073E4();
extern void fn_8002A508();
extern void fn_8002AA18();
extern void fn_800A5330();

extern void fn_80046F28(void *, int);
extern void fn_80046FC4(int, int);
extern int fn_8004918C(void);
extern void fn_8004948C(void *, int, int);
extern void fn_80067A18(int);
extern int fn_8006D4DC(int);
extern void fn_800CF598(void *);
extern void fn_800CF904(int);
extern void fn_8011DE18(void);
extern void fn_8011E174(int, int);
extern void fn_8011F104(int, float, float, float);
extern void fn_8011F114(Vec3 *, void *);
extern int fn_8011FB4C(int);
extern void fn_80120AD0(void *, int, int, int, float, float);
extern void fn_8012B750(void *);
extern void fn_8012B7A0(int);
extern void fn_8012C478(int, int, int);
extern void fn_8013B83C(int);
extern void *fn_80155DB4(void *);
extern void fn_801568C0(void *, void *);
extern void fn_801568FC(void *, void *);
extern void fn_8015C948(int, int, int, int, int, int, int, int, void *, int, int);
extern void fn_801A7864(int);
extern void fn_801AAE68(int, int, int, Vec3 *, float, int, int, int, unsigned short, int);
extern void fn_801AC350(int, int, int);
extern void fn_801D7E70(int, int);
extern void fn_801E7974(int, int);
extern void fn_801E79A0(int, int);
extern void fn_801E8328(int, void *);
extern void fn_801F6ED0(int, int);
extern void fn_801FA4F0(int, int);
extern unsigned long long fn_8020123C(int, int, int, int);
extern void *fn_80201814(int);
extern int fn_80201AE4(void);
extern void fn_80201AF8(int);
extern int fn_80201B44(void);
extern int fn_80201B54(void *);
extern Actor *fn_80201B8C(void *);
extern int fn_80201BC8(void *);
extern void fn_80201D1C(void *, int);
extern void fn_80201D34(void *, int);
extern void fn_80201D3C(void *, int);
extern void fn_80201D54(void *, int);

void fn_800A5390(void *object, void *target, Actor *actor, int unused, int arg4, int arg5, int arg6)
{
    Vec3 position;
    int skip;
    int id;
    void *handler;
    void *newObject;
    int model;
    int owner;
    Actor *newActor;
    int result;
    int value;

    if (arg6 != 0) {
        if (lbl_8064C948 != 0) {
            fn_801E7974(lbl_8064C4E0, 0x39A);
        } else {
            fn_801E79A0(lbl_8064C4E0, 0x39A);
        }
    }
    skip = fn_8006D4DC(0x17);
    id = fn_80201B54(object);
    fn_801568FC(fn_80155DB4(object), fn_8002AA18);
    fn_80201D3C(object, 1);
    actor->state = 2;
    fn_8011F114(&position, target);
    if (skip != 0) {
        fn_80067A18(id);
        fn_801E8328(2, object);
        fn_80201D34(object, 0);
        fn_80201D1C(object, 1);
    } else if (arg4 != 0) {
        lbl_8064C544 = 0;
        fn_800CF598(object);
        fn_80067A18(id);
        fn_80120AD0(target, 0, 0, 0x101, lbl_8064EEFC, lbl_8064EEF8);
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
    handler = fn_80155DB4(newObject);
    model = fn_80201BC8(newObject);
    newActor = fn_80201B8C(newObject);
    fn_801568FC(handler, fn_800073E4);
    fn_801568C0(handler, fn_8002A508);
    fn_80201D3C(newObject, 0);
    fn_8020123C(0xC0, fn_80201B54(newObject), actor->data->unkBC, 1);
    newActor->state = 1;
    newActor->substate = 1;
    newActor->data->unkBC = 0;
    result = fn_8011FB4C(model);
    lbl_8064C5B4 = handler;
    fn_80201AF8(owner);
    actor->data->unkBC = 0;

    if (skip == 0 && result != lbl_8064D18C) {
        fn_8015C948(result, 0, 0, 0, 4, 1, 1, 0x11, fn_800A5330, model, 1);
        fn_801AC350(0, 1, 0);
        lbl_8064C5C0 = 1;
    } else if (skip != 0) {
        fn_801F6ED0(lbl_8064C4E4, model);
        lbl_8064C4E4 = model;
        fn_80201D54(newObject, lbl_8064D18C);
        fn_80046F28(newObject, lbl_8064D18C);
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
    fn_801AAE68(0x2B1, 0x64, 0, &position, lbl_8064EF00, 2, 1, 0, (unsigned short)lbl_8064D18C, 0);
}
