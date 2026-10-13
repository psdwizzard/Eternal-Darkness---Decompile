typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Vec4 {
    float x, y, z, w;
} Vec4;

typedef float Matrix34[3][4];

typedef struct SearchResult {
    int second;
    int first;
    Vec3 rotation;
    Vec3 position;
    float value;
} SearchResult;

typedef struct EffectModel {
    u8 pad00[0x1E];
    u16 name;
    u8 pad20[0x14];
    void* colors;
    u8 pad38[0x10];
    void* indices;
    u8 pad4C[4];
    void* vertices;
    u8 pad54[0x14];
    int texture;
} EffectModel;

typedef struct EffectObject {
    u8 pad000[0x27C];
    float scale;
    u8 pad280[0x5A];
    u8 alpha;
    s8 alpha_step;
    u8 depth;
    u8 size;
} EffectObject;

typedef struct DrawState {
    u8 pad00[0x18];
    unsigned flags;
} DrawState;

extern void fn_80225F4C(int attribute, void* data, int format);
extern void fn_801ECEC8(int first, int second, int third);
extern int fn_801204E0(EffectObject* object);
extern unsigned int fn_8011FAF4(EffectObject* object);
extern int fn_80120558(EffectObject* object, unsigned value);
extern int fn_8011F598(EffectObject* object, int first, int second,
                       int previous, SearchResult* result, u8 options);
extern int fn_801ED3F4(int value);
extern void fn_80211B64(const Vec3* a, const Vec3* b, Vec3* out);
extern float fn_80211B08(const Vec3* v);
extern void fn_80211AAC(const Vec3* v, Vec3* out);
extern float fn_80211B44(const Vec3* a, const Vec3* b);
extern float fn_800490E8(float a, float b);
extern void fn_8017A244(const Vec3* axis, Vec4* out, float angle);
extern void fn_802114B8(Matrix34 m, float x, float y, float z);
extern void fn_802114E0(Matrix34 m, Vec4* rotation);
extern void fn_80211484(Matrix34 m, float x, float y, float z);
extern void fn_80210FDC(Matrix34 a, Matrix34 b, Matrix34 out);
extern void fn_8022B690(Matrix34 m, int index);
extern void fn_801ECF50(int mode);
extern void fn_801EDA7C(void* destination, int manager, int type, int value);
extern void fn_80226D28(int value);
extern void fn_80226AB4(int first, int second, int third);
extern void fn_801231AC(s16 x, s16 y, s16 z);
extern void fn_8012319C(float s, float t);
extern void fn_80123198(void);
extern void fn_8011FF40(EffectModel* model, unsigned flags, void* name,
                        int alpha, EffectObject* object);
extern unsigned int fn_8011FA8C(EffectObject* object, int flags, int value);

extern EffectModel* lbl_8064CEB0;
typedef struct PartIds {
    unsigned id[6];
} PartIds;

/* { 0.0f, 0.0f, 1.0f } */
extern const Vec3 lbl_8023A690;
/* { 0, 8, 9, 2, 3, 1 } */
extern const PartIds lbl_8023A69C;
extern DrawState lbl_80332500;
extern DrawState lbl_80332520;
extern Matrix34 lbl_8063C068;
extern int lbl_8064D224;
extern int lbl_8064D790;
extern float lbl_80650098;
extern float lbl_8065009C;
extern float lbl_806500A0;
extern float lbl_806500A4;

void fn_80120098(EffectObject* object)
{
    int pass;
    EffectModel* model = lbl_8064CEB0;
    Vec3 up = lbl_8023A690;

    if (model != 0) {
        SearchResult result;
        Matrix34 rotate;
        Matrix34 world;
        Matrix34 scale;
        PartIds ids = lbl_8023A69C;
        Vec3 axis;
        Vec4 rotation;
        int alpha;
        int step;
        float sine;
        float depth;
        s16 size;
        int ok;
        int saved;
        int visible;
        unsigned j;
        float cosine;

        alpha = object->alpha;
        step = object->alpha_step;
        size = object->size * (alpha / lbl_80650098);
        depth = object->depth * (alpha / lbl_8065009C);
        fn_80225F4C(9, model->vertices, 6);
        fn_80225F4C(10, model->colors, 6);
        fn_80225F4C(13, model->indices, 4);
        fn_801ECEC8(1, 3, 0);
        ok = fn_801204E0(object);
        for (pass = 9; pass <= 10 && ok != 0; pass++) {
            for (j = 0; j < 6; j++) {
                visible = 1;
                if (!(fn_8011FAF4(object) & 0x200)) {
                    visible = fn_80120558(object, ids.id[j]);
                }
                if (visible == 0) {
                    continue;
                }
                if (fn_8011F598(object, pass, ids.id[j], -1, &result, 1) == -1) {
                    continue;
                }
                saved = fn_801ED3F4(lbl_8064D224);

                /* Rotate the quad from +Z onto the part's position. */
                fn_80211B64(&up, &result.position, &axis);
                sine = fn_80211B08(&axis);
                fn_80211AAC(&axis, &axis);
                cosine = fn_80211B44(&up, &result.position);
                fn_8017A244(&axis, &rotation, fn_800490E8(sine, cosine));
                fn_802114B8(scale, object->scale, object->scale, depth);
                fn_802114E0(rotate, &rotation);
                fn_80211484(world, result.rotation.x, result.rotation.y,
                            result.rotation.z);
                fn_80210FDC(rotate, scale, rotate);
                fn_80210FDC(world, rotate, world);
                fn_80210FDC(lbl_8063C068, world, world);
                fn_8022B690(world, 0);

                fn_801ECF50(8);
                if (fn_8011FAF4(object) & 1) {
                    fn_801EDA7C(&lbl_80332520, lbl_8064D790, 0x2BF, 0);
                } else {
                    fn_801EDA7C(&lbl_80332500, lbl_8064D790, 0x2BF, 0);
                }
                lbl_80332500.flags |= 0x80000000;
                fn_80226D28(0);
                fn_80226AB4(0x80, 2, 4);
                fn_801231AC(-size * 32, size * 32, 0x500);
                fn_8012319C(lbl_806500A0, lbl_806500A0);
                fn_801231AC(size * 32, size * 32, 0x500);
                fn_8012319C(lbl_806500A4, lbl_806500A0);
                fn_801231AC(size * 32, -size * 32, 0x500);
                fn_8012319C(lbl_806500A4, lbl_806500A4);
                fn_801231AC(-size * 32, -size * 32, 0x500);
                fn_8012319C(lbl_806500A0, lbl_806500A4);
                fn_80123198();
                fn_80226D28(1);

                fn_801ED3F4(model->texture);
                fn_8011FF40(model, 0, (void*)model->name, alpha, object);
                fn_801ED3F4(saved);
            }
        }

        /* Pulse the alpha between 5 and 0xC3; fading out ends the effect. */
        alpha += step;
        if (alpha > 0xC3) {
            alpha = 0xC3;
            step = -1;
        } else if (alpha < 5) {
            alpha = 0;
            step = 5;
            fn_8011FA8C(object, 0x20000000, 0);
        }
        object->alpha = alpha;
        object->alpha_step = step;
    }
}
