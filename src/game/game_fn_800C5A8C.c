typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Object Object;
typedef struct Queue Queue;
typedef struct Runtime Runtime;
typedef struct Object80201D14 Object80201D14;
typedef struct Object80201D2C Object80201D2C;

typedef struct ActorState {
    u8 pad00[0x44];
    Vec3 position;
    float angle;
    u8 pad54[0x18];
    int target;
    u8 pad70[0x14];
    int value84;
    u8 pad88[0xD];
    u8 value95;
} ActorState;
typedef struct ActorInfo {
    ActorState* state;
    u8 pad04[0x90];
    int value94;
    u8 pad98[7];
    u8 value9F;
} ActorInfo;

extern void* fn_80201B8C(unsigned char*);
extern void* fn_80201BC8(void*);
extern int fn_80201B54(int*);
extern void* fn_8004918C(void);
extern void* fn_80036374(void*);
extern void fn_8011F114(Vec3*, Vec3*);
extern int fn_8011EB04(Object*);
extern u8* fn_801294DC(void*, int, int, int);
extern u64 fn_8020123C(int, int, int, int);
extern float fn_8012B7D0(const void*, const void*);
extern float fn_8012B750(void*);
extern int fn_8012A1FC(void*, int);
extern void fn_801287C4(Queue*, void*, u32, u32);
extern float fn_80179F20(float);
extern void fn_80129BA4(u8*, float, float);
extern void fn_80128C44(Runtime*, u32, u32);
extern void fn_80128C28(Runtime*, u32, u32);
extern int fn_80204810(void*, int);
extern void fn_800C59F0(void*, int);
extern void fn_80201D2C(Object80201D2C*, int);
extern void fn_80201D14(Object80201D14*, u8);
extern const float lbl_8064F1E8;

void fn_800C5A8C(void* object)
{
    ActorInfo* info;
    void* owner;
    void* entry;
    void* target;
    ActorInfo* targetInfo;
    void* targetOwner;
    register int id;
    Vec3 position;
    Vec3 temporary;
    Vec3 anglePosition;
    Vec3 ownerPosition;
    float angle;
    int duration;

    info = fn_80201B8C(object);
    owner = fn_80201BC8(object);
    id = fn_80201B54(object);
    fn_8004918C();
    target = fn_80036374(object);
    if (target != 0) {
        targetInfo = fn_80201B8C(target);
        targetOwner = fn_80201BC8(target);
        fn_8011F114(&temporary, targetOwner);
        position = temporary;
        fn_8011EB04(targetOwner);
        entry = fn_801294DC(owner, 0x72, 0x100, 6);
        if (entry != 0 && (u32)(fn_8020123C(0xC2, id, fn_80201B54(target), 1) & 0xFFFFFFFF) == 1) {
            anglePosition = position;
            angle = fn_8012B7D0(owner, &anglePosition);
            fn_8012B750(owner);
            duration = fn_8012A1FC(owner, 0x72);
            info->state->target = fn_80201B54(target);
            fn_8011F114(&ownerPosition, owner);
            info->state->position = ownerPosition;
            info->state->angle = angle;
            fn_801287C4(entry, (void*)fn_80204810, ((u32)id << 8) | 0x16, (duration >> 17) + 60);
            fn_80129BA4(entry, fn_80179F20(angle), lbl_8064F1E8);
            fn_80128C44(entry, (u32)fn_80204810, ((u32)id << 8) | 7);
            fn_80128C28(entry, (int)fn_80204810, ((u32)id << 8) | 12);
            fn_800C59F0(target, 1200);
            fn_80201D2C(object, 0x54);
            fn_80201D14(object, 1);
            info->state->value95 = targetInfo->value9F;
            info->state->value84 = targetInfo->value94;
        }
    }
}
