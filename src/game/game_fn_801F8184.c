typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef float Matrix34[3][4];

extern void fn_8011F114(Vec3*, void*);
extern void* fn_8011FE34(void*);
extern void PSMTXIdentity(Matrix34);
extern void PSMTXConcat(Matrix34, Matrix34, Matrix34);
extern void PSMTXTrans(Matrix34, float, float, float);
extern void PSMTXQuat(Matrix34, void*);
extern void PSMTXMultVec(Matrix34, Vec3*, Vec3*);

void fn_801F8184(Vec3* output, void* state)
{
    Vec3 translation;
    Vec3 position;
    Matrix34 translation_matrix;
    Matrix34 object_matrix;
    void* object = *(void**)((unsigned char*)state + 0x60);
    void* parent;

    fn_8011F114(&position, object);
    translation = position;
    parent = fn_8011FE34(object);
    PSMTXIdentity(translation_matrix);
    PSMTXTrans(translation_matrix, translation.x, translation.y, translation.z);
    PSMTXQuat(object_matrix, parent);
    PSMTXConcat(translation_matrix, object_matrix, translation_matrix);
    PSMTXMultVec(translation_matrix, output, output);
}
