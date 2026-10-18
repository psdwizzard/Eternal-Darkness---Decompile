typedef float Matrix8012B6FC[12];

extern void PSMTXQuat(Matrix8012B6FC, const void*);
extern void PSMTXMultVec(Matrix8012B6FC, const void*, const void*);

void fn_8012B6FC(void* owner, const void* value, const void* output)
{
    Matrix8012B6FC matrix;

    PSMTXQuat(matrix, (char*)owner + 0x2C);
    PSMTXMultVec(matrix, value, output);
}
