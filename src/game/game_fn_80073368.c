#define NULL ((void *)0)

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Vec3s {
    short x, y, z;
} Vec3s;

typedef struct Shape {
    Vec3 first;
    Vec3 second;
    float radius;
    Vec3 axis;
    float length;
    Vec3 center;
    float bound_radius;
} Shape;

typedef struct Segment {
    Vec3 first;
    Vec3 second;
    Vec3 axis;
    float length;
} Segment;

typedef struct Result {
    Vec3 normal;
    Vec3 point;
} Result;

typedef struct Spot {
    char pad0[0x2C];
    Vec3s pos;
    char pad32[0x48 - 0x32];
    unsigned int flags;
} Spot;

typedef struct Model {
    char pad0[0x9F];
    unsigned char type;
} Model;

extern void fn_8011F0E8(Vec3 *object, Vec3 *position);
extern void fn_8011F114(Vec3 *, Vec3 *);
extern float fn_8011F6F8(void *);
extern void *fn_8011F770(void *object);
extern unsigned int fn_8011FAEC(void *);
extern void *fn_8012AB2C(unsigned char *);
extern void fn_8012B7A0(void *, float);
extern float fn_8012B7D0(void *, Vec3 *);
typedef struct CollisionWorld CollisionWorld;
extern int fn_80137350(void *, const Shape *, const CollisionWorld *, Result *, unsigned int, unsigned short *);
extern int fn_8013B9DC(void *object, char *item, unsigned short count, void *other);
extern int fn_8013BAAC(void *context, void *object, float value);
extern void fn_8013F3C0(Shape *, const Vec3 *, const Vec3 *, float);
extern void fn_8013F4D0(Segment *, const Vec3 *, const Vec3 *);
extern void *fn_80140258(void *owner, const Vec3 *value, Vec3 *out, int flags, void *filter);
extern void *fn_8015C2FC(int);
extern int fn_80179064(int, int, int, int);
extern void fn_80179DB0(Vec3 *, Vec3s *);
extern void *fn_80201B8C(unsigned char *);
extern void *fn_80201B9C(void);
extern void *fn_80201BC0(void *);
extern void *fn_80201BC8(void *);
extern void *fn_80201BD0(void *object);
extern int fn_80201EB8(void *);
extern void PSVECAdd(Vec3 *, Vec3 *, Vec3 *);

extern void *lbl_8064C4E4;
extern int lbl_8064D18C;
extern float lbl_8064E868;
extern float lbl_8064E86C;

int fn_80073368(char *item, unsigned short itemCount, Spot *spots, unsigned short spotCount, Vec3 *origin,
                Vec3 *out, unsigned int blockDist, unsigned int maxDist, unsigned int minDist, void *context,
                void *self, void *target) {
    Shape shapeA;
    Segment segment;
    Shape shapeB;
    Spot *found[8];
    Result resultA;
    Result resultB;
    Vec3 selfPos;
    Vec3 hitPos;
    Vec3 pos;
    Vec3 dir;
    Vec3 tmp;
    Vec3 targetPos;
    unsigned short hitA;
    unsigned short hitB;
    Vec3 *targetRot;
    void *owner;
    int i;
    int numFound;
    int done;
    unsigned int dist;
    Model *model;
    float scale;

    numFound = 0;
    done = 0;
    PSVECAdd(origin, fn_8011F770(self), &selfPos);
    targetRot = fn_8011F770(target);
    owner = fn_8012AB2C(self);

    for (i = 0; i < spotCount && numFound < 8; i++, spots++) {
        void *node;
        int blockers;
        void *object;

        if (!(spots->flags & 0x40)) {
            continue;
        }
        dist = fn_80179064(spots->pos.x, spots->pos.y, origin->x, origin->y);
        if (dist >= maxDist || dist <= minDist) {
            continue;
        }

        node = fn_80201B9C();
        for (blockers = 0; node != NULL && blockers == 0; node = fn_80201BC0(node)) {
            object = fn_80201BC8(node);
            if (object != NULL && lbl_8064D18C == fn_80201EB8(node) && (fn_8011FAEC(object) & 0xC0)) {
                fn_8011F114(&tmp, object);
                pos = tmp;
                if (fn_80179064(spots->pos.x, spots->pos.y, pos.x, pos.y) < blockDist) {
                    blockers++;
                }
            }
        }
        if (blockers != 0) {
            continue;
        }

        fn_80179DB0(out, &spots->pos);
        PSVECAdd(out, targetRot, &dir);
        if (lbl_8064C4E4 != self) {
            void *filter = fn_8015C2FC(2);
            fn_8013F3C0(&shapeA, &dir, &dir, fn_8011F6F8(target));
            if (fn_80137350(target, &shapeA, filter, &resultA, 1, &hitA) == 0) {
                found[numFound++] = spots;
            }
        } else {
            fn_8013F4D0(&segment, &selfPos, &dir);
            if (fn_8013B9DC(self, item, itemCount, &segment) == 0 &&
                fn_80140258(owner, &segment.first, &hitPos, 1, NULL) == NULL) {
                void *filter = fn_8015C2FC(2);
                fn_8013F3C0(&shapeB, &dir, &dir, fn_8011F6F8(target));
                if (fn_80137350(target, &shapeB, filter, &resultB, 1, &hitB) == 0) {
                    found[numFound++] = spots;
                }
            }
        }
    }

    for (i = 0; i < numFound && done == 0; i++) {
        model = fn_80201B8C(fn_80201BD0(target));
        fn_80179DB0(out, &found[i]->pos);
        fn_8011F0E8(target, out);
        targetPos = *out;
        fn_8012B7A0(target, fn_8012B7D0(self, &targetPos));
        switch (model->type) {
        case 3:
            scale = lbl_8064E868;
            break;
        case 6:
            scale = lbl_8064E86C;
            break;
        default:
            scale = lbl_8064E86C;
            break;
        }
        if (fn_8013BAAC(context, target, scale) == 0) {
            done = 1;
        }
    }
    return done;
}
