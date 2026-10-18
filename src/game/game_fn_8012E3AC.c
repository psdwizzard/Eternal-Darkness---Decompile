typedef unsigned char u8;

extern int fn_8012E200(void*, int, void*);
extern void PSMTXConcat(void*, void*, void*);

void fn_8012E3AC(void* entry, void* matrix)
{
    u8 value[48];

    if (fn_8012E200(entry, 0, value)) {
        PSMTXConcat(matrix, value, matrix);
    }
    if (fn_8012E200(entry, 1, value)) {
        PSMTXConcat(value, matrix, matrix);
    }
}
