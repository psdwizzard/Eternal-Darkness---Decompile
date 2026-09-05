typedef struct EffectState {
    unsigned char pad[0xC];
    int value;
    int primary;
    int secondary;
} EffectState;

extern unsigned long long fn_8020123C();

void fn_8008E810(int object_id, EffectState* state)
{
    int target = state->primary;
    switch (target) {
    case 0:
        target = state->secondary;
        break;
    default:
        break;
    }
    fn_8020123C(126, object_id, target, 0);
    fn_8020123C(122, object_id, state->value, 0);
    state->primary = 0;
    state->value = 0;
    state->secondary = 0;
}
