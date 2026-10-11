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

extern int fn_800FBFB0(void);
extern void fn_80211A48(Vec3 *, Vec3 *, Vec3 *);
extern void fn_80211A90(Vec3 *, Vec3 *, float);
extern float fn_80211B08(Vec3 *);
extern float fn_80211B44(Vec3 *, Vec3 *);
extern void fn_80211C78(Vec3 *, Vec3 *, Vec3 *);

extern float lbl_8065031C;
extern float lbl_80650320;
extern float lbl_80650324;
extern float lbl_8065032C;
extern float lbl_80650330;

void fn_8013C5F4(Body *body, Source *src, Vec3 *axis, float dist, float damping) {
    Vec3 step;
    float len;

    float d = -(dist + fn_80211B44(axis, &body->normal));
    float limit = -(lbl_80650324 + body->offset);

    if (d > limit) {
        fn_80211C78(&body->dir, axis, &body->dir);
        body->dir.x += ((float)(fn_800FBFB0() % 10) - lbl_8065032C) / lbl_80650330;
        body->dir.y += ((float)(fn_800FBFB0() % 10) - lbl_8065032C) / lbl_80650330;
        len = fn_80211B08(&body->dir);
        if (len != lbl_8065031C) {
            fn_80211A90(&body->dir, &body->dir, lbl_80650320 / len);
        }
        body->speed *= damping;
        fn_80211A90(&body->dir, &step, body->speed);
        body->pos = src->pos;
        fn_80211A48(&body->pos, &step, &body->normal);
    }
}
