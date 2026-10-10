#define NULL ((void *)0)

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Vec3s {
    short x, y, z;
} Vec3s;

typedef struct Segment {
    char data[0x28];
} Segment;

typedef struct Spot {
    char pad0[0x2C];
    Vec3s pos;
    char pad32[0x48 - 0x32];
    unsigned int flags;
} Spot;

extern void fn_8011F0E8(void *object, Vec3 *position);
extern void fn_8011F114(Vec3 *, void *);
extern Vec3 *fn_8011F770(void *object);
extern unsigned int fn_8011FAEC(void *);
extern void *fn_8012AB2C(void *);
extern void fn_8012B7A0(void *, float);
extern float fn_8012B7D0(void *, Vec3);
extern int fn_8013B9DC(void *object, char *item, unsigned short count, void *other);
extern void fn_8013F4D0(Segment *, Vec3 *, Vec3 *);
extern void *fn_80140258(void *owner, const Vec3 *value, Vec3 *out, int flags, void *filter);
extern unsigned int fn_80179064(int, int, int, int);
extern void fn_80179DB0(Vec3 *, Vec3s *);
extern void *fn_80201B9C(void);
extern void *fn_80201BC0(void *);
extern void *fn_80201BC8(void *);
extern int fn_80201EB8(void *);
extern void fn_80211A48(Vec3 *, Vec3 *, Vec3 *);

extern void *lbl_8064C4E4;
extern int lbl_8064D18C;

int fn_80072F88(char *item, unsigned short itemCount, Spot *spots, unsigned short spotCount, Vec3 *origin,
                Vec3 *out, unsigned int blockDist, unsigned int maxDist, unsigned int minDist, void *self,
                void *target) {
    Segment segment;
    Vec3 selfPos;
    Vec3 hitPos;
    Vec3 pos;
    Vec3 dir;
    Vec3 tmp;
    Vec3 *targetRot;
    void *owner;
    int i;
    int done;
    unsigned int dist;

    Vec3 *selfRot;

    done = 0;
    selfRot = fn_8011F770(self);
    fn_80211A48(origin, selfRot, &selfPos);
    targetRot = fn_8011F770(target);
    owner = fn_8012AB2C(self);

    for (i = 0; i < spotCount && done == 0; i++, spots++) {
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
        fn_80211A48(out, targetRot, &dir);
        fn_8013F4D0(&segment, &selfPos, &dir);
        if (lbl_8064C4E4 == self) {
            if (fn_8013B9DC(self, item, itemCount, &segment) != 0) {
                continue;
            }
            if (fn_80140258(owner, (Vec3 *)&segment, &hitPos, 1, NULL) != NULL) {
                continue;
            }
        }
        fn_80179DB0(out, &spots->pos);
        fn_8011F0E8(target, out);
        fn_8012B7A0(target, fn_8012B7D0(self, *out));
        done = 1;
    }
    return done;
}
