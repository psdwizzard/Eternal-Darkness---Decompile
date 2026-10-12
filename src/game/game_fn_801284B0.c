typedef unsigned char u8;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct SearchResult {
    int second;
    int first;
    Vec3 position;
    u8 pad14[0x0C];
    float value;
    u8 pad24[0x10];
} SearchResult;

extern void fn_8012C198(u8 *owner);
extern int fn_8011F598(void *object, int first, int second, int previous,
                      SearchResult *result, u8 options);
extern float fn_80211B08(const Vec3 *vector);
extern void fn_80211A90(const Vec3 *input, Vec3 *output, float scale);
extern void fn_8012CCF0(u8 *state, int index, Vec3 *first, Vec3 *second,
                      Vec3 *third, int alternate);
extern Vec3 lbl_8023A6C8;
extern float lbl_806501A4;

/* The joint routine receives private copies of its vector arguments. */
static inline void setJointVectors(u8 *owner, int index, Vec3 first,
                                  Vec3 second, Vec3 third, int alternate)
{
    fn_8012CCF0(owner, index, &first, &second, &third, alternate);
}

void fn_801284B0(u8 *owner, int first, int second)
{
    SearchResult result;
    Vec3 scaled;
    Vec3 direction;

    if (owner != 0) {
        fn_8012C198(owner);
        if (fn_8011F598(owner, first, second, -1, &result, 2) != -1) {
            direction.x = -result.position.x;
            direction.y = -result.position.y;
            direction.z = -result.position.z;
            if (fn_80211B08(&direction) > lbl_806501A4) {
                fn_80211A90(&direction, &scaled, lbl_806501A4);
                setJointVectors(owner, 15, lbl_8023A6C8, scaled, direction, 0);
            }
        }
    }
}
