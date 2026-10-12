typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Search {
    int query[2];
    Vec3 position;
    unsigned char unknown[24];
} Search;

extern void *fn_80201BC8(void *);
extern int fn_8011F598(void *, int, int, int, Search *, unsigned char);
extern void *fn_80201B94(void *);
extern int fn_80201B54(void *);
extern void *fn_80201C48(void *);
extern void *fn_80201814(int);
extern int fn_8011EB04(void *);
extern unsigned long long fn_8020123C(int, int, int, int);
extern void fn_80067180(int);
extern void fn_800CEA1C(int, int, void *, void *, int, unsigned char,
                       void *, float, float, float);
extern void fn_8014D478(void *, Vec3 *, float *, int, int, int *, int);
extern int fn_800C77B4(int, void *);

extern Vec3 lbl_80239890;
extern int lbl_802FC5BC[];
extern float lbl_8064F228;
extern float lbl_8064F21C;
extern float lbl_8064F22C;

int fn_800C7918(int unused, void *object)
{
    int owner;
    register int target;
    register void *runtime;
    unsigned long objectAddress = (unsigned long)object;
    register void *parent;
    register Vec3 *position;
    register int *effect;
    register void *other;
    Vec3 direction;
    Search search;

    runtime = fn_80201BC8((void *)objectAddress);
    if (fn_8011F598(runtime, 2, 15, -1, &search, 1) != -1) {
        direction = lbl_80239890;
        parent = fn_80201B94((void *)objectAddress);
        owner = fn_80201B54((void *)objectAddress);
        target = (int)fn_80201C48(parent);
        other = fn_80201814(target);
        fn_80201BC8(other);
        fn_8011EB04(runtime);
        fn_8020123C(8, owner, target, 0);
        fn_80067180((int)other);
        position = &search.position;
        effect = lbl_802FC5BC + 6;
        fn_800CEA1C(0x17, 3, position, 0, 5, 20, effect,
                    lbl_8064F228, lbl_8064F21C, lbl_8064F22C);
        fn_8014D478(runtime, position, &direction.x, 15, 10, effect, 3);
    }
    fn_800C77B4(0, (void *)objectAddress);
    return 1;
}
