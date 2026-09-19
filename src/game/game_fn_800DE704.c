typedef unsigned int u32;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct SpawnInfo {
    Vec3 position;
    u32 field_0C;
    u32 field_10;
    u32 field_14;
    u32 field_18;
    u32 field_1C;
    u32 field_20;
    u32 field_24;
    u32 field_28;
    u32 field_2C;
    u32 field_30;
    u32 field_34;
} SpawnInfo;

extern u32 lbl_8064D18C;
extern void *lbl_8064C504;
extern void *fn_80204A8C(void);
extern void *fn_80201AE4(void);
extern int fn_80201B44();
extern void *fn_80201814();
#define FN_80201E78_RETURN Vec3
#define FN_80201E78_PARAMETERS void *
extern FN_80201E78_RETURN fn_80201E78(FN_80201E78_PARAMETERS);extern void fn_80043F44(SpawnInfo *);
extern void *fn_80034708(SpawnInfo *);
extern void *fn_80201BC8();
extern int fn_80201B54();
extern void fn_80204CE4(void *, void *);
extern void fn_80201D54(void *, u32);
extern void fn_802015A4(void *);
extern void *fn_80156DA0(int, Vec3 *);
extern int fn_8011FCB0(void *);
extern void fn_801568C8(void *, void *, void *, void *);
extern void fn_80156904(void *, int);
extern void fn_801568FC(void *, void *);
extern void fn_8015690C(void *, void *);
extern void fn_80156918(void *, void *);
extern int fn_801261F4(void *);
extern void* fn_80201C24();
extern int fn_80157BC4(void);
extern int fn_80157BF4(void *);
extern void *fn_801E6CA0(void *, int, int, int, int);
extern void fn_80027948(void *, int, void *, void *, int, int, int);
extern void fn_8002A590(void);
extern void fn_8002A508(void);
extern void fn_8002AC60(void);
extern void fn_8002AA18(void);
extern void fn_8002A4C8(void);

/* NonMatching: behavior-complete object/action/event setup. The generated
 * function is four bytes short because MWCC coalesces the fn_80201B54 result
 * directly into its final register; retail retains an extra mr through r0.
 * Keeping the reused owner identity integer-typed does not prevent that
 * coalescing. The remaining differences are callee-saved register allocation.
 */
void fn_800DE704(void)
{
    void *context = fn_80204A8C();
    void *source = fn_80201AE4();
    int owner = fn_80201B44();
    void *parent;
    Vec3 position;
    SpawnInfo spawn;
    void *object;
    void *info;
    void *handle;

    fn_80201814(source);
    parent = fn_80201814((void *)owner);
    position = fn_80201E78(parent);
    fn_80043F44(&spawn);
    spawn.field_10 = 25;
    spawn.field_14 = 105;
    spawn.field_18 = 187;
    spawn.field_28 = 30;
    spawn.position = position;
    object = fn_80034708(&spawn);
    info = fn_80201BC8(object);
    owner = fn_80201B54(object);
    fn_80204CE4(object, context);
    fn_80201D54(object, lbl_8064D18C);
    fn_802015A4(object);
    handle = fn_80156DA0(3, &position);
    fn_801568C8(handle,
                fn_8011FCB0(info) != 0 ? fn_8002A508 : fn_8002A590,
                fn_8002AC60, fn_8002AA18);
    fn_80156904(handle, 0);
    fn_801568FC(handle, fn_8002AA18);
    fn_8015690C(handle, fn_8002A4C8);
    fn_80156918(handle, object);
    fn_801261F4(info);
    object = fn_80201C24(object);
    info = (void *)fn_80157BC4();
    object = fn_801E6CA0(lbl_8064C504, fn_80157BF4(object), (int)info, 0, 1);
    fn_80027948(object, 0, source, (void *)owner, 0, 0, 0);
}
