typedef unsigned char u8;
typedef unsigned int u32;

#pragma use_lmw_stmw on

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct State {
    u8 pad_00[0x44];
    struct State *owner;
    u8 pad_48[0x16C];
    void *handle;
    u8 pad_1B8[0x0B];
    u8 active;
} State;

extern int fn_80128EAC(void *);
extern void *fn_801A7498(void *);
extern void *fn_801A7490(void *);
extern void fn_8011F114();
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void *fn_80201B8C();
extern int fn_80074440(void *, void *, State *, Vec3 *);
extern void fn_80129BE4(void *);
extern int fn_80074310(void *, Vec3 *, State *, Vec3 *);
extern void fn_8011F6F0(void *);
extern void *fn_80137E60(void *, Vec3 *);
extern unsigned long long fn_8020123C();

/* NonMatching: behavior-complete paired-object setup and routing. Retail and
 * base have the same size and 15 call relocations; the remaining differences
 * are MWCC's callee-saved register assignments. */
int fn_800741E8(void *object, void *link)
{
    register void *resolved_second;
    void *second;
    register void *first;
    register State *state;
    void *resolved_value;
    void *resolved_final;
    Vec3 position;
    Vec3 result;
    int found;

    resolved_second = link;
    if (fn_80128EAC(object) == 7) {
        first = fn_801A7498(resolved_second);
        second = fn_801A7490(resolved_second);
        fn_8011F114(&position, object);
        resolved_value = fn_80201814(second);
        resolved_second = fn_80201814(first);
        resolved_final = fn_80201BC8(resolved_value);
        state = ((State *)fn_80201B8C(resolved_second))->owner;
        found = fn_80074440(object, resolved_final, state, &result);
        fn_80129BE4(object);
        if (found != 0) {
            state->active = 1;
            fn_80074310(object, &position, state, &result);
            fn_8011F6F0(object);
            state->handle = fn_80137E60(object, &position);
        } else {
            fn_8020123C(0x74, first, second, 0);
            fn_8020123C(0x74, first, first, 0);
        }
    }
    return 1;
}
