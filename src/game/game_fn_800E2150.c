typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Quat {
    float x, y, z, w;
} Quat;

typedef struct Matrix34 {
    float m[3][4];
} Matrix34;

typedef struct EventData {
    unsigned char pad[0x5C];
    int object_id;
} EventData;

extern void *fn_80201814();
extern void *fn_80155DB4(void *);
extern void *fn_80201BC8();
extern void *fn_80201B8C();
extern void* fn_80201C24();
extern int fn_8012FDA0(void *, int);
extern void fn_8011F114();
extern void fn_80127FD8(void *, int, Matrix34 *);
extern void fn_80211EFC(Quat *, Matrix34 *);
extern void fn_80127DF8(void *, int, Matrix34 *);
extern void fn_8012B690(void *, Vec3 *, Vec3 *);
extern void fn_800CC140(void *, int, int, int, int);
extern void fn_80204FDC(void *);
extern int fn_801A98F4(int, int);
extern int fn_8011FCB0(void *);
extern void fn_801568C8(void *, void *, void *, void *);
extern void fn_80156904(void *, int);
extern void fn_801568FC(void *, void *);
extern void fn_8015690C(void *, void *);
extern void fn_801570F8(void *, void *);
extern void fn_8011FE3C(void *, void *);
extern void *fn_8011FB4C(void *);
extern void fn_8011FB54(void *, void *);
extern void fn_8011F0E8(void *, Vec3 *);
extern Quat *fn_8011FE34(void *);
extern unsigned int fn_8011FA8C(void *, int, int);

extern void fn_8002A590(void);
extern void fn_8002A508(void);
extern void fn_8002AC60(void);
extern void fn_8002AA18(void);
extern void fn_8002A4C8(void);

void fn_800E2150(void *context, void *source, EventData *data, void *transform)
{
    Matrix34 matrix;
    Vec3 scale;
    Vec3 position;
    Quat rotation;
    Vec3 transform_position;
    void *callback;
    void *owner;
    void *object;
    void *transform_copy;
    int slot;
    void *source_callback;
    Quat *owner_rotation;

    transform_copy = transform;
    if (data->object_id == 0)
        return;

    object = fn_80201814(data->object_id);
    callback = fn_80155DB4(object);
    owner = fn_80201BC8(object);
    fn_80201B8C(object);
    fn_80201C24(object);
    slot = fn_8012FDA0(owner, 15);
    fn_8011F114(&transform_position, transform_copy);
    source_callback = fn_80155DB4(source);
    fn_80127FD8(owner, slot, &matrix);
    fn_80211EFC(&rotation, &matrix);
    fn_80127DF8(owner, slot, &matrix);
    scale.x = matrix.m[0][3];
    scale.y = matrix.m[1][3];
    scale.z = matrix.m[2][3];
    fn_8012B690(owner, &scale, &position);
    fn_800CC140(context, data->object_id, 0, 0, 0);
    fn_80204FDC(source);
    fn_801A98F4(45, 68);
    fn_801568C8(callback, fn_8011FCB0(transform_copy) ? fn_8002A508 : fn_8002A590,
                 fn_8002AC60, fn_8002AA18);
    fn_80156904(callback, 0);
    fn_801568FC(callback, fn_8002AA18);
    fn_8015690C(callback, fn_8002A4C8);
    fn_801570F8(source_callback, callback);
    fn_8011FE3C(owner, owner);
    fn_8011FB54(owner, fn_8011FB4C(transform_copy));
    fn_8011F0E8(owner, &position);
    owner_rotation = fn_8011FE34(owner);
    *owner_rotation = rotation;
    fn_8011FA8C(owner, 0, 0x10000);
}
