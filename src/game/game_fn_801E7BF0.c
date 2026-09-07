typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern void fn_801ECC4C(void);
extern void fn_801ED468(int);
extern void fn_801EDA7C(void*, int, int, int);
extern void fn_801ECD74(void*);
extern void fn_801ECF50(int);
extern void fn_80226AB4(int, int, int);
extern void fn_801E7BDC(float, float, float);
extern void fn_801E7BD8(void);
extern u32 lbl_802FC53C[];

void fn_801E7BF0(Vec3* a, Vec3* b, Vec3* c, u32* value)
{
    u32 local;

    fn_801ECC4C();
    fn_801ED468(0x1B);
    fn_801EDA7C(lbl_802FC53C, 0, 0x2BF, 0);
    local = *value;
    fn_801ECD74(&local);
    fn_801ECF50(4);
    fn_80226AB4(0x90, 3, 3);
    fn_801E7BDC(a->x, a->y, a->z);
    fn_801E7BDC(b->x, b->y, b->z);
    fn_801E7BDC(c->x, c->y, c->z);
    fn_801E7BD8();
}
