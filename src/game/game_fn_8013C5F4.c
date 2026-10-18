typedef struct Vec3 { float x, y, z; } Vec3;

typedef struct Body {
    Vec3 pos;
    Vec3 normal;
    float offset;
    Vec3 dir;
    float speed;
} Body;

typedef struct Source {
    char pad[0xC];
    Vec3 pos;
} Source;

extern int rand(void);
extern void PSVECAdd(Vec3 *, Vec3 *, Vec3 *);
extern void PSVECScale(Vec3 *, Vec3 *, float);
extern float PSVECMag(Vec3 *);
extern float PSVECDotProduct(Vec3 *, Vec3 *);
extern void C_VECReflect(Vec3 *, Vec3 *, Vec3 *);

extern float lbl_8065031C;
extern float lbl_80650320;
extern float lbl_80650324;
extern float lbl_8065032C;
extern float lbl_80650330;

void fn_8013C5F4(Body *body, Source *src, Vec3 *axis, float dist, float damping) {
    Vec3 step;
    float len;

    float d = -(dist + PSVECDotProduct(axis, &body->normal));
    float limit = -(lbl_80650324 + body->offset);

    if (d > limit) {
        C_VECReflect(&body->dir, axis, &body->dir);
        body->dir.x += ((float)(rand() % 10) - lbl_8065032C) / lbl_80650330;
        body->dir.y += ((float)(rand() % 10) - lbl_8065032C) / lbl_80650330;
        len = PSVECMag(&body->dir);
        if (len != lbl_8065031C) {
            PSVECScale(&body->dir, &body->dir, lbl_80650320 / len);
        }
        body->speed *= damping;
        PSVECScale(&body->dir, &step, body->speed);
        body->pos = src->pos;
        PSVECAdd(&body->pos, &step, &body->normal);
    }
}
