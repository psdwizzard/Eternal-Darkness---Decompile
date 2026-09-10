typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern float lbl_8064D7A0;
extern float fn_801F8FAC(Vec3*, void*, float);

void fn_801F7C04(void* state)
{
    Vec3 position;

    *(float*)((unsigned char*)state + 0x78) =
        fn_801F8FAC(&position, *(void**)((unsigned char*)state + 0x7C), lbl_8064D7A0);
    *(Vec3*)state = position;
}
