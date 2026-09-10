typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern void fn_801F7E40(Vec3*, void*, float);

#pragma opt_propagation off
void fn_801F7FBC(void* state)
{
    Vec3 result;
    float amount = *(float*)((unsigned char*)state + 0x38);
    void* target = *(void**)((unsigned char*)state + 0x68);

    fn_801F7E40(&result, target, amount);
    *(Vec3*)state = result;
}
#pragma opt_propagation reset
