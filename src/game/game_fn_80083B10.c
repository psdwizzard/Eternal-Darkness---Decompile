typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct MenuState {
    unsigned char pad[0x430];
    Vec3 *model;
    unsigned char pad434[4];
    unsigned int sound;
    unsigned char pad43C[4];
    int active;
} MenuState;

extern MenuState lbl_8031CD84;
/* Keep the lower-bound reads separate on the two clamp paths. */
extern volatile float lbl_8064EACC;
extern const float lbl_8064EAD0;
extern void fn_80144C40(void);
extern void fn_8011F114(Vec3 *, Vec3 *);
extern void fn_8011F0E8(Vec3 *, Vec3 *);
extern int fn_801A98F4(int, void *);
extern void fn_80083938(void);

static inline float maximum(float value, float lower)
{
    if (value > lower) {
        lower = value;
    }
    return lower;
}

static inline float clampX(float value)
{
    float lower = maximum(value, lbl_8064EACC);
    float upper = lbl_8064EAD0;
    if (upper < lower) {
        return upper;
    }
    return maximum(value, lbl_8064EACC);
}

/* Move the menu model along its x axis, clamping it to the menu limits. */
void fn_80083B10(short offset)
{
    Vec3 position;
    float previousX;
    float newX;

    fn_80144C40();
    fn_8011F114(&position, lbl_8031CD84.model);
    previousX = position.x;
    newX = previousX + offset;
    position.x = newX;
    position.x = clampX(newX);
    fn_8011F0E8(lbl_8031CD84.model, &position);
    if (previousX != position.x) {
        if (lbl_8031CD84.sound == 0) {
            lbl_8031CD84.sound = fn_801A98F4(0x10E, (void *)100);
        }
        lbl_8031CD84.active = 1;
    }
    fn_80083938();
}
