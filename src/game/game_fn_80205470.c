typedef signed short s16;
typedef unsigned int u32;

typedef struct Vec3s80205470 {
    s16 x;
    s16 y;
    s16 z;
} Vec3s80205470;

typedef struct Vec3f80205470 {
    float x;
    float y;
    float z;
} Vec3f80205470;

typedef struct Value80205470 {
    u32 words[4];
} Value80205470;

extern Value80205470 lbl_8023B890;
extern int lbl_8064D8B0;
extern int lbl_8064D18C;
extern u32 lbl_806515BC;
extern u32 lbl_806515C0;
extern u32 lbl_806515C4;

extern void *fn_80201814(int id);
extern void *fn_80201BC8(void *object);
extern void *fn_80155DB4(void *object);
extern void fn_801261F4(void *object);
extern void fn_80204E0C(void *object, int value);
extern void fn_801568D8(void *object);
extern void fn_801568E4(void *object);
extern void fn_801568F0(void *object);
extern void fn_8011F0E8(void *object, Vec3f80205470 *position);
extern void fn_8011FB54(void *object, int value);
extern void fn_8011F7E0(void *object, int value);
extern void fn_8012B7A0(void *object, float value);
extern void fn_8012CDF0(void *object, int index, Value80205470 value, int flags);
extern void fn_8012C62C(void *object, int index, u32 *a, u32 *b, u32 *c,
                        int flags);
extern void fn_8020123C(int type, int first, int second, int value);

void fn_80205470(void *unused, int id, Vec3s80205470 *packed_position,
                 int event_type, float scale)
{
    void *object = fn_80201814(id);
    void *runtime = fn_80201BC8(object);
    void *model = fn_80155DB4(object);
    Vec3f80205470 position;
    Value80205470 value = lbl_8023B890;
    u32 a;
    u32 b;
    u32 c;

    position.x = packed_position->x;
    position.y = packed_position->y;
    position.z = packed_position->z;

    fn_801261F4(runtime);
    fn_80204E0C(object, lbl_8064D8B0);
    fn_801568D8(model);
    fn_801568E4(model);
    fn_801568F0(model);
    fn_8011F0E8(runtime, &position);
    fn_8011FB54(runtime, lbl_8064D18C);
    fn_8011F7E0(runtime, 0);
    fn_8012B7A0(runtime, scale);
    fn_8012CDF0(runtime, 15, value, 1);

    c = lbl_806515C4;
    b = lbl_806515C0;
    a = lbl_806515BC;
    fn_8012C62C(runtime, 15, &a, &b, &c, 4);
    fn_8020123C(event_type, id, id, 0);
}
