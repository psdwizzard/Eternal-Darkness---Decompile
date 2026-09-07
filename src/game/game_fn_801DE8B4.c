typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 { float x, y, z; } Vec3;

extern void* fn_80201B9C(void);
extern void* fn_80201BC8(void*);
extern void* fn_80201BC0(void*);
extern int fn_80201EB8(void*);
extern int fn_80201B4C(void*);
extern void fn_8011F114(Vec3*, void*);
extern int fn_80178E94(Vec3*, Vec3*);
extern int fn_80072A2C(Vec3*, Vec3*, int, int);
extern int fn_801D38E8(int);
extern int fn_800CAC5C(int, int, int*, int*, int*);
extern void fn_80043F44(void*);
extern void* fn_80034708(void*);
extern void fn_801261F4(void);
extern void fn_80201D54(void*, int);
extern void fn_80201D24(void*, int);
extern void fn_802015A4(void*);
extern void fn_8012C62C(void*, int, int*, int*, int*, int);
extern void fn_8011FA8C(void*, int, int);
extern int fn_80201B54(void*);
extern void fn_8020123C(int, int, int, int);
extern void* fn_80036D38(void*);
extern int fn_8012A100(void*, int);
extern void fn_801DDB84(Vec3*, int, int, void*);
extern void* fn_801294DC(void*, int, int, int);
extern void fn_80128C44(void*, void*, int);
extern void fn_80128C28(void*, void*, int);
extern int fn_801DE8AC(void);
extern void fn_801DE7FC(void*, int);
extern void fn_801DE7A0(int);
extern void fn_8012B7A0(void*, float);
extern void fn_80048708(void*);
extern void fn_801E8328(int, void*);
extern void fn_801AC9F4(int, int, Vec3*, int);
extern int fn_801D3A34(int, int);
extern int fn_801CEB2C(int);
extern void fn_8014F3A4(Vec3*, int, int, int, void*);
extern int lbl_8064D5A8, lbl_8064C308;

/* NonMatching: complete honest-C reconstruction of the selection, spawn,
 * callback, and follow-up effect paths. Retail's exact r21-r31 allocation,
 * aggregate Vec3 copy scheduling, and 0xd0-byte frame lowering diverge. */
int fn_801DE8B4(void* object, int variant, int skip_search, float scale)
{
    u8* base = object;
    u8* state = base + 0xbc;
    void* iterator = 0;
    void* selected = 0;
    void* spawned = 0;
    int ok = 1;
    int found = 0;
    int distance;
    int category;
    int a, b, c;
    Vec3 pos, target, args;

    if (!skip_search) {
        iterator = fn_80201B9C();
        distance = (*(int*)(base + 8) == 2 || *(int*)(base + 8) == 8)
                       ? 120 : *(short*)(state + 0x20);
        while (iterator && !found) {
            void* candidate = fn_80201BC8(iterator);
            if (candidate) {
                fn_8011F114(&pos, candidate);
                category = fn_80201EB8(iterator);
                a = fn_80201B4C(iterator);
                if (*(int*)(base + 8) == category &&
                    fn_80178E94((Vec3*)(state + 0x58 + state[0x1d] * 12), &pos) < (u32)distance &&
                    (a <= 1 || a == 2))
                    found = 1;
            }
            iterator = fn_80201BC0(iterator);
        }
        if (found) {
            ok = fn_80072A2C((Vec3*)(state + 0x58 + state[0x1d] * 12),
                             (Vec3*)(state + 0x4c), distance, 1);
            if (!ok && *(int*)(base + 8) != 2 && *(int*)(base + 8) != 8)
                ok = fn_80072A2C((Vec3*)(state + 0x58 + state[0x1d] * 12),
                                 (Vec3*)(state + 0x4c), 150, 1);
        } else {
            *(Vec3*)(state + 0x4c) = *(Vec3*)(state + 0x58 + state[0x1d] * 12);
        }
    } else {
        *(Vec3*)(state + 0x4c) = *(Vec3*)(state + 0x58 + state[0x1d] * 12);
    }
    if (!ok) return 0;

    category = fn_801D38E8(*(int*)(base + 4));
    if (fn_800CAC5C(*(int*)(state + 0x3c + state[0x1d] * 4), category, &a, &b, &c) != 1)
        return 0;
    fn_80043F44(&args);
    args = *(Vec3*)(state + 0x4c);
    args.z = scale;
    spawned = fn_80034708(&args);
    if (!spawned) return 0;
    selected = fn_80201BC8(spawned);
    if (!selected) { fn_801E8328(28, spawned); return 0; }
    fn_801261F4();
    fn_80201D54(spawned, *(int*)(base + 8));
    fn_80201D24(spawned, 1);
    fn_802015A4(spawned);
    fn_8012C62C(selected, 15, &a, &b, &c, 4);
    fn_8011FA8C(selected, 0x100, 0);
    a = fn_80201B54(spawned);
    *(int*)(state + 0x24) = a;
    if (*(int*)(state + 0x18))
        fn_801DDB84((Vec3*)(state + 0x4c), category,
                    variant ? 2 : 1, selected);
    if (variant) fn_801DE7A0(a);
    fn_8012B7A0(selected, scale);
    fn_80048708(selected);
    if (*(void (**)(void*, int))(base + 0x28))
        (*(void (**)(void*, int))(base + 0x28))(object, *(int*)(base + 0x2c));
    fn_801E8328(1, spawned);

    lbl_8064C308 = lbl_8064D5A8;
    fn_801AC9F4(0x168, 100, (Vec3*)(state + 0x4c), 2);
    category = *(int*)(state + 0x3c + state[0x1d] * 4);
    distance = (category == 4) ? 500 : ((category == 5 || category >= 7) ? 350 : 125);
    pos = *(Vec3*)(state + 0x4c);
    pos.z += distance;
    a = fn_801D3A34(*(int*)(base + 4), 0x4e);
    b = fn_801D3A34(*(int*)(base + 4), 0x35);
    category = fn_801CEB2C(*(int*)(base + 4));
    fn_8014F3A4(&pos, category, b, a, state + 0x84);
    return selected != 0;
}
