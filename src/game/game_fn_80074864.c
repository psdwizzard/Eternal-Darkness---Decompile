typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

#pragma use_lmw_stmw on

typedef struct Info {
    u8 pad_00[0x3A];
    u8 value;
    u8 count;
    u8 limit;
} Info;

typedef struct State {
    u8 pad_00[0x1C0];
    u8 ready;
} State;

typedef struct World {
    u8 pad_00[0x44];
    State *state;
    u8 pad_48[0x48];
    void *info_handle;
} World;

typedef struct Status {
    u16 flags;
} Status;

extern unsigned int fn_800FBFB0(void);
#define fn_800FBFB0() ((int)fn_800FBFB0())
extern void *fn_80201B8C();
extern Info *fn_80072354(void *);
extern void fn_800360B0(void *, Status *);
extern int fn_80066D04(void *, int);

/* Randomized state-selection helper. The two-stage low-bit gate preserves the
 * original control-flow shape and MWCC callee-saved register allocation. */
int fn_80074864(void *object, void *unused, int *kind, u16 *count, u8 *value)
{
    int result;
    State *state;
    u8 *value_r;
    u16 *count_r;
    int *kind_r;
    void *object_r;
    Info *info;
    s8 limit;
    int random_value;
    World *world;
    Status status;

    object_r = object;
    kind_r = kind;
    count_r = count;
    value_r = value;
    random_value = fn_800FBFB0() % 100;
    *kind_r = -1;
    *value_r = 0;
    result = 0;
    world = fn_80201B8C(object_r);
    state = world->state;
    info = fn_80072354(world->info_handle);
    fn_800360B0(object_r, &status);
    limit = info->limit;
    if (fn_80066D04(object_r, 3) == 0) {
        status.flags |= 1;
    }
    if (fn_80066D04(object_r, 2) == 0) {
        status.flags |= 2;
    }
    if ((status.flags & 0x80) != 0) {
        goto done;
    }
    if ((status.flags & 1) == 0) {
        goto select;
    }
    if ((status.flags & 1) != 0) {
        goto done;
    }
select:
    if (random_value <= limit || state->ready != 0) {
        *kind_r = 7;
        result = 1;
        *value_r = info->value;
        *count_r = info->count;
        state->ready = 0;
    }
done:
    return result;
}
