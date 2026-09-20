typedef unsigned char u8;
typedef signed short s16;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Resource {
    u8 pad[0x2C];
    int slots[3];
} Resource;

typedef struct RuntimeState {
    u8 pad[0x2C];
    void *payload;
    u8 pad30[0x5C];
    Resource *resource;
} RuntimeState;

typedef struct Payload {
    u8 flags;
    u8 pad01[7];
    int first;
    int second;
    int fourth;
    s16 fifth;
    u8 pad16[6];
    void *third;
    void *eighth;
    Vec3 position;
} Payload;

extern void *fn_80201814(int);
extern void *fn_80201B8C(void *);
extern int fn_80201B44(RuntimeState *);
extern unsigned long long fn_8020123C(int, int, int, int);
extern void *fn_80037AF4(int);
extern int fn_80201B54(void *);
extern void fn_802015A4(void *);
extern int fn_801E8328(int, void *);
extern void fn_8020104C(int, void*, void*, int, float);
#define fn_8020104C(a,b,c,d,e) fn_8020104C((int)(a),(void*)(b),(void*)(c),(int)(d),(float)(e))

#pragma use_lmw_stmw on
void *fn_800CD6C0(int argFirst, int argSecond, void *argThird, u8 argFlags,
                  int argFourth, s16 argFifth, Vec3 *argPosition, float time,
                  void *argEighth)
{
    void *object = 0;
    RuntimeState *state = 0;
    int slot = 0;
    int id;
    void *resolved;
    Payload *payload;

    resolved = fn_80201814(argFirst);
    if (resolved != 0) {
        state = ((RuntimeState *)fn_80201B8C(resolved));
        if (argFirst == fn_80201B44(state)) {
            id = state->resource->slots[0];
            if (id != 0) {
                fn_8020123C(0x39, id, id, 0);
            }
            slot = 0;
        } else {
            for (slot = 0; slot < 3; ++slot) {
                id = state->resource->slots[slot];
                if (id == 0) {
                    break;
                }
            }
        }
    }
    if (slot < 3) {
        object = fn_80037AF4(0x19);
        id = fn_80201B54(object);
        if (state != 0) {
            state->resource->slots[slot] = id;
        }
        payload = (Payload *)((RuntimeState *)fn_80201B8C(object))->payload;
        payload->flags = argFlags;
        payload->first = argFirst;
        payload->second = argSecond;
        payload->fourth = argFourth;
        payload->fifth = argFifth;
        payload->third = argThird;
        payload->position = *argPosition;
        payload->eighth = argEighth;
        fn_802015A4(object);
        fn_801E8328(0x15, object);
        if ((payload->flags & 6) == 0) {
            fn_8020104C(0x39, id, id, 0, time);
        }
    }
    return object;
}
