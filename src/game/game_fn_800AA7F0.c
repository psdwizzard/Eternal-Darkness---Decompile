typedef struct Vec3i { int x, y, z; } Vec3i;

typedef struct Effect {
    unsigned char pad0[4];
    int handle;
    int owner;
    int fieldC;
    unsigned char pad10[0xC];
    Vec3i position;
    int value;
    unsigned short kind;
    unsigned char pad2E[8];
    unsigned char flag36;
    unsigned char pad37;
    unsigned char mode;
    unsigned char pad39[0xF];
    void* callback;
} Effect;

extern float lbl_8064EF18;
extern float lbl_8064EF78;
extern void fn_8014CBC0(Effect*);
extern int fn_800AA6F4(void*);
extern void fn_801FE8DC(int*, void*, float, float, float);
extern int fn_801E8328();

void fn_800AA7F0(Effect* effect, Vec3i* position, int* value, int kind,
                 int flag, int owner)
{
    if (effect != 0) {
        float first;
        float second;
        float third;

        fn_8014CBC0(effect);
        effect->handle = 0;
        first = lbl_8064EF18;
        third = lbl_8064EF78;
        effect->position = *position;
        second = first;
        effect->value = *value;
        effect->callback = fn_800AA6F4;
        effect->kind = kind;
        effect->flag36 = flag;
        effect->fieldC = 0;
        effect->owner = owner;
        effect->mode = 2;
        fn_801FE8DC(&effect->handle, fn_800AA6F4, first, second, third);
        fn_801E8328(0x13, effect);
    }
}
