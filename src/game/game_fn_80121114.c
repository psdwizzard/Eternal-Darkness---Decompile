typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef float Mtx[3][4];
typedef struct InputStorage InputStorage;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Color {
    u8 r, g, b, a;
} Color;

typedef struct Model {
    u8 pad00[0x1E];
    u16 count;
    u8 pad20[0x28];
    void* palette;
} Model;

typedef struct Target {
    u32 flags;
} Target;

typedef struct Owner {
    Vec3 position;
    u8 pad0C[8];
    float height;
    u8 pad18[0x14];
    float rotation[4];
    Model* model;
    u8 pad40[0x134];
    struct Owner* parent;
    u8 pad178[0xCC];
    s32 kind;
    u8 pad248[0xC];
    u32 flags;
    u8 pad258[0x20];
    float scale;
    u8 pad27C[0x24];
    Target* target;
    u8 pad2A4[8];
    float frame;
    float light_dir[3];
    float light_value;
    u8 pad2C0[0x10];
    u16 draw_flags;
    u16 light_flags;
    s16 light_param;
    u8 pad2D6[8];
    u8 fade;
} Owner;

typedef struct Material {
    u8 pad00[0x1F];
    u8 alpha;
} Material;

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define CLAMP01(x) ((1.0f < MAX(x, 0.0f)) ? lbl_806500A4 : MAX(x, 0.0f))

extern Vec3 lbl_8063D378;
extern Vec3 lbl_804ED5C0;
extern Mtx lbl_8063C068;
extern Mtx lbl_8063BF68[][2];
extern Material lbl_8024EDE8;
extern s32 lbl_8064B9D4;
extern Owner* lbl_8064C4E4;
extern float lbl_8064CF08;
extern s32 lbl_8064D738;
extern float lbl_806500A0;
extern float lbl_806500A4;
extern float lbl_806500C4;
extern float lbl_806500CC;
extern float lbl_806500D0;
extern float lbl_806500D4;
extern float lbl_806500D8;
extern float lbl_806500DC;
extern float lbl_806500E0;
extern float lbl_806500E4;
extern float lbl_806500E8;
extern float lbl_806500EC;
extern float lbl_806500F0;

extern u32 fn_80048668(void);
extern void fn_8011F114(Vec3*, Vec3*);
extern void* fn_8011FA6C(Owner*, s32);
extern void* fn_8011FA7C(Owner*, s32);
extern u32 fn_8011FAEC(Owner*);
extern u32 fn_8011FAF4(void*);
extern void* fn_8011FB4C(void*);
extern void* fn_8011FB6C(void*);
extern Owner* fn_8011FE34(Owner*);
extern s32 fn_8011FF38(void);
extern void fn_80120098(Owner*);
extern void fn_801208CC(Mtx, float*, float*);
extern void fn_80122638(Owner*, s32, s32, s32, s32, s32, float, float);
extern void fn_801227A0(Owner*, s32, s32);
extern void fn_80122AD4(Owner*, s32, s32, float);
extern u16 fn_801231C0(const Model*);
extern float fn_80123708(Owner*, s32);
extern s32 fn_80126050(Owner*);
extern u16 fn_8012DBE8(Owner*, s32, Color*);
extern void fn_80130720(Owner*);
extern s32 fn_80130998(s32, float);
extern float fn_8017968C(Vec3*, Vec3*);
extern void fn_801ECD48(s32);
extern void fn_801ECEC8(u8, s32, u8);
extern void fn_801ED118(void);
extern u32 fn_801ED3F4(u32);
extern void fn_801ED468(s32);
extern s32 fn_801ED56C(s32);
extern s32 fn_801ED59C(s32, s32);
extern void fn_801ED5F4(s32, s32, s16, float*, Mtx, float);
extern s32 fn_801EDA7C(s16*, s32, s32, void*);
extern void fn_801EFFE4(s32);
extern void fn_801F10BC(s32, s32, s32);
extern void fn_801F1528(s32);
extern s32 fn_801F1A38(Vec3*, Vec3*, InputStorage*, s32, s32, s32, float);
extern void fn_801F3FD8(Vec3*, s32);
extern void fn_801F4380(Vec3*);
extern void PSMTXIdentity(Mtx);
extern void PSMTXConcat(const Mtx, const Mtx, Mtx);
extern u32 PSMTXInverse(const Mtx, Mtx);
extern u32 PSMTXInvXpose(const Mtx, Mtx);
extern void PSMTXTrans(Mtx, float, float, float);
extern void PSMTXScale(Mtx, float, float, float);
extern void PSMTXQuat(Mtx, float*);
extern void PSMTXMultVec(const Mtx, const Vec3*, Vec3*);
extern void GXSetArray(s32, const void*, u8);
extern void GXFlush(void);
extern void GXSetBlendMode(s32, s32, s32, s32);
extern void GXSetColorUpdate(u8);
extern void GXSetAlphaUpdate(u8);
extern void GXLoadPosMtxImm(Mtx, s32);
extern void GXLoadNrmMtxImm(Mtx, s32);
extern void GXLoadTexMtxImm(Mtx, s32, s32);
extern void* memcpy(void*, const void*, u32);

void fn_80121114(Owner* owner, InputStorage* input, s32 mode, s32 draw, s32 outline, s32 fog)
{
    u32 flags;
    u32 attr;
    void* color0;
    void* color1;
    Model* model;
    float frame;
    Vec3* camera;
    s32 hidden;
    s32 layer;
    s32 kind;
    s32 drawn;
    float* lit;
    s32 saved_light;
    s32 saved_state;
    float scale;
    float alpha;
    Owner* parent;
    s32 group;
    s32 rflags;
    s32 fade;
    s32 visible;
    float clamp;
    float total;
    float level;
    Vec3 pos1;
    Vec3 pos2;
    Vec3 pos3;
    float axis1[4];
    float axis2[4];
    Vec3 got1;
    Vec3 got2;
    Vec3 got3;
    Mtx matrix;
    Mtx rot;
    Mtx inverse;
    Mtx copy;
    Mtx tex;
    Mtx temp;
    Mtx shadow0;
    Mtx shadow1;
    Mtx outline_mtx;
    Mtx offset;
    Color color;
    register s32 format;

    flags = fn_8011FAEC(owner);
    attr = fn_8011FAF4(owner);
    color0 = fn_8011FA6C(owner, lbl_8064D738);
    color1 = fn_8011FA7C(owner, lbl_8064D738);
    model = owner->model;
    frame = owner->frame;
    camera = &lbl_8063D378;
    hidden = flags & 8;
    layer = 1;
    drawn = 0x9C4;
    lit = 0;

    if (owner->target == 0 || lbl_806500A0 == frame) {
        return;
    }
    if (!(flags & 0x80000)) {
        return;
    }
    if (!fn_80126050(owner)) {
        return;
    }
    if (flags & 0x10000000) {
        if (owner->target->flags & 2) {
            return;
        }
    } else if (owner->target->flags & 2) {
        return;
    }

    if (owner->kind == 0x68) {
        saved_state = fn_801ED56C(0);
    }
    if (owner->light_flags != 0) {
        saved_light = fn_801ED59C(0, 1);
    }
    if (owner == lbl_8064C4E4 || owner->parent == lbl_8064C4E4) {
        fn_801ECD48(1);
    } else {
        fn_801ECD48(0);
    }
    kind = fn_80130998(model->count, frame);
    if (owner == lbl_8064C4E4) {
        layer = 4;
    }
    fn_801ED3F4((u32)fn_8011FB6C(owner));
    scale = fn_8017968C(&owner->position, camera);
    GXSetArray(9, color0, 6);
    GXSetArray(10, color1, 6);
    GXSetArray(13, model->palette, 4);
    fn_801231C0(model);
    /* ASM: mr consumes the callee's zero-extended result without C's
     * redundant u16-to-int mask. */
    asm { mr format, r3 }
    fn_801EFFE4(format);
    fn_801F10BC(0, 0, 0);

    if (!hidden) {
        if (input != 0) {
            fn_8011F114(&got1, &owner->position);
            pos1 = got1;
            parent = fn_8011FE34(owner);
            group = (s32)fn_8011FB4C(owner);
            alpha = owner->scale;
            rflags = 0;
            fn_80048668();
            /* ASM: cmpwi and beq retain the signed status comparison;
             * MWCC discards a C signed cast and emits cmplwi. */
            asm {
                cmpwi r3, 0
                beq expansion_done
            }
            if ((u16)attr & 0x800) {
                alpha *= lbl_806500CC;
            } else if ((u16)attr & 0x400) {
                alpha *= lbl_806500D0;
            }
            /* ASM: expansion_done is the target of the signed status test. */
            asm { expansion_done: }
            if (flags & 0x10000) {
                rflags |= 1;
            }
            if (flags & 1) {
                rflags |= 2;
            }
            if (owner->flags & 0x40000) {
                alpha *= lbl_806500C4;
            }
            if (owner->fade != 0) {
                alpha *= owner->fade * lbl_806500D4 + lbl_806500A4;
            }
            drawn = fn_801F1A38(&pos1, &parent->position, input, group, layer, rflags, alpha);
        } else {
            fn_8011F114(&got2, &owner->position);
            pos2 = got2;
            fn_801F3FD8(&pos2, mode);
        }
    } else if (!(attr & 0x20)) {
        fn_8011F114(&got3, &owner->position);
        pos3 = got3;
        fn_801F4380(&pos3);
    }

    if (!(owner->draw_flags & 0x100)) {
        fn_801F1528(0);
    }
    GXFlush();
    PSMTXIdentity(matrix);
    PSMTXTrans(matrix, owner->position.x, owner->position.y, owner->position.z);
    PSMTXQuat(rot, owner->rotation);
    PSMTXConcat(matrix, rot, matrix);
    PSMTXInverse(matrix, inverse);
    PSMTXMultVec(inverse, &lbl_8063D378, &lbl_804ED5C0);
    if (owner->light_flags & 0x4000) {
        memcpy(copy, matrix, sizeof(Mtx));
        lit = copy[0];
        fn_801ED5F4(1, 0x4000, owner->light_param, owner->light_dir, (float(*)[4])lit,
                    owner->light_value);
    }
    lbl_804ED5C0.x *= lbl_806500D8;
    lbl_804ED5C0.y *= lbl_806500D8;
    lbl_804ED5C0.z *= lbl_806500D8;

    PSMTXConcat(matrix, lbl_8063C068, tex);
    PSMTXInvXpose(tex, tex);
    PSMTXScale(temp, lbl_806500DC, lbl_806500E0, lbl_806500A0);
    PSMTXConcat(temp, tex, tex);
    PSMTXTrans(temp, lbl_806500E4, lbl_806500E4, lbl_806500A4);
    PSMTXConcat(temp, tex, tex);
    GXLoadTexMtxImm(tex, 0x30, 1);
    PSMTXConcat(lbl_8063BF68[lbl_8064D738][0], matrix, shadow0);
    PSMTXConcat(lbl_8063BF68[lbl_8064D738][1], matrix, shadow1);
    PSMTXConcat(lbl_8063C068, matrix, matrix);
    GXLoadTexMtxImm(shadow0, 0x36, 0);
    GXLoadTexMtxImm(shadow1, 0x39, 0);
    GXLoadPosMtxImm(matrix, 0);
    GXLoadNrmMtxImm(matrix, 0);
    fn_801ED468(0);

    level = drawn / lbl_806500E8;
    if (fog) {
        if (owner->flags & 0x1000000) {
            fn_801ECEC8(1, 3, 0);
        } else {
            fn_801ECEC8(1, 3, 1);
        }
    }
    if (fog) {
        GXSetBlendMode(1, 4, 5, 0xF);
        GXSetAlphaUpdate(1);
    }
    fn_80122638(owner, kind, layer, draw, 0, (s32)lit, scale, level);
    if (fog) {
        GXSetAlphaUpdate(0);
    }
    if (draw) {
        if (outline) {
            fn_801227A0(owner, kind, 1);
        } else {
            fn_801227A0(owner, kind, 0);
        }
    }
    if (draw && (owner->flags & 0x20000000) && fn_8011FF38()) {
        fn_80120098(owner);
        GXSetArray(9, color0, 6);
        GXSetArray(10, color1, 6);
        GXSetArray(13, model->palette, 4);
    }

    if ((owner->flags & 0x100) && draw && !outline) {
        scale = fn_80123708(owner, 1);
        total = lbl_8064B9D4;
        clamp = lbl_8064CF08 - lbl_806500EC;
        fade = total * (1.0f - CLAMP01(clamp));
        visible = 0;
        if ((owner->frame != scale || scale > lbl_806500F0) && fade != 0) {
            visible = 1;
        }
        if (owner == lbl_8064C4E4) {
            fade = lbl_8064B9D4;
            visible = 1;
        }
        if (visible) {
            PSMTXIdentity(matrix);
            PSMTXTrans(matrix, owner->position.x, owner->position.y, owner->position.z);
            PSMTXQuat(rot, owner->rotation);
            PSMTXConcat(matrix, rot, matrix);
            axis1[0] = 0.0f;
            axis1[1] = 0.0f;
            axis1[2] = 1.0f;
            axis1[3] = 0.0f;
            axis2[0] = 0.0f;
            axis2[1] = 0.0f;
            axis2[2] = 1.0f;
            axis2[3] = 0.0f;
            fn_801208CC(outline_mtx, axis1, axis2);
            outline_mtx[2][3] += lbl_806500C4;
            if (owner->draw_flags & 0x2000) {
                PSMTXConcat(outline_mtx, matrix, matrix);
                PSMTXTrans(offset, lbl_806500A0, lbl_806500A0, owner->height);
                PSMTXConcat(offset, matrix, matrix);
            } else {
                PSMTXConcat(matrix, outline_mtx, matrix);
            }
            PSMTXConcat(lbl_8063C068, matrix, matrix);
            GXLoadPosMtxImm(matrix, 3);
            fn_801ED468(3);
            fn_801ED118();
            fn_8012DBE8(owner, 0xF, &color);
            lbl_8024EDE8.alpha = 0xFF - ((0 > color.a - fade) ? 0 : color.a - fade);
            fn_801EDA7C((s16*)&lbl_8024EDE8, 0, 0, 0);
            if (fog) {
                GXSetAlphaUpdate(1);
                GXSetColorUpdate(0);
            }
            GXSetBlendMode(2, 1, 0, 3);
            fn_801F10BC(0, 0, 0);
            fn_80122AD4(owner, 7, 0, scale);
            if (!(owner->draw_flags & 0x4000)) {
                fn_80122AD4(owner, 7, 1, scale);
            }
            GXSetBlendMode(1, 4, 5, 0);
            if (fog) {
                GXSetColorUpdate(1);
                GXSetAlphaUpdate(0);
            }
        }
    }

    if (owner->light_flags != 0) {
        fn_801ED5F4(0, 0, 0, 0, 0, lbl_806500A0);
        fn_801ED59C(saved_light, 1);
    }
    fn_801ECD48(0);
    fn_80130720(owner);
    if (owner->kind == 0x68) {
        fn_801ED56C(saved_state);
    }
}
