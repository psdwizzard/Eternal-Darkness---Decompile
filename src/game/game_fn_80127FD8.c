typedef unsigned char u8;
typedef float Matrix34[3][4];

extern void fn_80127DF8(void*, int, Matrix34);
extern void PSMTXIdentity(Matrix34);
extern void PSMTXTrans(Matrix34, float, float, float);
extern void PSMTXQuat(Matrix34, const Matrix34);
extern void PSMTXConcat(const Matrix34, const Matrix34, Matrix34);

void fn_80127FD8(void* entry, int index, Matrix34 output)
{
    Matrix34 transform;
    Matrix34 local;

    fn_80127DF8(entry, index, output);
    PSMTXIdentity(transform);
    PSMTXTrans(transform, *(float*)((u8*)entry + 0),
                 *(float*)((u8*)entry + 4), *(float*)((u8*)entry + 8));
    PSMTXQuat(local, (const float (*)[4])((u8*)entry + 0x2C));
    PSMTXConcat(transform, local, transform);
    PSMTXConcat(transform, output, output);
}
