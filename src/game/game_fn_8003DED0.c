typedef unsigned int u32;
typedef signed short s16;
typedef unsigned short u16;
typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct EffectState {
    u32 flags;
    unsigned char padding[0x156];
    s16 countdown;
} EffectState;

typedef struct QueryResult {
    unsigned char header[8];
    Vec3 position;
    unsigned char trailing[20];
} QueryResult;

extern void *fn_801A717C(void);
extern int fn_80201B54(int *);
extern void fn_80201E78(void *, void *);
extern void fn_801A74A0(void *, u32);
extern void fn_801A74A8(void *, u32);
extern void fn_801A7538(void *, u16);
extern void fn_801A7518(void *, s16);
extern void fn_801A7470(void *, u32);
extern void fn_801A764C(void *, const Vec3 *);
extern void fn_801A7588(void *, u32);
extern u32 fn_801A74C0(void *);
extern u32 fn_801A74C8(void *, u32);
extern void fn_8020104C(int, int, int, int, float);
extern u32 fn_800FBFB0(void);
extern int fn_8011F6A4(void *, int, int, int, void *, int);
extern void fn_8014D478(void *, Vec3 *, float *, int, int, int *, int);
extern int lbl_802FC5BC[];
extern float lbl_8064E26C;
extern float lbl_8064E2D0;
extern float lbl_8064E2D4;

/* Instruction-identical to retail. MWCC's two generated signed-to-float
 * bias references use a local literal instead of shared lbl_8064E298. */
int fn_8003DED0(int *object, void *owner, EffectState *state)
{
    QueryResult query;
    Vec3 rotation;
    Vec3 position;
    void *effect;
    int handle;
    int result = 0;

    if (state->flags & 0x20000) {
        state->countdown = state->countdown > 0 ? state->countdown - 1 : 0;
        if (state->countdown == 0) {
            effect = fn_801A717C();
            handle = fn_80201B54(object);
            fn_80201E78(&position, object);
            fn_801A74A0(effect, handle);
            fn_801A74A8(effect, handle);
            fn_801A7538(effect, 1);
            fn_801A7518(effect, 5);
            fn_801A7470(effect, 11);
            fn_801A764C(effect, &position);
            fn_801A7588(effect, 0x8000);
            fn_801A74C8(effect, fn_801A74C0(effect) | 0x1000);
            fn_8020104C(0xED, handle, handle, (int)effect, lbl_8064E26C);
            state->countdown = (fn_800FBFB0() & 0x7F) + 0xEC;
            if (fn_8011F6A4(owner, 0, 1, -1, &query, 1) != -1) {
                position = query.position;
            } else {
                position.z += lbl_8064E2D0;
            }
            rotation.x = (float)(8 - (int)(fn_800FBFB0() & 0xF));
            rotation.y = (float)(8 - (int)(fn_800FBFB0() & 0xF));
            rotation.z = lbl_8064E2D4;
            fn_8014D478(owner, &position, &rotation.x, 3, 2, lbl_802FC5BC + 6, 3);
            result = 1;
        }
    }
    return result;
}
