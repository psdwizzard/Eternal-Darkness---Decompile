/* fn_80127DF8 (0x80127DF8, 408 bytes): build a joint's world matrix by
 * walking up the joint hierarchy (and into an attached parent model). */

typedef float Matrix[3][4];

typedef struct JointDef {
    float scale[3];
    Matrix mtx;
    struct JointDef *parent;
    char pad40[0x44 - 0x40];
    unsigned int flags;
    unsigned int parentJoint;
    char pad4C[0x50 - 0x4C];
} JointDef;

typedef struct ModelData {
    char pad0[0x24];
    JointDef *joints;
} ModelData;

typedef struct ModelExt {
    char pad0[0x700];
    void *track;
} ModelExt;

typedef struct Model {
    char pad0[0x3C];
    ModelData *data;
    char pad40[0x174 - 0x40];
    struct Model *attachParent;
    char pad178[0x2A4 - 0x178];
    ModelExt *ext;
} Model;

extern void *fn_80128E6C(void *);
extern int fn_80124128(Model *, unsigned int);
extern void fn_801279E8(Model *model, int index, Matrix m, int noOverride);
extern void fn_8012E3AC(void *track, Matrix m);
extern void PSMTXIdentity(Matrix m);
extern void PSMTXConcat(const Matrix a, const Matrix b, Matrix out);
extern void PSMTXInverse(const Matrix src, Matrix dst);
extern void PSMTXScale(Matrix m, float x, float y, float z);

void fn_80127DF8(Model *model, int index, Matrix m) {
    Matrix parentMtx;
    Matrix inv;
    Matrix scaleMtx;
    ModelData *data;
    JointDef *joint;
    Model *parent;
    unsigned int attached;
    void *track;
    int parentIndex;

    data = model->data;
    joint = &data->joints[index];
    fn_80128E6C(model);
    parent = model->attachParent;
    if (parent == 0) {
        parent = model;
    }
    attached = data->joints[index].flags & 1;
    if (model == parent || attached == 0) {
        if (attached == 0) {
            fn_801279E8(model, index, m, attached);
            if (joint->parent != 0) {
                fn_80127DF8(model, joint->parent - data->joints, parentMtx);
                PSMTXConcat(parentMtx, m, m);
            }
        } else {
            track = model->ext->track;
            PSMTXIdentity(m);
            if (track != 0) {
                fn_8012E3AC(track, m);
            }
        }
    } else {
        parentIndex = fn_80124128(parent, data->joints[index].parentJoint);
        fn_80127DF8(parent, parentIndex, m);
        if (data->joints[index].parent != 0) {
            PSMTXScale(scaleMtx, data->joints[index].scale[0], data->joints[index].scale[1],
                        data->joints[index].scale[2]);
            PSMTXConcat(scaleMtx, data->joints[index].mtx, scaleMtx);
            PSMTXInverse(scaleMtx, inv);
            PSMTXConcat(data->joints[index].parent->mtx, inv, inv);
            PSMTXConcat(m, inv, m);
        }
    }
}
