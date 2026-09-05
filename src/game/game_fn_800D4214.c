typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct State {
    u8 pad_00[0x64];
    u32 effect;
    u8 pad_68[0x1E];
    u16 kind;
} State;

extern void *fn_80201A84(void *);
extern void fn_8011F114();
extern u32 fn_80155330(int, void *, int, int, Vec3 *, int);
extern float lbl_8064F3B8;

void fn_800D4214(void *object, State *state)
{
    void *controller = fn_80201A84(object);
    Vec3 position;
    Vec3 source;
    int kind;

    fn_8011F114(&source, object);
    position = source;
    position.z += lbl_8064F3B8;

    kind = state->kind;
    switch (kind) {
    case 0:
        state->effect = fn_80155330(1, controller, 2, 14, 0, 0);
        break;
    case 1:
        state->effect = fn_80155330(2, controller, 2, 14, 0, 0);
        break;
    case 2:
        state->effect = fn_80155330(3, controller, 2, 14, &position, 250);
        break;
    case 3:
        break;
    }
}
