typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ObjectData {
    u8 pad[0x90];
    int resourceIndex;
    u8 pad94[0xB];
    u8 kind;
} ObjectData;

typedef struct Resource {
    u8 pad[0x90];
    s16 amount;
    s16 alternateAmount;
} Resource;

typedef struct ModeState {
    int pad[2];
    int mode;
} ModeState;

typedef struct Effect Effect;
typedef struct Position { u32 words[3]; } Position;

extern ModeState lbl_803003C8;
extern int fn_80201B44(void);
extern int fn_80201B54(int *object);
extern void *fn_80201814(int id);
extern void *fn_80036D5C(void *object);
extern void fn_80036DA4(void *object, void *flags);
extern int fn_80204508(void *object, void *other);
extern void *fn_80201B8C(u8 *object);
extern Resource *fn_80072354(int index);
extern Effect *fn_801A717C(void);
extern void fn_801A7228(Effect *effect);
extern void fn_801A74A0(Effect *effect, u32 id);
extern void fn_801A74A8(Effect *effect, u32 id);
extern void fn_801A7538(Effect *effect, u16 type);
extern void fn_801A7518(Effect *effect, s16 amount);
extern void fn_801A7470(Effect *effect, u32 value);
extern void *fn_80201BC8(void *object);
extern Position *fn_8011F130(void *transform);
extern void fn_801A764C(Effect *effect, const Position *position);
extern unsigned long long fn_8020123C(int type, int objectId, int actorId, int effect);

void fn_800CC860(void *object, int mode, s16 amount)
{
    int actorId;
    int objectId;
    void *actor;
    ObjectData *data;
    Resource *resource;
    Effect *effect;
    s16 change;

    actorId = fn_80201B44();
    objectId = fn_80201B54(object);
    actor = fn_80201814(actorId);
    if (lbl_803003C8.mode != 1 &&
        ((actor != 0 && !((u32)fn_80036D5C(object) & 0x10) && mode == 1 &&
          (u8)fn_80204508(object, fn_80201814(actorId)) != 0) ||
         (actor != 0 && mode == 2) ||
         (actor != 0 && mode == 3 && ((u32)fn_80036D5C(object) & 0x2000)))) {
        data = fn_80201B8C(object);
        resource = fn_80072354(data->resourceIndex);
        effect = fn_801A717C();
        switch (mode) {
        case 1:
            change = -resource->alternateAmount;
            break;
        case 2:
            if (data->kind == 7)
                change = -amount;
            else
                change = -resource->amount;
            break;
        case 3:
            change = amount;
            break;
        }
        if (change != 0) {
            fn_801A74A0(effect, objectId);
            fn_801A74A8(effect, actorId);
            fn_801A7538(effect, 2);
            fn_801A7518(effect, change);
            fn_801A7470(effect, -1);
            fn_801A764C(effect, fn_8011F130(fn_80201BC8(object)));
            fn_8020123C(0x27, objectId, actorId, (int)effect);
            fn_80036DA4(object, (void *)((u32)fn_80036D5C(object) | 0x10));
        }
        fn_801A7228(effect);
    }
}
