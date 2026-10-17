typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern Vec3 lbl_80239878;
extern float lbl_8064F140;
extern float lbl_8064F164;
extern float lbl_8064F1D0;
extern float lbl_8064F1D4;
extern float lbl_8064F1D8;

extern unsigned short fn_801A7580(void *);
extern int fn_8011EB04(void *);
extern void fn_8012B690(void *, const void *, void *);
extern void *fn_8011F130(void *);
extern void fn_80211A6C(const Vec3 *, const Vec3 *, Vec3 *);
extern unsigned int fn_80178E94(const float *, const float *);
extern float fn_80048C2C(float);
extern void fn_80211A90(const Vec3 *, Vec3 *, float);
extern void fn_80211A48(const Vec3 *, const Vec3 *, Vec3 *);

int fn_800C4718(void *object, void *target, void *actor, Vec3 *position)
{
    Vec3 offset;
    Vec3 direction;
    float time;
    float distance;
    Vec3 *origin;
    int handled = 0;

    offset = lbl_80239878;
    time = (float)fn_801A7580(actor);
    if (fn_8011EB04(target) == 0x60 && fn_801A7580(actor) < 60U) {
        fn_8012B690(object, &offset, &direction);
        origin = fn_8011F130(object);
        fn_80211A6C(&direction, origin, &direction);
        distance = (float)fn_80178E94(&origin->x, &position->x);
        fn_80211A90(&direction, &direction,
            (distance * ((lbl_8064F1D0 * (lbl_8064F140 - time / lbl_8064F1D4)) *
            fn_80048C2C(lbl_8064F1D8 * time))) / lbl_8064F164);
        fn_80211A48(position, &direction, position);
        handled = 1;
    }
    return handled;
}
