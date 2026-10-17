typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct ShortVec3 {
    short x, y, z;
} ShortVec3;

typedef struct QueryResult {
    int second, first;
    Vec3 position;
    u8 tail[0x14];
} QueryResult;

typedef struct State {
    u8 pad[0x58];
    u32 flags;
} State;

typedef struct ObjectData {
    u8 pad[0x8C];
    State *state;
} ObjectData;

typedef struct ModeState {
    u8 pad[8];
    int mode;
} ModeState;

extern int fn_80200C10(int *);
extern void *fn_80200C38(void **);
extern void *fn_80201BC8(void *);
extern int fn_80201B54(void *);
extern void *fn_80201B8C(void *);
extern void *fn_80201B3C(void);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, u8);
extern int fn_80201EB8(void *);
extern void fn_80201E78(void *, void *);
extern u64 fn_8020123C(int, int, int, int);
extern int fn_8006BE44(void);
extern void fn_801303F0(void *, int, int, float, float);
extern void fn_80130434(void *, int);
extern int fn_8011F6A4(void *, int, int, int, void *, int);
extern int fn_8012FF34(void *, Vec3 *, int, int);
extern void fn_801302BC(void *, int);
extern float fn_8012B7D0(const void *, const void *);
extern float fn_8012B750(void *);
extern void fn_8017A12C(float *, float, float);
extern void fn_801AC980(u32, int);
extern void fn_801795A4(Vec3 *, Vec3 *, Vec3 *);
extern void fn_80179A18(Vec3 *);
extern u32 fn_80178E94(const float *, const float *);
extern void *fn_801A82FC(u32);
extern int fn_8013B8C0(void *, void *);
extern u32 fn_8015C910(void);
extern void *fn_80153904(Vec3 *, Vec3 *, u16, float);
extern void fn_801798DC(Vec3 *, float);
extern void fn_80179E60(short *, float *);
extern void fn_80153050(void *, void *, u8, u8, u16, u16, u8 *, u8,
                       u16, short, u8, u8);
extern u16 fn_80050730(int, int, u8 *, u8 *, u16 *, u32 *);
extern int fn_801AAE68(u16, u8, u8, float, Vec3 *, signed char,
                      u8, u8, u16, u32);
extern int fn_800BE86C(void *, Vec3 *, int, int, float);
extern int fn_8015C4A4(u32, int);
extern int fn_80158B20(int, int, Vec3 *, Vec3 *, float *);
extern int fn_801B05E8(int, u8, u8, u8, Vec3 *, u8, int, int);

extern ModeState lbl_803003C8;
extern int lbl_8064B5C0;
extern u32 lbl_8064B5C4;
extern void *lbl_8064C4E4;
extern int lbl_8064C8F4;
extern u32 lbl_8064C8F8;
extern int lbl_8064C8FC;
extern int lbl_8064D18C;
extern int lbl_8064D5A8;
extern const float lbl_8064EA10;
extern const float lbl_8064EA14;
extern const float lbl_8064EA54;
extern const float lbl_8064EA90;
extern const u32 lbl_8064EB54;
extern const float lbl_8064EB58;
extern const float lbl_8064EB5C;
extern const float lbl_8064EB60;
extern const float lbl_8064EB64;
extern const float lbl_8064EB68;
extern const float lbl_8064EB6C;
extern const float lbl_8064EB70;

int fn_80087070(void *object, int phase, void **event)
{
    QueryResult playerQuery;
    QueryResult query;
    Vec3 playerPosition;
    Vec3 direction;
    Vec3 soundPosition;
    Vec3 ambientPosition;
    Vec3 fetchedPlayerPosition;
    Vec3 facingPosition;
    Vec3 fetchedSoundPosition;
    ShortVec3 effectDirection;
    float angle;
    u32 color;
    u8 soundFlags;
    u8 level;
    float facing;
    float magnitude;
    int kind;
    State *state;
    int objectId;
    void *runtime;
    int value;
    int ownerId;
    int blocked;
    void *other;
    u16 sound;
    int index;

    kind = fn_80200C10((int *)event);
    runtime = fn_80201BC8(object);
    objectId = fn_80201B54(object);
    state = ((ObjectData *)fn_80201B8C(object))->state;

    /* Event dispatch. */
    if (phase == 0) {
        if (kind == 1) {
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            lbl_8064C8F4 = 0;
            return 1;
        }
        if (kind == 0x3E) {
            lbl_8064B5C0 = 120;
            lbl_8064C8FC = 0;
            lbl_8064C8F8 = 0;
            return 1;
        }
        if (kind == 0x94) {
            if ((int)fn_80200C38(event) != 0) {
                value = state->flags | 2;
            } else {
                value = state->flags & ~2;
            }
            state->flags = value;
            return 1;
        }
        if (kind == 0x95) {
            if ((int)fn_80200C38(event) != 0) {
                value = state->flags | 1;
            } else {
                value = state->flags & ~1;
            }
            state->flags = value;
            return 1;
        }
        if (kind == 0x58) {
            ownerId = fn_80201EB8(object);
            value = (int)fn_80200C38(event);
            state->flags &= ~12U;
            if (ownerId == lbl_8064D18C && value != 0) {
                state->flags |= 4;
                if (value & 2) {
                    fn_801303F0(runtime, 0, 1, lbl_8064EB58, lbl_8064EB5C);
                    state->flags |= 8;
                } else {
                    fn_801303F0(runtime, 0, 1, lbl_8064EB60, lbl_8064EB5C);
                }
            }
            return 1;
        }
        if (kind == 0x1C) {
            if ((int)fn_80200C38(event) == 0) {
                if (fn_8006BE44() > 0 &&
                    (lbl_803003C8.mode == 7 || lbl_803003C8.mode == 0)) {
                    ownerId = fn_80201EB8(object);
                    if (ownerId == lbl_8064D18C) {
                        fn_8020123C(0x58, 0, objectId, 3);
                    }
                }
            } else if (lbl_803003C8.mode == 7 || lbl_803003C8.mode == 0) {
                ownerId = fn_80201EB8(object);
                if (ownerId == lbl_8064D18C) {
                    fn_80130434(runtime, 1);
                }
            }
            return 1;
        }
    } else if (phase == 1) {
        if (kind == 1) {
            lbl_8064B5C4 = 600;
            return 1;
        }
        if (kind == 3) {
            /* Apply pending movement, or request it for the active owner. */
            if (state->flags & 4) {
                ownerId = fn_80201EB8(object);
                if (ownerId == lbl_8064D18C &&
                    (!(lbl_8064D5A8 & 7) || (state->flags & 8))) {
                    if (fn_8011F6A4(fn_80201BC8(fn_80201B3C()), 0, 1, -1,
                                    &playerQuery, 1) != -1) {
                        if (fn_8012FF34(runtime, &playerQuery.position, 4, 2)) {
                            fn_801302BC(runtime, 16);
                        } else {
                            state->flags &= ~12U;
                        }
                    }
                    if (state->flags & 8) {
                        state->flags &= ~12U;
                    }
                }
            } else if (fn_8006BE44() > 0 &&
                       (lbl_803003C8.mode == 7 || lbl_803003C8.mode == 0)) {
                ownerId = fn_80201EB8(object);
                if (ownerId == lbl_8064D18C) {
                    fn_8020123C(0x58, 0, objectId, 1);
                }
            }

            /* Facing the player controls the effect and sound timers. */
            if (state->flags & 2) {
                fn_80201E78(&fetchedPlayerPosition, fn_80201B3C());
                /* Keep a separate facing-query copy of the player position. */
                facingPosition = playerPosition = fetchedPlayerPosition;
                facing = fn_8012B7D0(runtime, &facingPosition);
                fn_8017A12C(&angle, fn_8012B750(runtime), facing);
                magnitude = angle;
                lbl_8064B5C0 = lbl_8064B5C0 > 0 ? lbl_8064B5C0 - 1 : 0;
                if (magnitude < lbl_8064EA14) {
                    magnitude = -magnitude;
                }
                if (magnitude <= lbl_8064EB64) {
                    if (lbl_8064B5C0 == 0 && (state->flags & 1)) {
                        blocked = 0;
                        fn_8011F6A4(runtime, 2, 15, -1, &query, 1);
                        if (lbl_8064C8FC == 1 && lbl_8064C8F8 != 0) {
                            fn_801AC980(lbl_8064C8F8, 30);
                            lbl_8064C8FC = 0;
                            lbl_8064C8F8 = 0;
                        }
                        fn_801795A4(&playerPosition, &query.position, &direction);
                        direction.z = lbl_8064EA14;
                        fn_80179A18(&direction);
                        fn_80178E94(&playerPosition.x, &query.position.x);
                        other = fn_801A82FC(0x9436C407);
                        if (other != 0) {
                            blocked = fn_8013B8C0(lbl_8064C4E4, other);
                        }
                        if (fn_8015C910() == 0 && blocked == 0) {
                            color = lbl_8064EB54;
                            query.position.z += lbl_8064EA54;
                            fn_80153904(&query.position, &direction, 50, lbl_8064EB68);
                            fn_801798DC(&direction, lbl_8064EB6C);
                            fn_80179E60(&effectDirection.x, &direction.x);
                            fn_80153050(&query.position, &effectDirection, 10, 4, 10,
                                        10, (u8 *)&color, 1, 5, -1, 1, 200);
                            sound = fn_80050730(65, 0, &level, &soundFlags, 0, 0);
                            fn_801AAE68(sound, level, 0, lbl_8064EA90, &query.position,
                                        2, 2, 0, (u16)lbl_8064D18C, 0);
                        }
                        lbl_8064B5C0 = 120;
                    }
                } else {
                    fn_80201E78(&fetchedSoundPosition, object);
                    soundPosition = fetchedSoundPosition;
                    fn_800BE86C(runtime, &playerPosition, 15, 0, lbl_8064EB70);
                    if (lbl_8064C8FC == 0 && lbl_8064C8F8 == 0) {
                        lbl_8064C8F8 = fn_801AAE68(476, 100, 0, lbl_8064EA10,
                                                  &soundPosition, 1, 2, 0,
                                                  (u16)lbl_8064D18C, 0);
                        lbl_8064C8FC = 1;
                    }
                }
                if (lbl_8064B5C4 == 0) {
                    index = fn_8015C4A4(0x49423972, 2);
                    if (index != -1) {
                        fn_80158B20(index, 2, &ambientPosition, 0, 0);
                        fn_801B05E8(11, 100, 1, 1, &ambientPosition, 2, 0, 0);
                    }
                    lbl_8064B5C4 += 600;
                } else {
                    lbl_8064B5C4--;
                }
            } else {
                lbl_8064B5C4 = 600;
            }
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
