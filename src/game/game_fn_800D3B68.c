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
    register int (*canAct)(void *, void *);
    register void (*performAction)(Actor *, void *, int);
    register int (*getRange)(int, Range *);
    register int (*chooseAction)(void *);
    register void (*setKind)(Actor *);
    register int (*chooseVariant)(int);
    register int (*handleEvent)(void *, int, void *, int *);
    register int (*interact)(void *, void *, int);
    /* ASM: lis loads callback address halves ahead of the parameter stores;
     * C interleaves these loads with stores under the fixed compiler flags. */
    asm {
        lis chooseAction, fn_800D4100@ha
        lis chooseVariant, fn_800D4310@ha
        lis handleEvent, fn_800D4324@ha
        lis interact, fn_800D6294@ha
        lis canAct, fn_800D6314@ha
        lis getRange, fn_800D6358@ha
        lis setKind, fn_800D6430@ha
        lis performAction, fn_800D6638@ha
    }
    /* ASM: addi completes callback addresses at these store boundaries;
     * C defers the additions until later method writes under the fixed flags. */
    asm {
        addi chooseAction, chooseAction, fn_800D4100@l
    }
    actor->sounds = lbl_80248AF0;
    /* ASM: addi completes callback addresses at these store boundaries;
     * C defers the additions until later method writes under the fixed flags. */
    asm {
        addi chooseVariant, chooseVariant, fn_800D4310@l
        addi handleEvent, handleEvent, fn_800D4324@l
    }
    actor->field_26C = 50;
    actor->field_26E = 1600;
    /* ASM: addi completes callback addresses at these store boundaries;
     * C defers the additions until later method writes under the fixed flags. */
    asm {
        addi interact, interact, fn_800D6294@l
        addi canAct, canAct, fn_800D6314@l
    }
    actor->field_270 = 7000;
    /* ASM: addi completes callback addresses at these store boundaries;
     * C defers the additions until later method writes under the fixed flags. */
    asm {
        addi getRange, getRange, fn_800D6358@l
        addi setKind, setKind, fn_800D6430@l
    }
    actor->field_272 = 34;
    actor->field_25D = 0;
    actor->counter = 0;
    actor->field_260 = 573;
    actor->methods->initialize = fn_800D406C;
    /* ASM: addi completes callback addresses at these store boundaries;
     * C defers the additions until later method writes under the fixed flags. */
    asm {
        addi performAction, performAction, fn_800D6638@l
    }
    actor->methods->chooseAction = chooseAction;
    actor->methods->chooseVariant = chooseVariant;
    actor->methods->handleEvent = handleEvent;
    actor->methods->update = fn_800D5EFC;
    actor->methods->react = fn_800D607C;
    actor->methods->interact = interact;
    actor->methods->canAct = canAct;
    actor->methods->getRange = getRange;
    actor->methods->setKind = setKind;
    actor->methods->configure = fn_800D64A8;
    actor->methods->setActions = fn_800D6588;
    actor->methods->performAction = performAction;
}
