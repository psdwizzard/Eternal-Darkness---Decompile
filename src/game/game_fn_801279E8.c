/* fn_801279E8 (0x801279E8, 424 bytes): build a joint's local matrix. */

typedef float Matrix[3][4];

typedef struct Quat {
    float x;
    float y;
    float z;
    float w;
} Quat;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct JointDef {
    char pad0[0xC];
    Matrix mtx;
    void *hasMtx;
    char pad40[0x10];
} JointDef;

typedef struct JointAnim {
    char pad0[0x48];
    void *track;
} JointAnim;

typedef struct ModelData {
    char pad0[0x24];
    JointDef *joints;
} ModelData;

typedef struct Model {
    char pad0[0x3C];
    ModelData *data;
    char pad40[0x154 - 0x40];
    Vec3 *trans;
    Quat *rot;
    char pad15C[0x160 - 0x15C];
    JointAnim *anims;
    char pad164[0x2A8 - 0x164];
    unsigned char *flags;
} Model;

extern unsigned int fn_8011FAEC(void *object);
extern void fn_80210FB0(Matrix m);
extern unsigned int fn_802110A8(const Matrix src, Matrix dst);
extern void fn_802114E0(Matrix m, const Quat *q);
extern void fn_8012E3AC(void *track, Matrix m);
extern const float lbl_80650188;

void fn_801279E8(Model *model, int index, Matrix m, int noOverride) {
    unsigned int state;
    JointAnim *anims;
    JointDef *def;
    void *track;
    int flags;
    Quat *q;
    int bit400;
    int bit20000;

    state = fn_8011FAEC(model);
    def = &model->data->joints[index];
    anims = model->anims;
    bit400 = state & 0x400;
    bit20000 = state & 0x20000;
    if ((anims != 0 && (bit400 != 0 || bit20000 != 0)) || (state & 0x8000)) {
        track = anims[index].track;
    } else {
        if (def->hasMtx != 0) {
            fn_802110A8(def->mtx, m);
        } else {
            fn_80210FB0(m);
        }
        return;
    }
    flags = model->flags[index];
    if (noOverride != 0) {
        flags = 0;
    }
    if (flags & 1) {
        q = &model->rot[index];
        if (q->x == lbl_80650188 && q->y == lbl_80650188 && q->z == lbl_80650188 &&
            q->w == lbl_80650188) {
            fn_80210FB0(m);
        } else {
            fn_802114E0(m, q);
        }
    } else if (def->hasMtx != 0) {
        fn_802110A8(def->mtx, m);
    } else {
        fn_80210FB0(m);
    }
    if (flags & 2) {
        m[0][3] += model->trans[index].x;
        m[1][3] += model->trans[index].y;
        m[2][3] += model->trans[index].z;
    }
    if (track != 0) {
        fn_8012E3AC(track, m);
    }
}
