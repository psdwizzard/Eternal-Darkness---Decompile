typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern void *fn_800453E8(int kind, int subtype, int owner, int param18,
                        int param1C, int param20, int param24, int count,
                        float scale, Vec3 *position, int mode, void *source);
extern int fn_80201B54(int *object);

int fn_800453AC(int kind, int subtype, int owner, int param18,
                int param1C, int param20, int param24, int count,
                Vec3 *position, int mode, int source, float scale)
{
    int *object = fn_800453E8(kind, subtype, owner, param18, param1C, param20,
                            param24, count, scale, position, mode,
                            (void *)source);
    return fn_80201B54(object);
}
