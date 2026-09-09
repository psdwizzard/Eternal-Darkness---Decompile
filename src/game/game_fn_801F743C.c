typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct State {
    Vec3 position;
    unsigned char pad0c[0x24];
    float divisor;
    unsigned char pad34[0x3C];
    Vec3* reference;
} State;

int fn_801F743C(State* state)
{
    int x = (int)((state->position.x - state->reference->x) / state->divisor);
    int y = (int)((state->position.y - state->reference->y) / state->divisor);
    int z = (int)((state->position.z - state->reference->z) / state->divisor);

    if (x == 0 && y == 0 && z == 0) {
        return 1;
    }
    return 0;
}
