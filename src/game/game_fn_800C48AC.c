typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct QueryResult {
    u32 unknown[2];
    Vec3 position;
    u8 tail[0x18];
} QueryResult;

extern const Vec3 lbl_80239884;
extern u8 *lbl_8064C4E0;
extern float lbl_8064F1DC;

extern void *fn_80201B3C(void);
extern void *fn_80201B9C(void);
extern void *fn_80201BC8(void *);
extern int fn_80201EB8(void *);
extern int fn_80201B54(int *);
extern void *fn_80201B8C(u8 *);
extern void *fn_80201BC0(void *);
extern void *fn_80036D38(void *);
extern int fn_8011F6A4(void *, int, int, int, void *, int);
extern void fn_8011F114(Vec3 *, Vec3 *);
extern void *fn_801A717C(void);
extern void fn_801A7228(void *);
extern void fn_801A764C(void *, const Vec3 *);
extern void fn_801A74A0(void *, u32);
extern void fn_801A74A8(void *, u32);
extern void fn_801A76EC(void *, float);
extern void fn_801A7470(void *, u32);
extern u64 fn_8020123C(int, int, int, int);
extern void fn_801E7974(u8 *, u32);
extern void fn_8007D3C0(Vec3 *);

int fn_800C48AC(void *unused, void *context)
{
    QueryResult result;
    Vec3 position;
    Vec3 resolved;
    Vec3 fallback;
    Vec3 *source;
    void *current;
    void *object;
    void *model;
    void *message;
    int currentArea;
    int currentId;
    int area;
    int id;

    current = fn_80201B3C();
    if (fn_8011F6A4(context, 9, 15, -1, &result, 1) != -1) {
        object = fn_80201B9C();
        model = fn_80201BC8(current);
        if (model != 0) {
            fn_8011F114(&resolved, model);
            source = &resolved;
        } else {
            fallback = lbl_80239884;
            source = &fallback;
        }
        position = *source;
        currentArea = fn_80201EB8(current);
        currentId = fn_80201B54(current);
        message = fn_801A717C();
        fn_801A764C(message, &position);
        while (object != 0) {
            model = fn_80201BC8(object);
            area = fn_80201EB8(object);
            id = fn_80201B54(object);
            if (fn_80201B8C(object) != 0 && fn_80036D38(object) != 0 &&
                currentArea == area && current != object && model != 0) {
                fn_801A74A0(message, currentId);
                fn_801A74A8(message, id);
                fn_801A76EC(message, lbl_8064F1DC);
                fn_801A7470(message, 0x4D);
                /* Event payloads carry message pointers in a 32-bit integer slot. */
                fn_8020123C(0x32, currentId, id, (int)message);
            }
            object = fn_80201BC0(object);
        }
        fn_801A7228(message);
        fn_801E7974(lbl_8064C4E0, 0x300);
        fn_8007D3C0(&result.position);
    }
    return 1;
}
