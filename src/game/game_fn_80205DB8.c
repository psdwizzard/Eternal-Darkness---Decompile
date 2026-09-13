typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Int3 { int x, y, z; } Int3;
typedef struct Vec4 { float x, y, z, w; } Vec4;
typedef struct QueryResult {
    u8 pad[8];
    Vec3 position;
    u8 pad2[20];
} QueryResult;

extern const volatile u32 lbl_8023B8A0[3];
extern Vec3 lbl_80640A88;
extern Vec4 lbl_80640A94;
extern float lbl_8064D8B8;
extern float lbl_806515E8, lbl_806515EC, lbl_806515F0;
extern float lbl_806515F4, lbl_806515F8, lbl_806515FC;

extern void *fn_80156938(void);
extern void *fn_80201BC8(void *);
extern void fn_8011F114(Vec3 *, void *);
extern float fn_801F691C(void);
extern void fn_801F68B0(Vec3 *);
extern u16 fn_8011FAF4(void *);
extern void fn_801F69F0(const Int3 *, Vec3 *, int);
extern int fn_8011F6A4(void *, int, int, int, QueryResult *, int);
extern void fn_8012B690(void *, const Vec3 *, Vec3 *);
extern void fn_801795A4(const Vec3 *, const Vec3 *, Vec3 *);
extern float fn_80179A74(Vec3 *);
extern float fn_800DAFA8(float);
extern void fn_80179A18(Vec3 *);
extern void fn_801798DC(Vec3 *, float);
extern void fn_80179570(const Vec3 *, const Vec3 *, Vec3 *);
extern u32 fn_80178E94(const Vec3 *, const Vec3 *);
extern void fn_80206100(void *);
extern void fn_8011F0E8(void *, const Vec3 *);
extern void fn_8012CEA4(void *, int, Vec4 *);
extern void fn_8011FABC(void *, int, int);
extern void fn_80211A6C(const Vec3 *, const Vec3 *, Vec3 *);
extern void fn_802064F4(void *, Vec4 *);
extern void fn_8012D0D0(void *);
extern void fn_80124DBC(void *);
extern void fn_8011DF6C(void);

int fn_80205DB8(void)
{
    Vec3 initial_position;
    Vec3 offset;
    Vec3 original_position;
    Vec3 destination_position;
    Vec3 screen_position;
    Int3 screen_input;
    Vec3 constant_position;
    Vec3 hit_position;
    Vec3 difference;
    Vec3 random_position;
    Vec3 position_temp;
    Vec3 random_temp;
    QueryResult result;
    void *object;
    u16 flags;
    float random;
    float length;
    float timer;

    object = fn_80201BC8(fn_80156938());
    fn_8011F114(&position_temp, object);
    initial_position = position_temp;
    random = fn_801F691C();
    constant_position = *(const Vec3 *)lbl_8023B8A0;
    fn_801F68B0(&random_temp);
    random_position = random_temp;
    flags = fn_8011FAF4(object);
    original_position = initial_position;
    screen_input.x = 0x140;
    screen_input.y = 0xA5;
    screen_input.z = 0x3F3E;
    fn_801F69F0(&screen_input, &screen_position, 0);

    if (fn_8011F6A4(object, 0, 0, -1, &result, 1) == -1) {
        fn_8012B690(object, &constant_position, &hit_position);
    } else {
        hit_position = result.position;
    }

    fn_801795A4(&screen_position, &random_position, &difference);
    length = fn_80179A74(&difference);
    random = (lbl_806515E8 * length) /
             fn_800DAFA8(lbl_806515EC * (random * lbl_806515F0));
    fn_80179A18(&difference);
    fn_801798DC(&difference, random);
    fn_80179570(&random_position, &difference, &screen_position);
    fn_801795A4(&screen_position, &hit_position, &offset);
    destination_position.x = screen_position.x;
    destination_position.y = screen_position.y;
    destination_position.z = screen_position.z;

    if ((flags & 0x10) == 0) {
        fn_80206100(object);
    } else {
        if (fn_80178E94(&hit_position, &destination_position) > 0x19 &&
            (flags & 8) == 0) {
            fn_801798DC(&offset, lbl_806515F4);
            original_position.x += offset.x;
            original_position.y += offset.y;
            original_position.z += offset.z;
            fn_8011F0E8(object, &original_position);
        } else {
            if ((flags & 8) == 0) {
                lbl_80640A88 = hit_position;
                fn_8012CEA4(object, 0xF, &lbl_80640A94);
                lbl_8064D8B8 = lbl_806515F8;
                fn_8011FABC(object, 0, 8);
            }
            fn_80211A6C(&lbl_80640A88, &hit_position, &offset);
            original_position.x += offset.x;
            original_position.y += offset.y;
            original_position.z += offset.z;
            fn_8011F0E8(object, &original_position);
            timer = lbl_8064D8B8;
            timer += lbl_806515FC;
            lbl_8064D8B8 = timer;
            fn_802064F4(object, &lbl_80640A94);
        }
    }

    fn_8012D0D0(object);
    fn_80124DBC(object);
    fn_8011DF6C();
    return 2;
}
