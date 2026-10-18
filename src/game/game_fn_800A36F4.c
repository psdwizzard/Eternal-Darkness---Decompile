typedef unsigned char u8;

typedef struct Vec800A36F4 { float x, y, z; } Vec800A36F4;
typedef struct Matrix800A36F4 { float v[3][4]; } Matrix800A36F4;
typedef struct Object800A36F4 { u8 pad0[0x160]; void* active; } Object800A36F4;

extern void *fn_80201BC8();
extern void fn_8011F114();
extern void PSVECSubtract();
extern int fn_800A4F44(Vec800A36F4*, float);
extern void PSVECNormalize(Vec800A36F4*, Vec800A36F4*);
extern float fn_8011F6F8(void*);
extern void PSVECScale(Vec800A36F4*, Vec800A36F4*, float);
extern void PSVECAdd(void*, Vec800A36F4*, Vec800A36F4*);
extern void fn_8012AC74(void*, Vec800A36F4*, int);
extern float lbl_8064EE94;

int fn_800A36F4(Object800A36F4* object, Matrix800A36F4* matrix, void* arg)
{
    Vec800A36F4 result;
    Vec800A36F4 delta;
    Vec800A36F4 scaled;
    Vec800A36F4 origin;
    void* target;
    float amount;

    if (object->active != 0) {
        target = fn_80201BC8(arg);
        fn_8011F114(&origin, target);
        PSVECSubtract(&origin, matrix, &delta);
        if (fn_800A4F44(&delta, matrix->v[0][3]) > 0) {
            PSVECNormalize(&delta, &delta);
            amount = matrix->v[0][3] - fn_8011F6F8(target);
            amount *= lbl_8064EE94;
            PSVECScale(&delta, &scaled, amount);
            PSVECAdd(matrix, &scaled, &result);
            result.z = origin.z;
            fn_8012AC74(target, &result, 3);
        }
    }
    return 0;
}
