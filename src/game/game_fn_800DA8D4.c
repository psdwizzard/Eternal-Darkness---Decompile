typedef unsigned int u32;
typedef unsigned char u8;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Quaternion {
    float x, y, z, w;
} Quaternion;

typedef struct Int3 {
    int x, y, z;
} Int3;

typedef struct SearchResult {
    int second, first;
    Vec3 position;
    Vec3 direction;
    float value;
    int reserved;
} SearchResult;

typedef float Matrix34[3][4];

extern void *fn_80156938(void *);
extern void *fn_80201BC8(void *);
extern void *fn_80201C24(void *);
extern void *fn_8011F130(void *);
extern void fn_801F68B0(Vec3 *);
extern void fn_801F68F8(Vec3 *);
extern float fn_801F691C(void);
extern u32 fn_80157C80(void *);
extern u32 fn_8011FAF4(void *);
extern u32 fn_8011FAEC(void *);
extern short fn_80157858(void *);
extern void fn_801F69F0(const Int3 *, Vec3 *, int);
extern float fn_80179A74(Vec3 *);
extern float fn_800DAFA8();
extern void fn_80211A48(const Vec3 *, const Vec3 *, Vec3 *);
extern void fn_80211A6C(const Vec3 *, const Vec3 *, Vec3 *);
extern void fn_80211A90(const Vec3 *, Vec3 *, float);
extern void fn_80211AAC(const Vec3 *, Vec3 *);
extern void fn_80211B64(const Vec3 *, const Vec3 *, Vec3 *);
extern float fn_80211B08(const Vec3 *);
extern float fn_80211B44(const Vec3 *, const Vec3 *);
extern int fn_8012DCBC(void *, int, int, int *, int, int);
extern void *fn_8011FE34(void *);
extern void fn_8012B7A0();
extern void fn_8012CDF0(void *, int, Quaternion, int);
extern int fn_801579EC(void *);
extern int fn_8011EB04(void *);
extern int fn_8011F598(void *, int, int, int, SearchResult *, u8);
extern float fn_800490E8(float, float);
extern void fn_8017A244(const Vec3 *, Quaternion *, float);
extern void fn_80211DC0(const Quaternion *, const Quaternion *, Quaternion *);
extern void fn_802114E0(Matrix34, const Quaternion *);
extern void fn_80211710(const Matrix34, const Vec3 *, Vec3 *);
extern void fn_80211E70(Quaternion *, const Vec3 *, float);
extern void fn_8012CF08(void *, int, Quaternion, Quaternion, int, int, float);
extern u32 fn_80157C98(void *, u32, u32);
extern u32 fn_80178E94(const float *, const float *);
extern void fn_8012CEA4(void *, int, Quaternion *);
extern u32 fn_8011FABC(void *, u32, u32);
extern void fn_8017A34C(const Quaternion *, const Quaternion *, Quaternion *);
extern void fn_8012D0D0(void *);
extern int fn_8011FCB0(void *);
extern void fn_8012A254(void *);
extern void fn_80124DBC(void *);

extern Vec3 lbl_80248C18;
extern Quaternion lbl_80325B60;
extern Quaternion lbl_80325B70;
extern float lbl_8064CAC0;
extern float lbl_8064F464;
extern float lbl_8064F468;
extern float lbl_8064F46C;
extern float lbl_8064F470;
extern float lbl_8064F474;
extern float lbl_8064F478;
extern float lbl_8064F47C;
extern float lbl_8064F480;

int fn_800DA8D4(void *context)
{
    SearchResult primary;
    SearchResult secondary;
    Matrix34 matrix;
    Vec3 step;
    Vec3 destination;
    Vec3 projected;
    Vec3 camera;
    Vec3 lookAt;
    Vec3 axis;
    Vec3 turnAxis;
    Vec3 ray;
    Vec3 worldPoint;
    Int3 screenPoint;
    Quaternion original;
    Quaternion spin;
    Quaternion result;
    Quaternion combined;
    Quaternion finalRotation;
    Vec3 viewDirection;
    Vec3 side;
    Quaternion alignment;
    Quaternion turn;
    Vec3 transformed;
    Quaternion base;
    Vec3 cameraSource;
    Vec3 lookAtSource;
    int animation;
    void *owner;
    void *object;
    Vec3 *position;
    void *state;
    u32 flags;
    u32 objectFlags;
    register int depth;
    float fov;
    float distance;
    float scale;

    owner = fn_80156938(context);
    object = fn_80201BC8(owner);
    if (object != 0) {
        position = fn_8011F130(object);
        fn_801F68B0(&cameraSource);
        camera = cameraSource;
        fn_801F68F8(&lookAtSource);
        lookAt = lookAtSource;
        fov = fn_801F691C();
        depth = 0;
        state = fn_80201C24(owner);
        flags = fn_80157C80(state);
        objectFlags = fn_8011FAF4(object);
        if (!(fn_8011FAEC(object) & 0x4000)) {
            fn_80157858(state);
            /* ASM: mr retains the sign-extended short result returned by lha;
             * a C assignment inserts an additional, redundant extsh. */
            asm { mr depth, r3 }
        }
        /* Project the screen target and approach it in world space. */
        screenPoint.x = 320;
        screenPoint.y = 165;
        screenPoint.z = depth != 0 ? depth : 0x3F78;
        fn_801F69F0(&screenPoint, &worldPoint, 0);
        projected.x = worldPoint.x;
        projected.y = worldPoint.y;
        projected.z = worldPoint.z;
        fn_80211A6C(&projected, &camera, &ray);
        distance = fn_80179A74(&ray);
        scale = (lbl_8064F468 * distance) /
            fn_800DAFA8(lbl_8064F46C * (fov * lbl_8064F470));
        fn_80211AAC(&ray, &ray);
        fn_80211A90(&ray, &ray, scale);
        fn_80211A48(&camera, &ray, &projected);
        fn_80211A6C(&projected, position, &step);
        fn_80211A90(&step, &step, lbl_8064F474);
        destination = projected;
        if ((flags & 0x100) == 0 && fn_8012DCBC(object, 15, 2, &animation, 0, 0) == 0) {
            int kind = 1;

            /* Align the object's reference directions with the camera. */
            fn_80211A6C(&lookAt, &camera, &viewDirection);
            fn_80211B64(&viewDirection, &lbl_80248C18, &side);
            fn_80211B64(&side, &viewDirection, &lbl_80248C18);
            fn_80211AAC(&lbl_80248C18, &lbl_80248C18);
            lbl_8064CAC0 = lbl_8064F464;
            original = *(Quaternion *)fn_8011FE34(object);
            fn_8012B7A0(object, lbl_8064F464);
            fn_8012CDF0(object, 15, original, 1);
            if (fn_801579EC(state) == 0 &&
                (fn_8011EB04(object) == 0xC1 || fn_8011EB04(object) == 0xE6)) {
                kind = 9;
            }
            if (fn_8011F598(object, kind, 15, -1, &primary, 1) != -1) {
                fn_80201C24(owner);
                if (fn_8011F598(object, 19, 15, -1, &secondary, 1) != -1) {
                    float length;
                    float magnitude;
                    fn_80211B64(&primary.direction, &lbl_80248C18, &axis);
                    length = fn_80211B08(&axis);
                    magnitude = length;
                    if (length < lbl_8064F464) {
                        magnitude = -length;
                    }
                    if (magnitude > lbl_8064F46C) {
                        float angle;
                        float dot;
                        fn_80211AAC(&axis, &axis);
                        dot = fn_80211B44(&primary.direction, &lbl_80248C18);
                        angle = fn_800490E8(length, dot);
                        fn_8017A244(&axis, &alignment, angle);
                        fn_80211DC0(&alignment, &original, &result);
                        fn_802114E0(matrix, &alignment);
                        fn_80211AAC(&secondary.direction, &secondary.direction);
                        fn_80211710(matrix, &secondary.direction, &transformed);
                        fn_80211AAC(&transformed, &transformed);
                        fn_80211A90(&viewDirection, &viewDirection, lbl_8064F478);
                        fn_80211AAC(&viewDirection, &viewDirection);
                        fn_80211B64(&transformed, &viewDirection, &turnAxis);
                        length = fn_80211B08(&turnAxis);
                        fn_80211AAC(&turnAxis, &turnAxis);
                        angle = fn_800490E8(length, fn_80211B44(&transformed, &viewDirection));
                        fn_80211E70(&turn, &turnAxis, angle);
                        fn_80211DC0(&turn, &alignment, &combined);
                        fn_80211DC0(&combined, &original, &finalRotation);
                        fn_8012CF08(object, 15, original, finalRotation, 1, 0, lbl_8064F47C);
                    }
                }
            }
            fn_80157C98(state, 0, 0x100);
        }
        if (fn_80178E94(&position->x, &destination.x) > 2) {
            fn_80211A48(position, &step, position);
            if (fn_801579EC(state) != 0 && !(flags & 0x200) && (flags & 0x100) != 0 &&
                fn_8012DCBC(object, 15, 3, &animation, 0, 0) == 0) {
                fn_80157C98(state, 0, 0x200);
            }
        } else if ((flags & 0x100) != 0 && fn_8012DCBC(object, 15, 3, &animation, 0, 0) == 0) {
            int alternate = 0;
            if (fn_801579EC(state) != 0) {
                alternate = 1;
            }
            if (!(objectFlags & 8)) {
                if (alternate == 0) {
                    fn_8012CEA4(object, 15, &lbl_80325B60);
                } else {
                    fn_8012CEA4(object, 15, &lbl_80325B70);
                }
                fn_8011FABC(object, 0, 8);
            }
            /* Rotate the selected base orientation about the shared axis. */
            base = alternate ? lbl_80325B70 : lbl_80325B60;
            lbl_8064CAC0 += lbl_8064F480;
            fn_8017A244(&lbl_80248C18, &spin, lbl_8064CAC0);
            fn_8017A34C(&spin, &base, &result);
            fn_8012CDF0(object, 15, result, 1);
        }
        fn_8012D0D0(object);
        if (fn_8011FCB0(object) != 0) {
            fn_8012A254(object);
        } else {
            fn_80124DBC(object);
        }
    }
    return 2;
}
