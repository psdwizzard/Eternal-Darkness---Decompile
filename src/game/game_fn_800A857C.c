typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct PursuitState {
    int kind;
    int field4;
    int idleTimer;
    int resetTimer;
    int actionTimer;
    int actionDelay;
    int startDelay;
    int field1C;
    int searchDelay;
    int attempts;
    u8 pad28[0x18];
    u16 flags;
    s8 type;
} PursuitState;

typedef struct ActorInfo {
    u8 pad00[0x8C];
    void* actor;
} ActorInfo;

typedef struct ActorData {
    u8 pad00[0x24];
    int active;
} ActorData;

extern int fn_800AD3A4(void);
extern int fn_800A83DC(void*, void*, void*, int, PursuitState*);
extern int fn_800359A0(void*, void*);
extern void* fn_80201B3C(void);
extern void* fn_8011F130(void*);
extern void* fn_80201B94(void*);
extern void* fn_80201C48(void*);
extern void* fn_80201814(int);
extern int fn_802045AC(void*, Vec3*);
extern u8 fn_80204578(void*, const Vec3*);
extern int fn_80179064(int, int, int, int);
extern float fn_800CB444(void*, void*);
extern u32 rand(void);
extern int fn_8012AFC4(void*);
extern void fn_8012B344(void*);
/* Retail passes unused trailing arguments to these legacy callees. */
extern int fn_800A7A68();
extern void fn_800A7F8C();
extern void fn_8016B400(int, void*, void*);
extern int fn_80038308(void*, int, short*);
extern int fn_801D1A7C();
extern float fn_801790A4(float, float, float, float);
extern void fn_80201D2C(void*, int);
typedef struct Object80201D14 Object80201D14;
extern void fn_80201D14(Object80201D14*, unsigned char);
extern void* fn_80201B8C(void*);
extern int fn_800CD84C(void*);
extern void fn_800A821C();

extern void* lbl_8064C4E4;
extern void* lbl_8064C980;
extern void* lbl_8064C988;
extern void* lbl_8064C990;
extern float lbl_8064EF38;
extern const volatile u32 lbl_80239768[4];

int fn_800A857C(void* object, void* source, void* extra, int objectId,
                PursuitState* state)
{
    int ready;
    Vec3 targetPosition;
    int thresholds[4];
    int possibleEvents[2];
    short channel;
    Vec3* position;
    Vec3* otherPosition;
    void* target;
    void* player;
    void* resolvedTarget;
    int distance;

    if (fn_800AD3A4() != 0) {
        return 0;
    }

    ready = fn_800A83DC(object, source, extra, objectId, state);
    if (ready != 0) {
        if (state->type != 1 && state->type != 2 && state->type != 3) {
            goto fallback;
        }

        if (!(state->flags & 1)) {
            state->flags |= 1;
            fn_8016B400(0x8B6, lbl_8064C980, 0);
            goto fallback;
        }
        if (state->startDelay != 0) {
            state->startDelay--;
            goto fallback;
        }
        if (state->actionTimer == 0 && state->idleTimer == 0) {
            goto fallback;
        }
        player = fn_80201B3C();
        if (fn_800359A0(object, player) == 0) {
            goto fallback;
        }

        position = fn_8011F130(source);
        target = fn_80201B94(object);
        target = fn_80201C48(target);
        resolvedTarget = fn_80201814((int)target);
        fn_802045AC(object, &targetPosition);
        distance = fn_80179064((int)position->x, (int)position->y,
                               (int)targetPosition.x, (int)targetPosition.y);

        if (distance < (int)fn_800CB444(object, resolvedTarget) &&
            fn_80204578(object, &targetPosition) != 0) {
            thresholds[0] = lbl_80239768[0];
            thresholds[1] = lbl_80239768[1];
            thresholds[2] = lbl_80239768[2];
            thresholds[3] = lbl_80239768[3];
            if ((u8)rand() < thresholds[state->type]) {
                state->actionTimer = 0;
                goto fallback;
            }
            state->startDelay = state->actionDelay;
            if (fn_8012AFC4(source) != 0) {
                fn_8012B344(source);
            }
            if (state->attempts > 0) {
                state->attempts--;
                return fn_800A7A68(object, source, extra);
            }
            state->attempts = 5;
            fn_800A7F8C(objectId, position, 0x19, 1);
            return 1;
        }

        if (state->searchDelay != 0) {
            state->searchDelay--;
            goto fallback;
        }

        position = fn_8011F130(source);
        otherPosition = fn_8011F130(lbl_8064C4E4);
        fn_80038308(fn_80201814((int)lbl_8064C990), 0, &channel);
        if (state->idleTimer == 0 && fn_801D1A7C(lbl_8064C988) == 0) {
            fn_800A821C(0x300, lbl_8064C988, object, source, state, extra);
            goto fallback;
        }
        if (state->idleTimer == 0 && (rand() & 1) &&
            fn_801790A4(position->x, position->y, otherPosition->x,
                          otherPosition->y) > lbl_8064EF38) {
            fn_800A821C(0x500, 0, object, source, state, extra);
            goto fallback;
        }
        fn_80201D2C(object, 3);
        fn_80201D14(object, 1);
        return 1;
    }

fallback:
    if (ready != 0 && state->idleTimer == 0) {
        if (state->actionTimer == 0) {
            fn_800A821C(0x500, 0, object, source, state, extra);
            state->actionTimer = state->resetTimer;
        } else if ((int)(u8)state->type == 3) {
            int count;
            count = 0;
            if (((ActorData*)((ActorInfo*)fn_80201B8C(object))->actor)->active == 0) {
                possibleEvents[0] = 0x1010;
                count = 1;
            }
            if (fn_800CD84C(object) == 0) {
                possibleEvents[count++] = 0x410;
            }
            if (count != 0) {
                fn_800A821C(possibleEvents[(count - 1) & rand()],
                              0, object, source, state, extra);
            } else {
                state->idleTimer = 0x3C;
            }
        }
    }
    return 0;
}
