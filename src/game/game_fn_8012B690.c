typedef float Matrix8012B690[12];

extern void PSMTXQuat(Matrix8012B690, const void*);
extern void PSMTXMultVec(Matrix8012B690, const void*, const void*);
extern void PSVECAdd(const void*, const void*, void*);

void fn_8012B690(void* owner, const void* value, void* output)
{
    Matrix8012B690 matrix;

    PSMTXQuat(matrix, (char*)owner + 0x2C);
    PSMTXMultVec(matrix, value, output);
    PSVECAdd(owner, output, output);
}
