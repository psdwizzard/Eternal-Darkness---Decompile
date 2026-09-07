typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct DrawState {
    u32 words[8];
} DrawState;

extern DrawState lbl_8023B6A8;
extern void fn_801ECC4C(void);
extern void fn_801ED468(int);
extern void fn_801EDA7C(void*, int, int, int);
extern void fn_801ECF50(int);
extern void fn_80226AB4(int, int, int);
extern void fn_801E7BDC(float, float, float);
extern void fn_801E7BD8(void);

void fn_801E7CBC(Vec3* a, Vec3* b, Vec3* c, Vec3* d, u32* value)
{
    DrawState state = lbl_8023B6A8;

    fn_801ECC4C();
    fn_801ED468(0x1B);
    state.words[6] = 0x80000000;
    state.words[7] = *value;
    fn_801EDA7C(&state, 0, 0x2BF, 0);
    fn_801ECF50(4);
    fn_80226AB4(0x80, 3, 4);
    fn_801E7BDC(a->x, a->y, a->z);
    fn_801E7BDC(b->x, b->y, b->z);
    fn_801E7BDC(c->x, c->y, c->z);
    fn_801E7BDC(d->x, d->y, d->z);
    fn_801E7BD8();
}
