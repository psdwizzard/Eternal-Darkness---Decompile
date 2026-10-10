typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float Matrix[3][4];

typedef struct Joint {
    float scale[3];
    Matrix transform;
    struct Joint* parent;
    u32 key;
    u32 flags;
    u32 attachedKey;
    u32 pad4C;
} Joint;

typedef struct Table {
    u8 pad00[8];
    u16 count;
    u8 pad0A[0x1A];
    Joint* joints;
} Table;

typedef struct Runtime {
    u8 pad00[0x700];
    void* transform;
} Runtime;

typedef struct Owner {
    u8 pad00[0x3C];
    Table* table;
    u8 pad40[0x134];
    struct Owner* attached;
    u8 pad178[0x12C];
    Runtime* runtime;
} Owner;

extern Matrix lbl_804F02F0[];
extern Matrix lbl_804F1CA0[];
extern float lbl_80650110;
extern void* fn_80128E6C(void*);
extern int fn_80124128(Owner*, u32);
extern void fn_801279E8(void*, int, Matrix, u32);
extern void fn_80127DF8(void*, int, Matrix);
extern void fn_8012E3AC(void*, void*);
extern void fn_80210FB0(Matrix);
extern void fn_80210FDC(const Matrix, const Matrix, Matrix);
extern u32 fn_802110A8(const Matrix, Matrix);

void fn_80124180(Owner* owner, int independent)
{
    Matrix inverse;
    Matrix scaled;
    Matrix relative;
    Matrix local;
    Matrix scale;
    int i;
    Table* table = owner->table;
    Joint* joint;
    Matrix* world;
    Matrix* output;
    u32 attached;

    fn_80128E6C(owner);
    joint = table->joints;
    i = 0;
    output = lbl_804F02F0;
    world = lbl_804F1CA0;
    /* The diagonal is filled from each joint before concatenation. */
    scale[0][1] = lbl_80650110;
    scale[0][2] = lbl_80650110;
    scale[0][3] = lbl_80650110;
    scale[1][0] = lbl_80650110;
    scale[1][2] = lbl_80650110;
    scale[1][3] = lbl_80650110;
    scale[2][0] = lbl_80650110;
    scale[2][1] = lbl_80650110;
    scale[2][3] = lbl_80650110;

    for (; i < table->count; world++, joint++, output++, i++) {
        attached = joint->flags & 1;
        if (owner == owner->attached || attached == 0) {
            if (attached == 0) {
                if (joint->parent != 0 && independent == 0) {
                    Matrix* parent = &lbl_804F1CA0[joint->parent - table->joints];
                    fn_801279E8(owner, i, local, attached);
                    fn_80210FDC(*parent, local, *world);
                } else {
                    fn_801279E8(owner, i, *world, attached);
                }
            } else {
                void* transform = owner->runtime->transform;
                fn_80210FB0(*world);
                if (transform != 0) {
                    fn_8012E3AC(transform, *world);
                }
            }
        } else {
            int index = fn_80124128(owner->attached, joint->attachedKey);
            if (joint->parent != 0) {
                /* Express the attached joint relative to this joint's parent. */
                fn_80127DF8(owner->attached, index, local);
                scale[0][0] = joint->scale[0];
                scale[1][1] = joint->scale[1];
                scale[2][2] = joint->scale[2];
                fn_80210FDC(scale, joint->transform, scaled);
                fn_802110A8(scaled, inverse);
                fn_80210FDC(joint->parent->transform, inverse, relative);
                fn_80210FDC(local, relative, *world);
            } else {
                fn_80127DF8(owner->attached, index, *world);
            }
        }
        scale[0][0] = joint->scale[0];
        scale[1][1] = joint->scale[1];
        scale[2][2] = joint->scale[2];
        fn_80210FDC(scale, joint->transform, inverse);
        fn_80210FDC(*world, inverse, *output);
    }
}
