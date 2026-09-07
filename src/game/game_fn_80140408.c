typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Pair { Vec3 a, b; } Pair;
extern int lbl_8064CB90;
extern unsigned char lbl_8064D019;
extern unsigned char lbl_8064D01A;
extern Pair lbl_805B0EA8[40];
extern float lbl_806503E0;
extern const float lbl_806503E4;

void fn_80140408(const Vec3* a, const Vec3* b, const Vec3* extent)
{
    unsigned char count;
    Pair* p;
    unsigned char i;
    float margin;
    if (!lbl_8064CB90) return;
    margin = lbl_806503E0;
    if (a->x >= -extent->x - margin && a->x <= margin - extent->x &&
        a->y >= -extent->y - margin && a->y <= margin - extent->y &&
        a->z >= -extent->z - margin && a->z <= margin - extent->z) return;
    count = lbl_8064D01A;
    for (i = 0; i < count; i++) {
        p = &lbl_805B0EA8[i];
        if (a->x >= p->a.x - lbl_806503E4 && a->x <= lbl_806503E4 + p->a.x &&
            a->y >= p->a.y - lbl_806503E4 && a->y <= lbl_806503E4 + p->a.y &&
            a->z >= p->a.z - lbl_806503E4 && a->z <= lbl_806503E4 + p->a.z &&
            b->x >= p->b.x - lbl_806503E4 && b->x <= lbl_806503E4 + p->b.x &&
            b->y >= p->b.y - lbl_806503E4 && b->y <= lbl_806503E4 + p->b.y &&
            b->z >= p->b.z - lbl_806503E4 && b->z <= lbl_806503E4 + p->b.z) return;
    }
    lbl_805B0EA8[lbl_8064D019].a = *a;
    lbl_805B0EA8[lbl_8064D019].b = *b;
    lbl_8064D019 = (lbl_8064D019 + 1) % 40;
    if (++lbl_8064D01A > 40) lbl_8064D01A = 40;
}
