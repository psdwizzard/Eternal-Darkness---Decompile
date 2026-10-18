typedef unsigned char u8;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec4 { float x, y, z, w; } Vec4;
typedef struct Matrix34 { float m[3][4]; } Matrix34;
typedef struct FourWords { unsigned int words[4]; } FourWords;
typedef union RotationValue { Vec4 vector; FourWords words; } RotationValue;
typedef struct JointQuery {
    int first, second;
    Vec3 position, direction;
    int field20, field24;
} JointQuery;

typedef struct ThrowState {
    u8 pad00[0x50];
    Vec4 rotation;
    Vec3 axis, spin, velocity;
    float angle;
    u8 pad88[0x26];
    u8 flags;
} ThrowState;

extern void *fn_8011F130(void *);
extern int fn_8011F6A4(void *, int, int, int, void *, int);
extern void *fn_8011FE34(void *);
extern void PSVECNormalize(const Vec3 *, Vec3 *);
extern void PSMTXQuat(Matrix34 *, const Vec4 *);
extern void PSMTXInverse(Matrix34 *, Matrix34 *);
extern void PSMTXMultVec(Matrix34 *, const Vec3 *, Vec3 *);
extern void PSVECCrossProduct(const Vec3 *, const Vec3 *, Vec3 *);
extern float PSVECMag(const Vec3 *);
extern float PSVECDotProduct(const Vec3 *, const Vec3 *);
extern float fn_800490E8(float, float);
extern void fn_8017A244(const Vec3 *, Vec4 *, float);
extern void fn_8017A34C(const Vec4 *, const Vec4 *, Vec4 *);
extern void fn_8012CDF0(u8 *, int, FourWords, int);
extern float lbl_8064F814;

void fn_800E9C5C(void *model, ThrowState *state, Vec3 *target)
{
    JointQuery query;
    Matrix34 inverse, rotationMatrix;
    Vec3 direction;
    Vec4 spinRotation;
    RotationValue rotation;
    Vec3 cross;
    float magnitude, dot, angle;
    Vec4 *orientation;
    Vec3 *position;

    position = fn_8011F130(model);
    if (state->flags & 2) {
        fn_8011F6A4(model, 3, 15, -1, &query, 2);
        PSVECNormalize(&state->velocity, &direction);
        orientation = fn_8011FE34(model);
        PSMTXQuat(&rotationMatrix, orientation);
        PSMTXInverse(&rotationMatrix, &inverse);
        PSMTXMultVec(&inverse, &direction, &direction);
        PSVECCrossProduct(&query.direction, &direction, &cross);
        magnitude = PSVECMag(&cross);
        dot = PSVECDotProduct(&query.direction, &direction);
        angle = fn_800490E8(magnitude, dot);
        if (PSVECDotProduct(&cross, &state->axis) < lbl_8064F814) {
            angle = -angle;
        }
        state->angle += angle;
        fn_8017A244(&state->axis, &spinRotation, state->angle);
        fn_8017A34C(&spinRotation, &state->rotation, &rotation.vector);
        fn_8012CDF0(model, 15, rotation.words, 0);
    }
    *position = *target;
}
