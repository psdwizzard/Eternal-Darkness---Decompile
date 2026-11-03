typedef unsigned char u8;
typedef unsigned short u16;
typedef struct Actor Actor;
typedef struct Range Range;
typedef struct Object Object;

typedef struct ActorMethods {
    void (*initialize)(void *, void *);
    int (*chooseAction)(void *);
    int (*chooseVariant)(int);
    int (*handleEvent)(void *, int, void *, int *);
    void (*update)(void *);
    void (*reserved14)(void);
    void (*reserved18)(void);
    void (*reserved1C)(void);
    void (*reserved20)(void);
    void (*reserved24)(void);
    void (*react)(Actor *, void *, void *, int);
    int (*interact)(void *, void *, int);
    void (*reserved30)(void);
    int (*canAct)(void *, void *);
    int (*getRange)(int, Range *);
    void (*setKind)(Actor *);
    void (*configure)(void *, void *, void *, void *);
    void (*setActions)(void *, Object *);
    void (*performAction)(Actor *, void *, int);
} ActorMethods;

struct Actor {
    ActorMethods *methods;
    u8 pad004[0x259];
    u8 field_25D;
    u8 pad25E[2];
    u16 field_260;
    u8 pad262[2];
    u8 *sounds;
    u8 pad268[4];
    u16 field_26C;
    u16 field_26E;
    u16 field_270;
    u16 field_272;
    u8 pad274[0x10];
    short counter;
};

extern u8 lbl_80248AF0[];
extern void fn_800D406C(void *, void *);
extern int fn_800D4100(void *);
extern int fn_800D4310(int);
extern int fn_800D4324(void *, int, void *, int *);
extern void fn_800D5EFC(void *);
extern void fn_800D607C(Actor *, void *, void *, int);
extern int fn_800D6294(void *, void *, int);
extern int fn_800D6314(void *, void *);
extern int fn_800D6358(int, Range *);
extern void fn_800D6430(Actor *);
extern void fn_800D64A8(void *, void *, void *, void *);
extern void fn_800D6588(void *, Object *);
extern void fn_800D6638(Actor *, void *, int);

/* Initialize the actor's parameters and behavior callbacks. */
void fn_800D3B68(Actor *actor)
{
    actor->sounds = lbl_80248AF0;
    actor->field_26C = 50;
    actor->field_26E = 1600;
    actor->field_270 = 7000;
    actor->field_272 = 34;
    actor->field_25D = 0;
    actor->counter = 0;
    actor->field_260 = 573;
    actor->methods->initialize = fn_800D406C;
    actor->methods->chooseAction = fn_800D4100;
    actor->methods->chooseVariant = fn_800D4310;
    actor->methods->handleEvent = fn_800D4324;
    actor->methods->update = fn_800D5EFC;
    actor->methods->react = fn_800D607C;
    actor->methods->interact = fn_800D6294;
    actor->methods->canAct = fn_800D6314;
    actor->methods->getRange = fn_800D6358;
    actor->methods->setKind = fn_800D6430;
    actor->methods->configure = fn_800D64A8;
    actor->methods->setActions = fn_800D6588;
    actor->methods->performAction = fn_800D6638;
}
