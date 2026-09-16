typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Color { u8 r, g, b, a; } Color;
typedef struct Vec3f { float x, y, z; } Vec3f;
typedef struct QueryResult {
    u8 pad00[8];
    Vec3f position;
    u8 pad14[0x14];
} QueryResult;
typedef struct EffectDesc { u8 bytes[0x90]; } EffectDesc;
typedef struct Work {
    u8 pad00[8];
    void* object;
    u8 timer;
    u8 index;
    u8 count;
    u8 initialized;
    u8 pad10[0x1314];
    int token;
} Work;

extern int lbl_8064D18C;
extern Color lbl_80651C80;
extern Color lbl_806505F0;
extern u32 lbl_806505F4;
extern u16 lbl_806505F8;
extern float lbl_806505FC;
extern void fn_80149E28(void*);
extern void fn_8011F114(Vec3f*, void*);
extern unsigned short fn_8012DBE8(void*, int, Color*);
extern void* fn_8012C62C(void*, int, Color*, Color*, Color*, int);
extern void fn_801A19BC(EffectDesc*);
extern unsigned int fn_800FBFB0(void);
#define fn_800FBFB0() ((int)fn_800FBFB0())
extern int fn_8011F598(void*, int, int, int, QueryResult*, int);
extern void* fn_80148008(Vec3f*, void*, EffectDesc*, void*);
extern void fn_801A1BD0(void);
extern void *fn_80156938();
extern void fn_80180374(void*, int);
extern void fn_80180384(void*, int);

void fn_801547CC(void* work)
{
    Work* state = work;
    void* object;
    u8 index;
    Color source, first, second, third, temporary, solid;
    Vec3f initial_position;
    QueryResult result;
    u8 key[6];
    EffectDesc desc;
    Vec3f position;
    void* effect;

    object = state->object;

    if (state->token != lbl_8064D18C) {
        fn_80149E28(state);
        return;
    }
    if (state->initialized == 0) {
        index = state->index;
        fn_8011F114(&initial_position, object);
        fn_8012DBE8(object, index, &source);
        temporary = lbl_80651C80;
        temporary.r = source.r;
        temporary.g = source.g;
        temporary.b = source.b;
        solid = lbl_806505F0;
        third = temporary;
        second = solid;
        first = source;
        fn_8012C62C(object, index, &first, &second, &third, 6);
        state->initialized = 1;
        state->timer = 0;
    }
    if (state->timer == 0) {
        *(u32*)key = lbl_806505F4;
        *(u16*)(key + 4) = lbl_806505F8;
        index = state->index;
        fn_801A19BC(&desc);
        *(u16*)(desc.bytes + 6) = 80;
        *(float*)(desc.bytes + 20) = lbl_806505FC;
        desc.bytes[25] = (fn_800FBFB0() + 45) & 31;
        fn_8011F598(object, state->count, index, -1,
                     &result, 1);
        position = result.position;
        effect = fn_80148008(&position, key, &desc, fn_801A1BD0);
        if (effect != 0 && (effect = fn_80156938(effect)) != 0) {
            fn_80180374(effect, 255);
            fn_80180384(effect, 20);
        }
        state->count += 1;
        state->timer = (fn_800FBFB0() + 1) & 7;
    } else {
        state->timer -= 1;
    }
    if (state->count == 14)
        fn_80149E28(state);
}
