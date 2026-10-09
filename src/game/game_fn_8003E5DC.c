typedef signed char s8;
typedef unsigned char u8;

typedef struct ActorState {
    u8 pad[0x162];
    s8 facing;
} ActorState;

extern const float lbl_8064E27C;
extern const float lbl_8064E2D8;

extern void fn_80121104(void *object, float value);
extern float fn_8012110C(void *object);

void fn_8003E5DC(void *context, void *object, int owner, ActorState *actor)
{
    float value = fn_8012110C(object);

    if (actor->facing != 0) {
        value += lbl_8064E27C;
    } else {
        value -= lbl_8064E27C;
    }

    if (value > lbl_8064E2D8) {
        actor->facing = 0;
    }
    if (value < lbl_8064E27C) {
        actor->facing = 1;
    }

    fn_80121104(object, value);
}
