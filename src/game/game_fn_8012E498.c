typedef unsigned char u8;

extern void PSMTXQuat(void*, const void*);
extern void PSMTXConcat(void*, void*, void*);

void fn_8012E498(int* initialized, const void* value, void* matrix)
{
    u8 temporary[48];

    if (*initialized != 0) {
        PSMTXQuat(temporary, value);
        PSMTXConcat(temporary, matrix, matrix);
    } else {
        PSMTXQuat(matrix, value);
    }
    *initialized = 1;
}
