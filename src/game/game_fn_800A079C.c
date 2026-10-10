typedef unsigned char u8;
typedef short s16;
typedef int s32;
typedef float f32;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 mode;
} ModeState;

typedef struct {
    u8 pad0[0x8];
    u8 timer;
} EventState;

typedef struct {
    u8 pad0[0x15];
    u8 level;
    u8 pad16[0xC4 - 0x16];
    EventState *event;
} Owner;

typedef struct {
    u8 pad0[0x9A];
    s16 kind;
} ActorData;

extern s32 lbl_8064D18C;
extern ModeState lbl_803003C8;
extern char lbl_80245628[];
extern const f32 lbl_8064EE58;
extern const f32 lbl_8064EE5C;

extern void *fn_80201B9C(void);
extern int fn_80201EB8(void *);
extern ActorData *fn_80201B8C(void *);
extern int fn_80201B64(void *);
extern int fn_80201B54(void *);
extern void *fn_80201BC0(void *);
extern unsigned long long fn_8020123C(int, int, int, int);
extern void fn_8020104C(int, int, int, int, float);
extern void *fn_801E741C(char *);
extern int fn_8015C4A4(void *, int);
extern Vec3s *fn_80158ABC(int, int, void *);
extern void *fn_8007091C(int, int, int, s32, Vec3 *, f32);

static void fn_800A079C_start(s32 handle)
{
    fn_8020123C(0x9D, 0, handle, 0x1C);
    fn_8020104C(0x39, 0, handle, 0, lbl_8064EE58);
}

s32 fn_800A079C(Owner *owner)
{
    Vec3 pos;
    s32 result;
    EventState *event;
    void *object;
    s32 found;
    s32 room;
    s32 index;
    s32 handle;
    Vec3s *point;
    ActorData *actor;

    result = 0;
    if (lbl_8064D18C == 0x44 && lbl_803003C8.mode == 0) {
        object = fn_80201B9C();
        event = owner->event;
        found = 0;
        for (; object != 0; object = fn_80201BC0(object)) {
            room = fn_80201EB8(object);
            if (room == lbl_8064D18C && (actor = fn_80201B8C(object)) != 0 &&
                actor->kind == 0x97) {
                if (fn_80201B64(object) == 1) {
                    s32 handle = fn_80201B54(object);
                    fn_800A079C_start(handle);
                    result = 1;
                    event->timer = 5;
                }
                found = 1;
            }
        }
        if (owner->level >= 2) {
            if (event->timer == 0 && found == 0) {
                index = fn_8015C4A4(fn_801E741C(lbl_80245628), 2);
                if (index != -1) {
                    point = fn_80158ABC(index, 2, 0);
                    pos.x = point->x;
                    pos.y = point->y;
                    pos.z = point->z;
                    object = fn_8007091C(0x88, 0x97, 0x4B, lbl_8064D18C, &pos, lbl_8064EE5C);
                    if (object != 0) {
                        handle = fn_80201B54(object);
                        fn_8020123C(0x10, 0, handle, 0);
                        fn_800A079C_start(handle);
                        result = 1;
                        event->timer = 5;
                    }
                }
            } else if (event->timer != 0) {
                event->timer--;
            }
        }
    }
    return result;
}
