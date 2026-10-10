typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct SearchResult {
    unsigned char pad[8];
    Vec3 position;
    unsigned char pad2[20];
} SearchResult;

typedef struct Actor {
    unsigned char pad[0x90];
    int unk90;
} Actor;

extern void *fn_80201BC8(void *object);
extern Vec3 *fn_8011F130(void *model);
extern void *fn_80200C38(int id);
extern void *fn_801A7498(void *node);
extern void *fn_80201814(void *object);
extern void *fn_80205288(void *object);
extern int fn_800FBFB0(void);
extern int fn_801AC9F4(unsigned short sound, int volume, Vec3 *position, int flags);
extern int fn_8006AEA4(void *object);
extern Actor *fn_80201B8C(void *object);
extern int fn_80072354(int value);
extern void *fn_801A7770(void *node);
extern int fn_8006B0F0(void *data, void *object, int value, void *node);
extern int fn_801207F0(void *model);
extern void fn_801A7688(void *node, int index, Vec3 *out);
extern void fn_801795A4(Vec3 *a, Vec3 *b, Vec3 *out);
extern void fn_80179A18(Vec3 *v);
extern void fn_801798DC(Vec3 *v, float scale);
extern void *fn_80205868(void *model, int index, Vec3 *dir, int flags);
extern int fn_80201B54(void *object);
extern void fn_8020104C(int, int, int, int, float);
extern void fn_8012C478(void *model, int index, int arg);
extern int fn_8011F6A4(void *model, int, int, int, SearchResult *, int);
extern void fn_8006B0A0(Vec3 *position);
extern Vec3 fn_8006AFA0(Vec3 *position);
extern void fn_8006A9D0(void *object, int arg1, int id, int *out);
extern void fn_8006B1C0(void);

extern unsigned short lbl_80243ED0[];
extern float lbl_8064E798;
extern float lbl_8064E79C;

void fn_8006A740(void *object, int arg1, int id, int *out) {
    Vec3 dir;
    Vec3 b;
    Vec3 a;
    SearchResult result;
    void *node;
    void *model;
    Vec3 *position;
    int index;
    unsigned short sound;
    void *hit;

    model = fn_80201BC8(object);
    position = fn_8011F130(model);
    node = fn_80200C38(id);
    if (fn_80205288(fn_80201814(fn_801A7498(node))) != 0) {
        if (out != 0) {
            *out = 0x13;
        }
        fn_801AC9F4(fn_800FBFB0() % 5 + 0x2E, 100, position, 2);
        sound = lbl_80243ED0[fn_800FBFB0() % 5];
        fn_801AC9F4(sound, 50, position, 2);
        if (fn_8006AEA4(object) != 0) {
            arg1 = fn_80072354(fn_80201B8C(object)->unk90);
            index = fn_8006B0F0(fn_801A7770(node), object, arg1, node);
            if (index == 0 || index == 2 || index == 3) {
                if (fn_801207F0(model) != 0) {
                    fn_801A7688(node, 0, &b);
                    fn_801A7688(node, 2, &a);
                    fn_801795A4(&a, &b, &dir);
                    fn_80179A18(&dir);
                    fn_801798DC(&dir, lbl_8064E798);
                    hit = fn_80205868(model, index, &dir, 0x2000);
                    if (hit != 0) {
                        fn_8020104C(0x11, 0, fn_80201B54(hit), 0, lbl_8064E79C);
                    }
                } else {
                    fn_8012C478(model, index, 0);
                }
                if (fn_8011F6A4(model, 0x14, index, -1, &result, 1) != -1) {
                    fn_8006B0A0(&result.position);
                }
            } else {
                Vec3 pos = fn_8006AFA0(position);
                fn_8006B0A0(&pos);
            }
        } else {
            fn_8006A9D0(object, arg1, id, out);
            fn_8006B1C0();
        }
    } else {
        if (out != 0) {
            *out = 0x13;
        }
        fn_801AC9F4(0x1C9, 100, position, 2);
    }
}
