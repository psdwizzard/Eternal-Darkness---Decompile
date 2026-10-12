typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;

typedef struct Counters {
    u8 padding[0x1C];
    s16 first;
    s16 second;
} Counters;

typedef struct ActorState {
    u8 padding[0x167];
    u8 count;
} ActorState;

typedef struct Actor {
    u8 padding[0x8C];
    ActorState *state;
} Actor;

extern int fn_80201B54(int *);
extern unsigned int fn_8011FAEC(void *);
extern unsigned int fn_8011FA8C(void *, unsigned int, unsigned int);
extern u16 fn_8012DBE8(u8 *, unsigned int, u8 *);
extern void fn_800BE8D4(int);
extern u8 fn_8013017C(void *);
extern int fn_801305D4(void *);
extern int fn_801301B0(void *, u8, u8);
extern void *fn_8012C62C(u8 *, int, void *, signed char *, void *, int);
extern int lbl_8064C55C;
extern const int lbl_8064F590;
extern const int lbl_8064F594;
extern const int lbl_80651B04;

void fn_800DFF70(int *object, u8 *resource, Actor *actor,
                 Counters *counters, int *first_delay, int *second_delay)
{
    u8 color[4];
    int start;
    int end;
    int value;
    int owner = fn_80201B54(object);
    unsigned int flags = fn_8011FAEC(resource);

    counters->first = counters->first <= 1 ? 0 : counters->first - 1;
    counters->second = counters->second <= 1 ? 0 : counters->second - 1;
    *first_delay = *first_delay > 0 ? *first_delay - 1 : 0;
    *second_delay = *second_delay > 0 ? *second_delay - 1 : 0;
    if (flags & 0x10) {
        fn_8011FA8C(resource, 0x10, 0);
        actor->state->count++;
    }
    fn_8012DBE8(resource, 15, color);
    if (color[3] < 20) {
        fn_800BE8D4(owner);
    }
    if ((fn_8013017C(resource) & 0x40) && fn_801305D4(resource) == 0) {
        fn_801301B0(resource, 0x40, 0);
    }
    if (lbl_8064C55C != 0) {
        value = lbl_8064F594;
        end = lbl_80651B04;
        start = lbl_8064F590;
        fn_8012C62C(resource, 15, &start, (signed char *)&end, &value, 4);
    }
}
