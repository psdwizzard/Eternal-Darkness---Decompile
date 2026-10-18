typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec3s { short x, y, z; } Vec3s;
typedef struct Vec3i { int x, y, z; } Vec3i;
typedef struct Result { Vec3 normal; Vec3 point; } Result;
typedef struct Quad {
    float unk0;
    Vec3i pos;
    unsigned short idx[4];
    unsigned char unk18;
} Quad;
typedef struct QuadInfo {
    short unk0;
    unsigned char unk2;
    float x, y, z;
    float dist;
    Vec3i pos;
    float unk20;
    unsigned char unk24;
    char pad25[3];
    short unk28;
    unsigned short *indices;
    unsigned char unk30;
    int unk34;
} QuadInfo;
typedef struct Shape {
    Vec3 point;
    unsigned char pad0C[0xC];
    float radius;
    Vec3 axis;
    float tolerance;
    Vec3 bound;
    float bound_radius;
} Shape;
typedef struct Obstacle {
    unsigned char pad00[4];
    Vec3 bound;
    float tolerance;
    Vec3 axis;
    float distance;
} Obstacle;
extern void fn_80136610(Quad*, QuadInfo*, Vec3s*);
extern int fn_8013E284(const Shape*, const Obstacle*, const void*, Result*);
extern float PSVECSquareDistance(const Vec3*, const Vec3*);
extern float lbl_806502A0;

int fn_80136944(const Shape* shape, void* object, Result* out)
{
    QuadInfo surface;
    Result candidate;
    float best = lbl_806502A0;
    int found = 0;
    unsigned char i;

    for (i = 0; i < 6; i++) {
        fn_80136610((Quad*)((char*)object + 0x30 + i * 0x1C),
                    &surface, (Vec3s*)object);
        if (fn_8013E284(shape, (const Obstacle*)&surface, object, &candidate)) {
            float distance = PSVECSquareDistance(&shape->point, &candidate.point);
            if (distance < best) {
                best = distance;
                found = 1;
                *out = candidate;
            }
        }
    }
    return found;
}
