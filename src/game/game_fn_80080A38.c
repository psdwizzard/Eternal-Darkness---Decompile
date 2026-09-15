typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Segment {
    Vec3 start;
    Vec3 end;
    float width;
    Vec3 direction;
    float tail[2];
} Segment;

typedef struct Collision {
    float values[9];
} Collision;

typedef struct Hit {
    float pad[3];
    Vec3 position;
} Hit;

extern float lbl_8064EA60;
extern float lbl_8064EA78;
extern void *lbl_8064C4E4;

extern void fn_8013F3C0(Segment *, const Vec3 *, const Vec3 *, float);
extern unsigned int fn_8013638C(Segment *, Vec3 *, void *, Collision *, float *,
                                float);
extern void fn_80211A90(const Vec3 *, Vec3 *, float);
extern void fn_80211A48(const Vec3 *, const Vec3 *, Vec3 *);
extern void *fn_8015C348(int);
extern unsigned int fn_8013F898(void *, Segment *, Hit *);

void fn_80080A38(Vec3 *result, const Vec3 *start, Vec3 *end,
                 int adjust_hit, int shorten)
{
    /* NonMatching: behavior-complete, size-exact reconstruction. Remaining
     * differences are two word-load slots and FP expression scheduling. */
    Segment segment;
    Hit hit;
    Vec3 scaled;
    float fraction;
    Collision collision;

    fn_8013F3C0(&segment, start, end, lbl_8064EA60);
    if (shorten) {
        if (fn_8013638C(&segment, &segment.end, lbl_8064C4E4,
                        &collision, &fraction, lbl_8064EA78)) {
            fn_80211A90(&segment.direction, &scaled, fraction);
            fn_80211A48(&segment.start, &scaled, &segment.end);
            fn_8013F3C0(&segment, &segment.start, &segment.end,
                        segment.width);
            {
                unsigned int *src = (unsigned int *)&segment.end;
                unsigned int *dst = (unsigned int *)end;
                unsigned int second = src[1];
                unsigned int first = src[0];
                dst[0] = first;
                {
                    unsigned int third = src[2];
                    dst[1] = second;
                    dst[2] = third;
                }
            }
        }
    }
    if (adjust_hit) {
        void *context = fn_8015C348(2);
        if (fn_8013F898(context, &segment, &hit)) {
            float x = hit.position.x + segment.direction.x * segment.width;
            float z = hit.position.z + segment.direction.z * segment.width;
            float y = hit.position.y + segment.direction.y * segment.width;
            end->x = x;
            end->y = y;
            end->z = z;
        }
    }
    *result = *end;
}
