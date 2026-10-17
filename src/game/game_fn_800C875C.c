typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Color {
    u8 r, g, b, a;
} Color;

typedef struct RuntimeState {
    u32 first;
    u32 second;
    u8 pad[0xC];
    u32 owner;
    u8 active;
    u8 pending;
    u16 mode;
} RuntimeState;

typedef struct ActorData {
    u8 pad0[0x6C];
    RuntimeState *state;
    u8 pad70[0x1C];
    u8 *extra;
} ActorData;

typedef struct SoundParams {
    u8 data[0xC4];
} SoundParams;

extern int fn_80200C10(void *);
extern int fn_80200C20(void *);
extern int fn_80200C28(void *);
extern int fn_80200C38(void *);
extern void *fn_80201B3C(void);
extern int fn_80201B44(void);
extern int fn_80201B54(void *);
extern ActorData *fn_80201B8C(void *);
extern int fn_80201B94(void *);
extern void *fn_80201BC8(void *);
extern int fn_80201C48(int);
extern void *fn_80201814(int);
extern void fn_80201D14(void *, int);
extern void fn_80201D1C(void *, int);
extern void fn_80201D2C(void *, int);
extern void fn_80201D34(void *, int);
extern void fn_802006D4(int, int, int, int, int);
extern void fn_8020104C(int, int, int, int, float);
extern void fn_8020123C(int, int, int, int);
extern void fn_802045AC(void *, Vec3 *);
extern void fn_80204FDC(void *);
extern void fn_80211A6C(Vec3 *, Vec3 *, Vec3 *);
extern float fn_80211B08(Vec3 *);
extern void fn_8011F114(Vec3 *, void *);
extern void fn_8011F778(void *, float);
extern void fn_8011FA8C(void *, int, int);
extern void fn_8011FABC(void *, int, int);
extern void fn_8011FADC(void *, u32);
extern u32 fn_8011FAEC(void *);
extern void fn_8011FB5C(void *, int);
extern void fn_80128E30(void *);
extern void fn_801294DC(void *, int, int, int);
extern void fn_8012976C(void *, int, int, Vec3 *, float);
extern void fn_80129928(void *, Vec3 *);
extern void fn_80129BA4(float, float);
extern int fn_8012AFC4(void *);
extern void fn_8012B324(void *);
extern void fn_8012B344(void *);
extern void fn_8012B750(void *);
extern void fn_8012B7A0(void *);
extern float fn_8012B7D0(void *, Vec3);
extern void fn_8012C62C(void *, int, Color, Color, Color, int);
extern void fn_80149220(SoundParams *, u32 *);
extern u32 fn_80149D48(u32, int);
extern int fn_80179064(int, int, int, int);
extern void fn_801850CC(u32);
extern u32 fn_801A717C(void);
extern void fn_801A7228(u32);
extern void fn_801A7478(u32, SoundParams *);
extern u8 *fn_801A7480(u32);
extern void fn_801A74A0(u32, int);
extern void fn_801A74D8(u32, int);
extern void fn_801A7518(u32, int);
extern void fn_801A7538(u32, int);
extern void fn_801A7588(u32, int);
extern u32 fn_801AC8AC(int, int, int, Vec3 *);
extern int fn_801AC908(u32, Vec3 *, int);
extern void fn_801AC980(u32, int);
extern u32 fn_801D3974(int);
extern void fn_801E8328(int, void *);
extern void fn_80064B38(void *, void *, int *);
extern void fn_800C3ADC(void *, u32);
extern int fn_800C91F8(void *, void *);
extern void fn_800C9268(RuntimeState *);
extern void fn_800C92E8(void *);
extern int fn_800C9354(void *, void *, void *);
extern int fn_800C9450(void *, int);
extern void fn_800CA2C8(void *);
extern void fn_800CC4DC(void *);
extern void *memset(void *, int, u32);

extern SoundParams lbl_80325200[];
extern int lbl_8064CA98;
extern u32 lbl_8064D5A8;
extern Color lbl_8064F254;
extern Color lbl_8064F258;
extern Color lbl_8064F25C;
extern Color lbl_8064F260;
extern Color lbl_8064F264;
extern const float lbl_8064F268;
extern const float lbl_8064F26C;
extern const float lbl_8064F270;
extern const float lbl_8064F274;
extern const float lbl_8064F278;
extern const float lbl_8064F27C;
extern const float lbl_8064F280;
extern const float lbl_8064F284;
extern Color lbl_80651A70;

int fn_800C875C(void *context, int phase, void *message, int *result)
{
    int kind;
    void *targetObject;
    void *target;
    RuntimeState *state;
    ActorData *data;
    u8 *extra;
    int link;
    void *object;
    int id;
    int partner;
    Vec3 position;
    Vec3 targetPosition;
    Vec3 delta;
    Vec3 goal;

    kind = fn_80200C10(message);
    targetObject = 0;
    target = fn_80201B3C();
    object = fn_80201BC8(context);
    data = fn_80201B8C(context);
    extra = data->extra;
    link = fn_80201B94(context);
    id = fn_80201B54(context);
    fn_8011F114(&position, object);
    state = data->state;
    if ((partner = fn_80201B44()) != 0) {
        targetObject = fn_80201BC8(fn_80201814(partner));
        fn_8011F114(&targetPosition, targetObject);
    }

    if (kind == 3) {
        fn_800CC4DC(context);
        fn_800C92E8(context);
        if (targetObject != (void *)0) {
            fn_800C91F8(object, targetObject);
        }
        if (!(lbl_8064D5A8 & 3)) {
            void *other = fn_80201814(*(int *)(extra + 0xBC));
            if (other != (void *)0 && fn_800C9354(context, target, other) != 0) {
                fn_8020104C(0x39, id, id, 0, lbl_8064F268);
            }
        }
        if (fn_801AC908(state->owner, &position, 0xFF) == 0) {
            state->owner = fn_801AC8AC(0x24D, 0x6E, 0x1388, &position);
        }
        if (!(state->pending & 1) && state->first != 0) {
            u8 *sound = fn_801A7480(state->first);
            if (sound != 0 && *(u32 *)(sound + 0xC0) != 0) {
                u32 voice = fn_80149D48(*(u32 *)(sound + 0xC0), 0);
                if (voice != 0) {
                    state->second = voice;
                    state->pending |= 1;
                }
            }
        }
    }

    if (phase == 0) {
        if (kind == 1) {
            Color a = lbl_8064F254;
            Color b = lbl_8064F258;
            Color c = lbl_8064F25C;
            SoundParams *params;
            u32 info;
            fn_800C9268(state);
            fn_8012B7D0(object, targetPosition);
            fn_8012B7A0(object);
            fn_8011FB5C(object, 0x20000);
            fn_8011F778(object, lbl_8064F26C);
            fn_8011FA8C(object, 0, 0x802);
            state->first = fn_801A717C();
            fn_801A74A0(state->first, id);
            fn_801A7538(state->first, 5);
            fn_801A7518(state->first, 5);
            fn_801A7588(state->first, 0x8000);
            lbl_8064CA98++;
            lbl_8064CA98 %= 3;
            params = &lbl_80325200[lbl_8064CA98];
            memset(params, 0, sizeof(SoundParams));
            fn_801A74D8(state->first, 0x4000);
            fn_801A7478(state->first, params);
            fn_800C3ADC(object, state->first);
            info = fn_801D3974(2);
            ((u8 *)&info)[3] = 0x9C;
            fn_80149220(params, &info);
            fn_8011FA8C(object, 0, 0x100);
            fn_8011FABC(object, 0, 0x6000);
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (kind == 0x27) {
            fn_80064B38(context, message, result);
            return 1;
        }
        if (kind == 0x65) {
            fn_80200C38(message);
            if (result != 0) {
                *result = 1;
            }
            return 1;
        }
        if (kind == 0x3B) {
            fn_80200C38(message);
            if (result != 0) {
                *result = 1;
            }
            return 1;
        }
        if (kind == 0xEF) {
            if (result != 0) {
                *result = 1;
            }
            return 1;
        }
        if (kind == 8) {
            fn_8012B324(object);
            fn_8020104C(0x39, id, id, 1, lbl_8064F270);
            return 1;
        }
        if (kind == 0x82) {
            return 1;
        }
        if (kind == 0xED) {
            fn_801A7228(fn_80200C38(message));
            return 1;
        }
        if (kind == 0x3A) {
            fn_8020123C(0x27, fn_80200C20(message), fn_80200C28(message), fn_80200C38(message));
            fn_801A7228(fn_80200C38(message));
            return 1;
        }
        if (kind == 0xB) {
            fn_8012B344(object);
            fn_8020104C(0x39, id, id, 1, lbl_8064F270);
            if (result != 0) {
                *result = 0;
            }
            return 1;
        }
        if (kind == 0x35) {
            return 1;
        }
        if (kind == 0x39) {
            int flag = fn_80200C38(message) & 1;
            fn_801AC980(state->owner, 1);
            state->owner = 0;
            if (*(int *)(extra + 0xBC) != 0) {
                fn_8020123C(0x91, id, *(int *)(extra + 0xBC), 0);
            }
            if (flag != 0) {
                fn_800C9450(context, 0xD2);
            }
            fn_8012B324(object);
            if (state->second != 0) {
                fn_801850CC(state->second);
                state->second = 0;
                fn_801A7478(state->first, 0);
            }
            fn_801A7228(state->first);
            fn_80201D34(context, 0);
            fn_80201D1C(context, 1);
            fn_801E8328(2, context);
            return 1;
        }
        if (kind == 0xD5) {
            *(int *)(extra + 0xBC) = fn_80200C38(message);
            return 1;
        }
    } else if (phase == 1) {
        if (kind == 3) {
            if (fn_8011FAEC(object) & 0x10) {
                fn_8020104C(0x39, id, id, 1, lbl_8064F270);
            } else if (partner != 0) {
                float distance;
                if (state->mode != 0) {
                    state->mode--;
                    if (state->mode == 0) {
                        /* ASM: nop -- stripped assertion in the empty branch; C cannot emit it */
                        asm { nop }
                    }
                }
                fn_80211A6C(&position, &targetPosition, &delta);
                distance = fn_80211B08(&delta);
                if (distance <= lbl_8064F274) {
                    if (fn_800C9450(context, 0xD2) != 0) {
                        fn_8020123C(0x39, id, id, 0);
                    }
                } else {
                    if (distance < lbl_8064F278 && state->mode == 0) {
                        state->active = 0;
                    }
                    if (state->mode != 0 || (state->active != 0 && distance >= lbl_8064F278)) {
                        float facing = fn_8012B7D0(object, targetPosition);
                        fn_8012B750(object);
                        fn_80128E30(object);
                        fn_80129BA4(facing, lbl_8064F27C);
                    }
                }
            }
            return 1;
        }
        if (kind == 0x91) {
            fn_801294DC(object, 2, 0x121, 1);
            if (result != 0) {
                *result = 1;
            }
            fn_80201D2C(context, 3);
            fn_80201D14(context, 1);
            return 1;
        }
    } else if (phase == 3) {
        if (kind == 1) {
            fn_801294DC(object, 2, 0x121, 1);
            state->active = 1;
            state->mode = 0x1E;
            return 1;
        }
        if (kind == 3) {
            int handle;
            if ((handle = fn_80201C48(link)) != 0 && fn_80201814(handle) != 0) {
                int done = 0;
                int range;
                fn_802045AC(context, &goal);
                range = fn_80179064((int)position.x, (int)position.y, (int)goal.x, (int)goal.y);
                if (range <= 0xA0 && fn_800C9450(context, 0xD2) != 0) {
                    fn_8020123C(0x39, id, id, 0);
                }
                if (done == 0 && range > lbl_8064F280) {
                    if (fn_8012AFC4(object) != 0) {
                        fn_80129928(object, &goal);
                    } else {
                        fn_8012976C(object, 2, 0x21, &goal, lbl_8064F284);
                    }
                }
            } else {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
            return 1;
        }
        if (kind == 0x66) {
            fn_8012B344(object);
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
    } else if (phase == 8) {
        if (kind == 1) {
            if (object != 0) {
                fn_8011FADC(object, fn_8011FAEC(object) & ~0xC0);
            }
            fn_800CA2C8(context);
            fn_80204FDC(context);
            return 1;
        }
        if (kind == 0x3D) {
            fn_8020123C(0x39, id, id, 0);
            return 1;
        }
        if (kind == 0x11) {
            Color c = lbl_80651A70;
            Color b = lbl_8064F264;
            Color a = lbl_8064F260;
            fn_8012C62C(object, 0xF, a, b, c, 0x14);
            fn_80201D34(context, 0x15);
            fn_80201D1C(context, 1);
            return 1;
        }
        if (kind == 2) {
            fn_802006D4(id, id, 8, 0x11, 0);
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
